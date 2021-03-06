#include "newuserdialog.h"
#include "ui_newuserdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    ui->setupUi(this);
    inputUserName = ""; //Default username
}

NewUserDialog::~NewUserDialog()
{
    qDebug() << "dialog destroyed";
    delete ui;
}

QString NewUserDialog::getUserName() const
{
    return inputUserName;
}

void NewUserDialog::on_okButton_clicked()
{
    //gets the text present in line edit when ok button is clicked
    QString temp_username;
    temp_username = ui->lineEdit->text();

    //Converting QString to QByteArray of char
    QByteArray username_array = temp_username.toLatin1();

    for(int i = 0; i < temp_username.length(); i++)
    {
        //Comparing ascii values of each character in array with valid ones
        //Also checks if inputted string is not larger than 10
        if(!((username_array.at(i) > 64 && username_array.at(i) < 91) ||
           (username_array.at(i) > 96 && username_array.at(i) < 123) ||
           (username_array.at(i) > 47 && username_array.at(i) < 58)) ||
           (inputUserName.length() > 10))
        {
            //Displays warning and sets username to default
            QMessageBox::warning(this, tr("Invalid Username"), tr("Entered username is invalid! No new user created."),
                                 QMessageBox::Ok);
            inputUserName = "";

            //Closes dialog after warning message closes
            close();
            break;   //breaks out of loop
        }
        else if(i == temp_username.length() - 1)
        {
            //Displays conformation message
            QMessageBox::StandardButton answer;
            answer = QMessageBox::question(this, tr("Confirm username"), "Are you sure you sure you want to create user with name: "
                                           + temp_username + "?", QMessageBox::Yes|QMessageBox::No);

            //Closes the dialog if yes is chosen
            if(answer == QMessageBox::Yes)
            {
                inputUserName = temp_username;
                //Saves the new player info to rvz_players.csv
                writeToPlayerFile("/Users/Parth/Documents/QT/RvZ/rvz_players.csv");
                close(); //calls the destructor for dialog
            }
        }
    }
}

void NewUserDialog::writeToPlayerFile(QString file_name)
{
    QFile username_file(file_name);
    readFromPlayerFile(file_name); //updates playerList to remember previous players

    //Displays warning if file is not writable
    if(!username_file.open(QIODevice::WriteOnly|QIODevice::Text))
        QMessageBox::warning(this,tr("Error!"),tr("Error writing to rvz_players.csv! No new user created"),
                                     QMessageBox::Ok);

    QTextStream write_users(&username_file);

    for(int i = 0; i < playerList.length(); i++)
        write_users << playerList.at(i) << "\n"; //Rewrites previous players

    //Writes new player with timestamp and level
    write_users << QDateTime::currentDateTime().toString("yyyyMMddhhmmss:")
                << inputUserName << ":1\n"; //":1" because all new players start at level 1

    //closes file
    username_file.close();

}

void NewUserDialog::readFromPlayerFile(QString file_name)
{
    QFile username_file(file_name);

    //Displays warning if file is not readable
    if(!username_file.open(QIODevice::ReadOnly|QIODevice::Text))
        QMessageBox::warning(this,tr("Error!"),tr("Error reading rvz_players.csv!"),
                                     QMessageBox::Ok);

    QTextStream read_users(&username_file);

    //Makes a list of the players in the file to remember when updating
    while(!read_users.atEnd())
        playerList.append(read_users.readLine());

    //closes file
    username_file.close();
}

void NewUserDialog::closeEvent(QCloseEvent *event)
{
    //Signals to activate mainwindow buttons and delete newUserUi pointer in mainwindow.cpp
    changeButtonState(1);
    deleteNewUserDialog();
    event->accept(); //Closes the dialog
}

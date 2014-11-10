#include "newuserdialog.h"
#include "ui_newuserdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QByteArray>

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    ui->setupUi(this);
}

NewUserDialog::~NewUserDialog()
{
    qDebug() << "dialog destroyed";
    delete ui;
}

QString NewUserDialog::getUserName()
{
    return inputUserName;
}

void NewUserDialog::on_okButton_clicked()
{
    //gets the text present in line edit when ok button is clicked
    inputUserName = ui->lineEdit->text();

    //Converting QString to QByteArray of char
    QByteArray username_array = inputUserName.toLatin1();

    for(int i = 0; i < inputUserName.length(); i++)
    {
        //Comparing ascii values of each character in array with valid ones
        //Also checks if inputted string is not larger than 10
        if(!((username_array.at(i) > 64 && username_array.at(i) < 91) ||
           (username_array.at(i) > 96 && username_array.at(i) < 123) ||
           (username_array.at(i) > 47 && username_array.at(i) < 58)) ||
           (inputUserName.length() > 10))
        {
            //Displays warning and sets username to default (guest)
            QMessageBox::warning(this, tr("Invalid Username"), tr("Entered username is invalid! No new user created."),
                                 QMessageBox::Ok);
            inputUserName = "Guest";

            //Closes dialog after warning message closes
            close();
            break;   //breaks out of loop
        }
        else if(i == inputUserName.length() - 1)
        {
            //Displays conformation message
            QMessageBox::StandardButton answer;
            answer = QMessageBox::question(this, tr("Confirm username"), "Are you sure you sure you want to create user with name: "
                                           + inputUserName + "?", QMessageBox::Yes|QMessageBox::No);

            //Closes the dialog if yes is chosen
            if(answer == QMessageBox::Yes)
                close();
        }
    }
}

void NewUserDialog::closeEvent(QCloseEvent *event)
{
    //Signals to show mainwindow and delete newUserUi pointer in mainwindow.cpp
    showMainWindow(1);
    deleteNewUserDialog(1);
    event->accept(); //Closes the dialog
}

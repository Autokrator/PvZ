#include "existinguserdialog.h"
#include "ui_existinguserdialog.h"
#include <QDebug>

QString FileName = "/Users/Parth/Documents/QT/RvZ/rvz_players.csv";

ExistingUserDialog::ExistingUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingUserDialog)
{
    ui->setupUi(this);
    readFromPlayerFile(FileName);
}

ExistingUserDialog::~ExistingUserDialog()
{
    delete ui;
}


void ExistingUserDialog::on_deleteButton_clicked()
{

}

void ExistingUserDialog::on_selectButton_clicked()
{

}

void ExistingUserDialog::readFromPlayerFile(QString file_name)
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
    ui->playerListBox->updatesEnabled();

    //Loop start at the end of playerList so latest timestamps are displayed first
    for(int i = playerList.length() - 1; i >= 0; i--)
    {
        //Creates a temporary list to hold pieces of each line from player file
        QStringList temp_list;
        temp_list = playerList.at(i).split(':');
        ui->playerListBox->addItem(temp_list.at(4)); //Adds the name to combo box
    }
    //closes file
    username_file.close();
}


void ExistingUserDialog::on_deleteAllButton_clicked()
{
    QFile username_file(FileName);

    //Displays warning if file is not writable
    if(!username_file.open(QIODevice::WriteOnly|QIODevice::Text))
        QMessageBox::warning(this,tr("Error!"),tr("Error writing to rvz_players.csv! No new user created"),
                                     QMessageBox::Ok);

    //Overwrites data on file
    QTextStream clear_file(&username_file);
    clear_file << "";

    username_file.close();
    readFromPlayerFile(FileName);

}

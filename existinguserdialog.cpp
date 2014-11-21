#include "existinguserdialog.h"
#include "ui_existinguserdialog.h"

QString FileName = "/Users/Parth/Documents/QT/RvZ/rvz_players.csv";

ExistingUserDialog::ExistingUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExistingUserDialog)
{
    ui->setupUi(this);
    readFromPlayerFile(); //reads the existing users on file
    inputUser = "Guest"; //default username
}

ExistingUserDialog::~ExistingUserDialog()
{
    delete ui;
}

QString ExistingUserDialog::getUsername() const
{
    return inputUser;
}

QString ExistingUserDialog::getLevel() const
{
    return userLevel;
}


void ExistingUserDialog::on_deleteButton_clicked()
{
    QFile username_file(FileName);
    //Gets the username being deleted
    QString user_delete = ui->playerListBox->currentText();

    //Displays warning if file is not writable
    if(!username_file.open(QIODevice::ReadWrite|QIODevice::Text))
        QMessageBox::warning(this,tr("Error!"),tr("Error with rvz_players.csv! No new user created"),
                                     QMessageBox::Ok);
    
    QTextStream write_users(&username_file);
    QString final_text; //final text to be saved on csv file
    
    for(int i = 0; i < playerList.length(); i++)
    {
        //Seperates the name line in name + extra components
        QStringList temp_list;
        temp_list = playerList.at(i).split(':');

        //checks if the name component matches the one being deleted
        if(temp_list.at(4) != user_delete)
            final_text.append(playerList.at(i) + "\n");
    }

    //deletes all user info on the file
    ui->deleteAllButton->clicked(true);

    //Writes the updated user info on file
    write_users << final_text;

    //closes file
    username_file.close();
    readFromPlayerFile(); //Reads new version of file to update combo box
}

void ExistingUserDialog::on_selectButton_clicked()
{
    //Saves the currently active text in the combo box as the seletected user
    inputUser = ui->playerListBox->currentText();

    //Getting the level information for selected user
    QFile username_file(FileName);

    playerList.clear(); //clears playerList from previous read calls

    //Displays warning if file is not readable
    if(!username_file.open(QIODevice::ReadOnly|QIODevice::Text))
        QMessageBox::warning(this,tr("Error!"),tr("Error reading rvz_players.csv!"),
                                     QMessageBox::Ok);

    QTextStream read_users(&username_file);

    //Makes a list of the players in the file to remember when updating
    while(!read_users.atEnd())
        playerList.append(read_users.readLine());

    for(int i = 0; i < playerList.length(); i++)
    {
        //Creates temp list to hold pieces of each line
        QStringList temp_list;
        temp_list = playerList.at(i).split(':');

        //Gets the level for the selected user based on index in temp_list
        if(inputUser == temp_list.at(4))
            userLevel = temp_list.at(5).split(',').at(0); //removes extra ',' after level
    }

    username_file.close(); //closes file
    close(); //closes dialog
}

void ExistingUserDialog::readFromPlayerFile()
{
    QFile username_file(FileName);

    playerList.clear(); //clears playerList from previous read calls
    ui->playerListBox->clear(); //clears the combo box

    //Displays warning if file is not readable
    if(!username_file.open(QIODevice::ReadOnly|QIODevice::Text))
        QMessageBox::warning(this,tr("Error!"),tr("Error reading rvz_players.csv!"),
                                     QMessageBox::Ok);

    QTextStream read_users(&username_file);

    //Makes a list of the players in the file to remember when updating
    while(!read_users.atEnd())
        playerList.append(read_users.readLine());

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
        QMessageBox::warning(this,tr("Error!"),tr("Error writing to rvz_players.csv! No new user selected"),
                                     QMessageBox::Ok);

    //Overwrites data on file
    QTextStream clear_file(&username_file);
    clear_file << "";

    username_file.close(); //closes file
    ui->playerListBox->clear(); //clears combo box
}

void ExistingUserDialog::closeEvent(QCloseEvent *event)
{
    //Signals to activate mainwindow buttons and delete dialog pointer in mainwindow.cpp
    changeButtonState(1);
    deleteExistingUserDialog();
    event->accept(); //closes dialog
}

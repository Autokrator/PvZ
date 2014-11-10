#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Default user and level information
    userName = "Guest";
    userLevel = "1";

    //Displays current user and level information
    ui->statusBar->showMessage(getStatusMessage());
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "ui deleted";
}

void MainWindow::on_newUserButton_clicked()
{
    //Opens new dialog asking for username information
    newUserUi = new NewUserDialog(this);
    newUserUi->show(); //Shows dailog to enter a username

    //Connects the mainwindow with the new user dialog
    connect(newUserUi,SIGNAL(showMainWindow(bool)),this,SLOT(show()));
    connect(newUserUi,SIGNAL(deleteNewUserDialog(bool)),this,SLOT(deleteNewUserDialog()));

    hide(); //hides the main window while the new dialog is active
}

void MainWindow::on_existUserButton_clicked()
{

}

void MainWindow::on_startButton_clicked()
{
    //Creates a GameWindow object and connects it to the main window
    gameUi = new GameWindow(this);
    connect(gameUi,SIGNAL(showMainWindow(bool)),this,SLOT(show()));
    connect(gameUi,SIGNAL(deleteGameWindow(bool)),this,SLOT(deleteGameWindow()));

    //Opens the game window and updates status message
    gameUi->show();
    gameUi->setStatusMessage(getStatusMessage()); //game window status info
    hide(); //hides the mainwindow while game window is active
}

void MainWindow::on_quitButton_clicked()
{
    //Closes the window
    close();
}

void MainWindow::deleteGameWindow()
{
    //Deletes all information of previous game window
    delete gameUi;
    gameUi = NULL;
}

void MainWindow::deleteNewUserDialog()
{
    //Takes the user information from the dialog
    userName = newUserUi->getUserName();
    ui->statusBar->showMessage(getStatusMessage());

    //Calls the NewUserDialog destructor
    delete newUserUi;
    newUserUi = NULL;
}

QString MainWindow::getStatusMessage()
{
    //Builds status message based on active user and level
    QString status_message;
    status_message = "User: " + userName;
    status_message = status_message.leftJustified(36, ' ') + "Level: " + userLevel;

    return status_message;
}

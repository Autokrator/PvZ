#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//Default user and level information
QString MainWindow::userName = "";
QString MainWindow::userLevel = "1";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Displays current user and level information
    ui->statusBar->showMessage(getStatusMessage());

    //Checks username
    checkForSetUser();

    //Displays PvZ logo on mainwindow
    QPixmap logo_image(":/Images/logo");
    ui->logoLabel->setScaledContents(1);
    ui->logoLabel->setPixmap(logo_image);

}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "ui deleted";
}

void MainWindow::updateStatusBar()
{
    //Displays current user and level information
    ui->statusBar->showMessage(getStatusMessage());
}

void MainWindow::on_newUserButton_clicked()
{
    //Opens new dialog asking for username information
    newUserUi = new NewUserDialog(this);
    newUserUi->show(); //Shows dailog to enter a username
    changeButtonState(false);

    //Connects the mainwindow with the new user dialog
    connect(newUserUi,SIGNAL(changeButtonState(bool)),this,SLOT(changeButtonState(bool)));
    connect(newUserUi,SIGNAL(deleteNewUserDialog()),this,SLOT(deleteNewUserDialog()));
}

void MainWindow::on_existUserButton_clicked()
{
    existUserUi = new ExistingUserDialog(this);
    existUserUi->show();
    changeButtonState(false);

    connect(existUserUi,SIGNAL(changeButtonState(bool)),this,SLOT(changeButtonState(bool)));
    connect(existUserUi,SIGNAL(deleteExistingUserDialog()),this,SLOT(deleteExistUserDialog()));
}

void MainWindow::on_startButton_clicked()
{
    //Creates a GameWindow object and connects it to the main window
    gameUi = new GameScreen;
    connect(gameUi,SIGNAL(showMainWindow()),this,SLOT(show()));
    connect(gameUi,SIGNAL(deleteGameWindow()),this,SLOT(deleteGameWindow()));
    connect(gameUi,SIGNAL(levelWin(bool)),this,SLOT(levelSucess(bool)));

    //Passes player info gameScreen
    gameUi->setPlayerInfo(userName,userLevel);

    //Opens the game window and updates status message
    gameUi->show();
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
    //Ensures username is not reset if dialog is closed
    if(newUserUi->getUserName() != "")
    {
        //Takes the user information from the dialog
        userName = newUserUi->getUserName();
        userLevel = "1";
        ui->statusBar->showMessage(getStatusMessage()); //updates statusbar
    }

    checkForSetUser(); //checks for nondefault username

    //Calls the NewUserDialog destructor
    delete newUserUi;
    newUserUi = NULL;
}

void MainWindow::changeButtonState(bool change)
{
    ui->startButton->setEnabled(change);
    ui->newUserButton->setEnabled(change);
    ui->existUserButton->setEnabled(change);
}

void MainWindow::deleteExistUserDialog()
{
    //Ensures username is not reset if dialog is closed
    if(existUserUi->getUsername() != "")
    {
        //Takes the user and level information from dialog
        userName = existUserUi->getUsername();
        userLevel = existUserUi->getLevel();
        ui->statusBar->showMessage(getStatusMessage()); //updates statusbar
    }

    checkForSetUser(); //checks for nondefault username

    //Calls the ExistingUserDialog destructor
    delete existUserUi;
    existUserUi = NULL;
}

void MainWindow::levelSucess(bool win)
{
    delete gameUi;

    if(win) //Increases the level by 1 if last game was won
        userLevel = QString::number(userLevel.toInt() + 1);

    //Creates a  new GameWindow object and connects it to the main window
    gameUi = new GameScreen;
    connect(gameUi,SIGNAL(showMainWindow()),this,SLOT(show()));
    connect(gameUi,SIGNAL(deleteGameWindow()),this,SLOT(deleteGameWindow()));
    connect(gameUi,SIGNAL(levelWin(bool)),this,SLOT(levelSucess(bool)));

    //Passes player info gameScreen
    gameUi->setPlayerInfo(userName,userLevel);

    //Opens the game window and updates status message
    gameUi->show();
    hide(); //hides the mainwindow while game window is active

}

QString MainWindow::getStatusMessage()
{
    //Builds status message based on active user and level
    QString status_message;
    status_message = "User: " + userName;
    status_message = status_message.leftJustified(36, ' ') + "Level: " + userLevel;

    return status_message;
}

void MainWindow::checkForSetUser()
{
    //Username empty results in Start button being inactive
    if(userName == "")
        ui->startButton->setEnabled(false);
    else
        ui->startButton->setEnabled(true);
}

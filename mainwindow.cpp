#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

    //Displays PvZ logo on mainwindow
    QString logo_file = "/Users/Parth/Downloads/pvz_logo.png";
    image = new QImage(logo_file,"PNG");
    QPixmap logo_image = QPixmap::fromImage(*image);
    ui->logoLabel->setScaledContents(1);
    ui->logoLabel->setPixmap(logo_image);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete image; //deletes image

    qDebug() << "ui deleted";
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
    if(newUserUi->getUserName() != "Guest")
    {
        //Takes the user information from the dialog
        userName = newUserUi->getUserName();
        ui->statusBar->showMessage(getStatusMessage()); //updates statusbar
    }

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
    if(existUserUi->getUsername() != "Guest")
    {
        //Takes the user and level information from dialog
        userName = existUserUi->getUsername();
        userLevel = existUserUi->getLevel();
        ui->statusBar->showMessage(getStatusMessage()); //updates statusbar
    }

    //Calls the ExistingUserDialog destructor
    delete existUserUi;
    existUserUi = NULL;
}

QString MainWindow::getStatusMessage()
{
    //Builds status message based on active user and level
    QString status_message;
    status_message = "User: " + userName;
    status_message = status_message.leftJustified(36, ' ') + "Level: " + userLevel;

    return status_message;
}

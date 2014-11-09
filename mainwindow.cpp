#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameUi = new GameWindow(this);
    connect(gameUi,SIGNAL(showMainWindow(bool)),this,SLOT(show()));

    //Default user and level information
    userName = "Guest";
    userLevel = "1";

    //Displays current user and level information
    ui->statusBar->showMessage(getStatusMessage());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameUi;
}

void MainWindow::on_newUserButton_clicked()
{

}

void MainWindow::on_existUserButton_clicked()
{

}

void MainWindow::on_startButton_clicked()
{
    //Opens game window which contains the graphics view
    gameUi->show();
    gameUi->setStatusMessage(getStatusMessage()); //game window status info
    hide();
}

void MainWindow::on_quitButton_clicked()
{
    //Closes the window
    close();
}

QString MainWindow::getStatusMessage()
{
    //Builds status message based on active user and level
    QString statusMessage;
    statusMessage = "User: " + userName;
    statusMessage = statusMessage.leftJustified(36, ' ') + "Level: " + userLevel;

    return statusMessage;
}

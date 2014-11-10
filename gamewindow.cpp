#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);
}

GameWindow::~GameWindow()
{
    delete ui;
    qDebug() << "dest called";
}

void GameWindow::setStatusMessage(const QString &message)
{
    //Sets the message to game window status bar
    ui->statusbar->showMessage(message);
}
void GameWindow::closeEvent (QCloseEvent *event)
{
    //Asks user if they want to exit the whole program or just game window
    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, tr("Exit Location"), tr("Would you like to exit to the main menu?"),
                                   QMessageBox::Yes|QMessageBox::No);

    if(answer == QMessageBox::Yes)
    {
        //Sends signal to mainwindow to unhide
        event->accept(); //closes game window
        showMainWindow(1);
        deleteGameWindow(1);
    }
    else
    {
        //Does not unhide the mainwindow which automatically calls the mainwindow destructor
        event->accept(); //closes game window
        deleteGameWindow(1);
    }
}



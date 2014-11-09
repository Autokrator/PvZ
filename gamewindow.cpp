#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>
#include "mainwindow.h"
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
}

void GameWindow::setStatusMessage(const QString &message)
{
    //Sets the message to game window status bar
    ui->statusbar->showMessage(message);
}
void GameWindow::closeEvent (QCloseEvent *event)
{
    event->accept();
    showMainWindow(1);
}



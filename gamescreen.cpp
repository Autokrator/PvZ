#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent)
{
    //Makes a graphics view of following size
    this->setFixedHeight(760);
    this->setFixedWidth(1032);

    //Creates a new scene the same size as the view
    scene = new QGraphicsScene(this);
    this->setSceneRect(0, 0,geometry().width(),geometry().height());
    this->setScene(scene);

    //Creates the background of the view
    QPixmap background(":/pvzBackground");
    scene->addPixmap(background);
}

GameScreen::~GameScreen()
{
    delete scene;
    qDebug() << "dest called";
}

void GameScreen::closeEvent(QCloseEvent *event)
{
    //Asks user if they want to exit the whole program or just game window
    QMessageBox::StandardButton answer;
    QMessageBox exit_message;
    answer = exit_message.question(this, tr("Exit Location"), tr("Would you like to exit to the main menu?"),
                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

    if(answer == QMessageBox::Yes)
    {
        //Sends signal to mainwindow to unhide
        event->accept(); //closes game window
        showMainWindow();
        deleteGameWindow();
    }
    else if(answer == QMessageBox::No)
    {
        //Does not unhide the mainwindow which automatically calls the mainwindow destructor
        event->accept(); //closes game window
        deleteGameWindow();
    }
    else if(answer == QMessageBox::Cancel)
        event->ignore(); //resumes game
}

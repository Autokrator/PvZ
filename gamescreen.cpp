#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent), playerName("Guest"), playerLevel("1")
{
    sunPoints = 100; //Intializes sunpoints for session

    //Makes a graphics view of following size
    this->setFixedHeight(760);
    this->setFixedWidth(1032);

    //Enables mouse tracking
    this->setMouseTracking(true);

    //Creates a new scene the same size as the view
    scene = new QGraphicsScene(this);
    this->setSceneRect(0,0,geometry().width(),geometry().height());
    this->setScene(scene);

    //Creates the background of the view
    QPixmap background(":/Images/pvzBackground");
    scene->addPixmap(background);

    //Creates a custom cursor
    mouseCursor = new QCursor(QPixmap(":/Images/mainCursor"),0,0);
    this->setCursor(*mouseCursor);

    //Creates background for updating hud elements
    QPixmap score_Background_note(":/Images/scoreBackgroundNote");
    QPixmap score_Background(":/Images/scoreBackground");
    scene->addPixmap(score_Background_note);
    scene->addPixmap(score_Background)->setPos(score_Background.width(),0);
    scene->addPixmap(score_Background)->setPos(score_Background.width()*2,0);

    //Adds dynamic hud elements
    Hud = new GameHud;
    scene->addItem(Hud);

    //Refresh rate of 20 ms
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(20);

    //Spawns new sun every 10 seconds
    sunSpawnTimer = new QTimer(this);
    connect(sunSpawnTimer,SIGNAL(timeout()),this,SLOT(spawnSun()));
    sunSpawnTimer->start(1000);


    QPoint initial(240,245);

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            QRect rect(initial.x(),initial.y(),80,96);
            scene->addRect(rect,QPen(Qt::black),QBrush(Qt::NoBrush));
            initial.setX(initial.x()+80);
        }
        initial.setX(240);
        initial.setY(initial.y()+96);
    }
}

GameScreen::~GameScreen()
{
    delete mouseCursor;
    delete scene;
    qDebug() << "dest called";
}

void GameScreen::setPlayerInfo(QString name, QString level)
{
    //Sets player in for gamescreen instance
    Hud->user = name;
    Hud->level = level;
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

void GameScreen::spawnSun()
{
    light1 = new Sun;
    scene->addItem(light1);
}


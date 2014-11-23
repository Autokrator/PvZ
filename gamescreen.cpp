#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent)
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

    //Sunpoints display
    QBrush black(Qt::white);
    QPen blackpen(Qt::black);
    scene->addRect(10,10,200,150,blackpen,black)->setOpacity(0.5);

    scoreTimer = new QTimer(this);
    connect(scoreTimer,SIGNAL(timeout()),this,SLOT(updateSunPoints()));
    scoreTimer->start(1000);

    QGraphicsItem *plant = new QGraphicsPixmapItem(QPixmap("/Users/Parth/Documents/Qt/RvZ/RvZ_assests/SunFA.png"));
    plant->setPos(500,400);
    scene->addItem(plant);

    light1 = new Sun;
    scene->addItem(light1);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(40);

    //qDebug() << Sun::sunPoints;

    QPoint initial(240,245);

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            light1 = new Sun;
            scene->addItem(light1);

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

void GameScreen::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << e->pos();
}

void GameScreen::displaySunPoints() const
{

}

void GameScreen::updateSunPoints()
{
//    sunPoints = Sun::getSunPoints();
//    sunPointsText->setPlainText(QString::number(sunPoints));
//    sunPointsText->setPos(20,20);
//    scene->addItem(sunPointsText);
}

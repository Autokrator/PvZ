#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent), playerName("Guest"), playerLevel("1"), mouseState(0)
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

    /*Adding clickable plant icons*/

    //Aligning to y-point
    int y_alignment = 50;

    //Loading pixmap of each card
    peashooterCard = new QGraphicsPixmapItem(QPixmap(":/Images/peashooterCard"));
    sunflowerCard = new QGraphicsPixmapItem(QPixmap(":/Images/sunflowerCard"));
    walnutCard = new QGraphicsPixmapItem(QPixmap(":/Images/walnutCard"));
    cherrybombCard = new QGraphicsPixmapItem(QPixmap(":/Images/cherrybombCard"));

    //Setting their positions, making them selectable and adding them to the scene
    //peashooter
    peashooterCard->setPos(score_Background.width()+40,y_alignment);
    peashooterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(peashooterCard);

    //sunflower Card
    sunflowerCard->setPos(peashooterCard->x()+50,y_alignment);
    sunflowerCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(sunflowerCard);

    //walnut Card
    walnutCard->setPos(sunflowerCard->x()+50,y_alignment);
    walnutCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(walnutCard);

    //cherrybomb Card
    cherrybombCard->setPos(walnutCard->x()+50,y_alignment);
    cherrybombCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(cherrybombCard);


    /*End of adding selectable cards to scene*/

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
    sunSpawnTimer->start(10000);


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

void GameScreen::mousePressEvent(QMouseEvent *e)
{
    QGraphicsView::mousePressEvent(e);

    //Checks to see which card(if any) is selected when mouse is pressed
    if(peashooterCard->isSelected() && Sun::getSunPoints() >= 100)
    {
        mouseState = 1; //Gives permission to plant peashooter

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/peashooterGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        peashooterCard->setOpacity(1);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        cherrybombCard->setOpacity(0.5);

        //Resets selection
        peashooterCard->setSelected(false);
    }
    else if(sunflowerCard->isSelected() && Sun::getSunPoints() >= 50)
    {
        mouseState = 2; //Gives permission to plant sunflower

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/sunflowerGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        sunflowerCard->setOpacity(1);
        peashooterCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        cherrybombCard->setOpacity(0.5);

        //Resets selection
        sunflowerCard->setSelected(false);
    }
    else if(walnutCard->isSelected() && Sun::getSunPoints() >= 50)
    {
        mouseState = 3; //Gives permission to plant walnut

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/walnutGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        walnutCard->setOpacity(1);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        cherrybombCard->setOpacity(0.5);
    }
    else if(cherrybombCard->isSelected() && Sun::getSunPoints() >= 150)
    {
        mouseState = 4; //Gives permission to plant cherrybomb

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/cherrybombGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        cherrybombCard->setOpacity(1);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
    }

    //Checks if user clicked to plant
    if(mouseState != 0)
        addPlant( e);
}

void GameScreen::mouseMoveEvent(QMouseEvent *e)
{
    QGraphicsView::mouseMoveEvent(e);
}

void GameScreen::addPlant(QMouseEvent *event)
{

}

void GameScreen::spawnSun()
{
    light1 = new Sun;
    scene->addItem(light1);
}


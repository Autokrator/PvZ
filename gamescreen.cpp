#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent), sunSpawnInterval(10000), playerName("Guest"), playerLevel("1"),
    mouseState(0)
{
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

    //Sets a custom cursor
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
    sunSpawnTimer->start(sunSpawnInterval);

    //Lawn plot properties
    const int lawn_x = 240;
    const int lawn_y = 245;
    //QPoint initial(240,245); //location of where row 1 and column 1 plot is
    const int lawn_plot_width = 80; //width of each plot
    const int lawn_plot_height = 96; //height of each plot
    lawnVector.resize(5);

    for(int i = 0; i < 5; i++)
    {
        lawnVector.at(i).resize(9);

        for(int j = 0; j < 9; j++)
        {
            //Sets the top and bottom cordinates for each plot
            lawnPiece temp;
            temp.topX = lawn_x + j*lawn_plot_width;
            temp.topY = lawn_y + i*lawn_plot_height;
            temp.botX = temp.topX + lawn_plot_width;
            temp.botY = temp.topY + lawn_plot_height;
            temp.isPlantable = true;

            lawnVector[i][j] = temp;
        }
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
    //Sets player in for gamescreen and hud instance
    Hud->user = name;
    Hud->level = level;
    playerName = name;
    playerLevel = level;
}

void GameScreen::closeEvent(QCloseEvent *event)
{
    timer->stop(); // pauses the scene's advance calls
    int remember_sun_spawn_timer = sunSpawnTimer->remainingTime();
    sunSpawnTimer->stop(); //Stops new suns from spawning

    Sun::isPaused = true; //Changes state for all suns in the scene
    scene->advance();   //Advances to allow suns to activate Sun::pause() func

    //Asks user if they want to exit the level
    QMessageBox exit_message;

    int message_width = lawnVector[1][8].botX - lawnVector[1][0].topX;
    int message_height = lawnVector[3][0].botY - lawnVector[1][0].topY;
    exit_message.setFixedSize(message_width,message_height);
    exit_message.setText(tr("Are you sure you want to leave this level?"));
    exit_message.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);

    if(exit_message.exec() == exit_message.Ok) //If yes is selected
    {
        deleteGameWindow(); //Signals to delete gamewindow
        event->accept(); //closes game window
        showMainWindow(); //signals to display main window

    }
    else //If cancel is selected or window is closed
    {
        event->ignore(); //resumes game

        Sun::isPaused = false; //Changes back the state for all suns in the scene
        timer->start(20); //reactivates the advance and timeout() connection

        //Sun spawn timer interval is the remaining time from pause
        sunSpawnTimer->start(remember_sun_spawn_timer);
    }
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
        addPlant(e);
}

void GameScreen::addPlant(QMouseEvent *event)
{
    //Temporary variables to make conditional statements shorter
    int m_x = event->x();
    int m_y = event->y();

    for(int i = 0; i < (int)lawnVector.size(); i++)
    {
        for(int j = 0; j < (int)lawnVector.at(i).size(); j++)
        {
            lawnPiece *temp = &lawnVector[i][j];
            
            if(((m_x >= temp->topX && m_x <= temp->botX) &&
               (m_y >= temp->topY && m_y <= temp->botY)) &&
                temp->isPlantable)
            {
                if(mouseState == 1)
                {
                    temp->isPlantable = false;
                    Sun::updateSunPoints(-100);

                    QGraphicsPixmapItem *peashooter = new QGraphicsPixmapItem(QPixmap(":/Images/peashooter"));
                    peashooter->setPos(temp->topX + 5,temp->topY + 5) ;
                    scene->addItem(peashooter);
                }
                else if(mouseState == 2)
                {
                    temp->isPlantable = false;
                    Sun::updateSunPoints(-50);

                    QGraphicsPixmapItem *sunflower = new QGraphicsPixmapItem(QPixmap(":/Images/sunflower"));
                    sunflower->setPos(temp->topX + 5,temp->topY + 5) ;
                    scene->addItem(sunflower);
                }
                else if(mouseState == 3)
                {
                    temp->isPlantable = false;
                    Sun::updateSunPoints(-50);

                    QGraphicsPixmapItem *walnut = new QGraphicsPixmapItem(QPixmap(":/Images/walnut"));
                    walnut->setPos(temp->topX + 5,temp->topY + 5) ;
                    scene->addItem(walnut);
                }
                else if(mouseState == 4)
                {
                    temp->isPlantable = false;
                    Sun::updateSunPoints(-150);

                    QGraphicsPixmapItem *cherrybomb = new QGraphicsPixmapItem(QPixmap(":/Images/cherrybomb"));
                    cherrybomb->setPos(temp->topX + 5,temp->topY + 5) ;
                    scene->addItem(cherrybomb);
                }

                //Returns the mouse to default state and cursor
                mouseState = 0;
                setDefaultCursor();

                //Reset the opacities to indicate no active selected plant
                peashooterCard->setOpacity(1);
                sunflowerCard->setOpacity(1);
                walnutCard->setOpacity(1);
                cherrybombCard->setOpacity(1);
            }
        }
    }
}

void GameScreen::setDefaultCursor()
{
    //Sets a default custom cursor
    delete mouseCursor;
    mouseCursor = new QCursor(QPixmap(":/Images/mainCursor"),0,0);
    this->setCursor(*mouseCursor);
}

void GameScreen::spawnSun()
{
    /*Accounting for a interval that isn't the desired spawn rate
      this when the game is paused the interval is the remaining time
      from last countdown*/
    if(sunSpawnTimer->interval() != sunSpawnInterval)
    {
        //Restarts the timer with default sunSpawnInterval
        sunSpawnTimer->stop();
        sunSpawnTimer->start(sunSpawnInterval);
    }

    //Spawns a new type 1 sun
    sun = new Sun;
    scene->addItem(sun);
}


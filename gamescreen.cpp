#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent), sunSpawnInterval(500), playerName("Guest"), playerLevel("1"),
    mouseCursor(0)
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

    //Aligning to y-point and x-point
    int y_alignment = 50;
    int x_adj = 50;

    //Loading pixmap of each card
    peashooterCard = new QGraphicsPixmapItem(QPixmap(":/Images/peashooterCard"));
    sunflowerCard = new QGraphicsPixmapItem(QPixmap(":/Images/sunflowerCard"));
    walnutCard = new QGraphicsPixmapItem(QPixmap(":/Images/walnutCard"));
    cherrybombCard = new QGraphicsPixmapItem(QPixmap(":/Images/cherrybombCard"));
    chomperCard = new QGraphicsPixmapItem(QPixmap(":/Images/chomperCard"));
    snowpeashooterCard = new QGraphicsPixmapItem(QPixmap(":/Images/snowpeaCard"));
    repeaterCard = new QGraphicsPixmapItem(QPixmap(":/Images/repeaterCard"));
    potatomineCard = new QGraphicsPixmapItem(QPixmap(":/Images/potatomineCard"));

    //Setting their positions, making them selectable and adding them to the scene
    //peashooter
    peashooterCard->setPos(score_Background.width()+40,y_alignment);
    peashooterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(peashooterCard);

    //sunflower Card
    sunflowerCard->setPos(peashooterCard->x()+x_adj,y_alignment);
    sunflowerCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(sunflowerCard);

    //walnut Card
    walnutCard->setPos(sunflowerCard->x()+x_adj,y_alignment);
    walnutCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(walnutCard);

    //cherrybomb Card
    cherrybombCard->setPos(walnutCard->x()+x_adj,y_alignment);
    cherrybombCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(cherrybombCard);

    //chomper card
    chomperCard->setPos(score_Background.width()*2 + 40, y_alignment);
    chomperCard->setFlag((QGraphicsItem::ItemIsSelectable));
    scene->addItem(chomperCard);

    //snowpea card
    snowpeashooterCard->setPos(chomperCard->x()+x_adj,y_alignment);
    snowpeashooterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(snowpeashooterCard);

    //repeater card
    repeaterCard->setPos(snowpeashooterCard->x()+x_adj,y_alignment);
    repeaterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(repeaterCard);

    //potatomine card
    potatomineCard->setPos(repeaterCard->x()+x_adj,y_alignment);
    potatomineCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(potatomineCard);

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
    const int lawn_x = 240;//location of where row 1 and column 1 plot is
    const int lawn_y = 245;
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
            temp.topX = lawn_x + (j*lawn_plot_width);
            temp.topY = lawn_y + (i*lawn_plot_height-1);
            temp.botX = (temp.topX-1) + lawn_plot_width;
            temp.botY = (temp.topY-1) + lawn_plot_height;

            lawnVector[i][j] = temp;
        }
    }

    for(int i = 0; i < 1; i++)
    {
        QRect temp_rect(lawnVector[4][0].topX,lawnVector[4][0].topY,720,96);
        BucketHeadZombie *zombie = new BucketHeadZombie(&temp_rect);
        scene->addItem(zombie);
    }

    QRect temp_rect(lawnVector[0][0].topX,lawnVector[0][0].topY,80,96);
    LawnMower *lawn_mower = new LawnMower(&temp_rect,(int)scene->width());
    scene->addItem(lawn_mower);
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
        chomperCard->setOpacity(0.5);
        snowpeashooterCard->setOpacity(0.5);
        repeaterCard->setOpacity(0.5);
        potatomineCard->setOpacity(0.5);

        //Leaves function
        return;
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
        chomperCard->setOpacity(0.5);
        snowpeashooterCard->setOpacity(0.5);
        repeaterCard->setOpacity(0.5);
        potatomineCard->setOpacity(0.5);

        //Leaves function
        return;
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
        chomperCard->setOpacity(0.5);
        snowpeashooterCard->setOpacity(0.5);
        repeaterCard->setOpacity(0.5);
        potatomineCard->setOpacity(0.5);

        //Leaves function
        return;
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
        chomperCard->setOpacity(0.5);
        snowpeashooterCard->setOpacity(0.5);
        repeaterCard->setOpacity(0.5);
        potatomineCard->setOpacity(0.5);

        //Leaves function
        return;
    }
    else if(chomperCard->isSelected() && Sun::getSunPoints() >= 150)
    {
        mouseState = 5; //Gives permission to plant chomper

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/chomperGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        chomperCard->setOpacity(1);
        cherrybombCard->setOpacity(0.5);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        snowpeashooterCard->setOpacity(0.5);
        repeaterCard->setOpacity(0.5);
        potatomineCard->setOpacity(0.5);

        //Leaves function
        return;
    }
    else if(snowpeashooterCard->isSelected() && Sun::getSunPoints() >= 175)
    {
        mouseState = 6; //Gives permission to plant snowpea

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/snowpeaGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        snowpeashooterCard->setOpacity(1);
        cherrybombCard->setOpacity(0.5);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        chomperCard->setOpacity(0.5);
        repeaterCard->setOpacity(0.5);
        potatomineCard->setOpacity(0.5);

        //Leaves function
        return;
    }
    else if(repeaterCard->isSelected() && Sun::getSunPoints() >= 200)
    {
        mouseState = 7; //Gives permission to plant repeater

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/repeaterGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        repeaterCard->setOpacity(1);
        cherrybombCard->setOpacity(0.5);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        chomperCard->setOpacity(0.5);
        snowpeashooterCard->setOpacity(0.5);
        potatomineCard->setOpacity(0.5);

        //Leaves function
        return;
    }
    else if(potatomineCard->isSelected() && Sun::getSunPoints() >= 50)
    {
        mouseState = 8; //Gives permission to potatomine

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/potatomineGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        potatomineCard->setOpacity(1);
        cherrybombCard->setOpacity(0.5);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        chomperCard->setOpacity(0.5);
        snowpeashooterCard->setOpacity(0.5);
        repeaterCard->setOpacity(0.5);

        //Leaves function
        return;
    }
    else if(mouseState != 0)
    {
        //Checks if user clicked to plant
        addPlant(e->x(),e->y());
    }
}

void GameScreen::addPlant(int m_x, int m_y)
{
    for(int i = 0; i < (int)lawnVector.size(); i++)
    {
        for(int j = 0; j < (int)lawnVector.at(i).size(); j++)
        {
            lawnPiece *temp = &lawnVector[i][j];
            
            if(((m_x >= temp->topX && m_x <= temp->botX) &&
               (m_y >= temp->topY && m_y <= temp->botY)))
            {
                //Checks for plant item in current tile
                QGraphicsRectItem *tile = new QGraphicsRectItem(temp->topX,temp->topY,
                                                                temp->botX-temp->topX,
                                                                temp->botY-temp->topY);
                tile->setPen(QPen(Qt::transparent));
                scene->addItem(tile);

                //Creates a list of items currently colliding with the mask
                QList<QGraphicsItem *> collision_list = scene->collidingItems(tile);

                if(mouseState != 7)
                {
                    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
                    for(int i = 0; i < (int)collision_list.size(); i++)
                    {
                        Plant * item = dynamic_cast<Plant *>(collision_list.at(i));
                        if (item)
                        {
                            delete tile;
                            tile = NULL;
                            goto reset;
                        }
                    }
                    //deletes the tile object created for collision test
                    delete tile;
                    tile = NULL;
                }

                //Rect that holds information of the row it is planted on
                QRect temp_rect;
                temp_rect.setX(temp->topX);
                temp_rect.setY(temp->topY);
                temp_rect.setWidth(scene->width()-temp->topX);
                temp_rect.setHeight(temp->botY - temp->topY);

                if(mouseState == 1)
                {
                    Peashooter *peashooter = new Peashooter(&temp_rect);
                    scene->addItem(peashooter);
                    Sun::updateSunPoints(-peashooter->getCost());
                    goto reset;
                }
                else if(mouseState == 2)
                {
                    Sunflower *sunflower = new Sunflower(&temp_rect);
                    scene->addItem(sunflower);
                    Sun::updateSunPoints(-sunflower->getCost());
                    goto reset;
                }
                else if(mouseState == 3)
                {
                    Walnut *walnut = new Walnut(&temp_rect);
                    scene->addItem(walnut);
                    Sun::updateSunPoints(-walnut->getCost());
                    goto reset;
                }
                else if(mouseState == 4)
                {
                    QRect tile(temp->topX,temp->topY,
                               temp->botX-temp->topX,
                               temp->botY-temp->topY);

                    Cherrybomb *cherrybomb = new Cherrybomb(&tile);
                    scene->addItem(cherrybomb);
                    Sun::updateSunPoints(-cherrybomb->getCost());
                    goto reset;
                }
                else if(mouseState == 5)
                {
                    QRect tile(temp->topX,temp->topY,
                               temp->botX-temp->topX,
                               temp->botY-temp->topY);

                    Chomper *chomper = new Chomper(&tile);
                    scene->addItem(chomper);
                    Sun::updateSunPoints(-chomper->getCost());
                    goto reset;
                }
                else if(mouseState == 6)
                {
                    Peashooter *peashooter = new Peashooter(&temp_rect,true);
                    scene->addItem(peashooter);
                    Sun::updateSunPoints(-peashooter->getCost());
                    goto reset;
                }
                else if(mouseState == 7)
                {
                    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
                    for(int i = 0; i < (int)collision_list.size(); i++)
                    {
                        Peashooter * item = dynamic_cast<Peashooter *>(collision_list.at(i));
                        if (item)
                        {
                            delete item;
                            Repeater *repeater = new Repeater(&temp_rect);
                            scene->addItem(repeater);
                            Sun::updateSunPoints(-repeater->getCost());
                            goto reset;
                        }
                    }

                    goto reset; //if no peashooter is found on tile
                }
                else if(mouseState == 8)
                {
                    QRect tile(temp->topX,temp->topY,
                               temp->botX-temp->topX,
                               temp->botY-temp->topY);

                    Potatomine *potatomine = new Potatomine(&tile);
                    scene->addItem(potatomine);

                    Sun::updateSunPoints(-potatomine->getCost());
                    goto reset;
                }

            }
        }
    }

reset:
    //Returns the mouse to default state and cursor
    mouseState = 0;
    setDefaultCursor();

    //Resets the opacities after plant is placed
    peashooterCard->setOpacity(1);
    sunflowerCard->setOpacity(1);
    walnutCard->setOpacity(1);
    cherrybombCard->setOpacity(1);
    chomperCard->setOpacity(1);
    snowpeashooterCard->setOpacity(1);
    repeaterCard->setOpacity(1);
    potatomineCard->setOpacity(1);
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


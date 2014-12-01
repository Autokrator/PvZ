#include "gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent) :
    QGraphicsView(parent), sunSpawnInterval(10000), playerName("Guest"), playerLevel("1"),
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

    //Adding all plants' seeding timers
    peashooterTimer = new QTimer(this);
    sunflowerTimer = new QTimer(this);
    cherrybombTimer = new QTimer(this);
    walnutTimer = new QTimer(this);
    repeaterTimer = new QTimer(this);
    chomperTimer = new QTimer(this);
    snowpeashooterTimer = new QTimer(this);
    potatomineTimer = new QTimer(this);

    //Connecting all the timers to coressponding countdown slots
    connect(peashooterTimer,SIGNAL(timeout()),this,SLOT(peashooterCountdown()));
    connect(sunflowerTimer,SIGNAL(timeout()),this,SLOT(sunflowerCountdown()));
    connect(cherrybombTimer,SIGNAL(timeout()),this,SLOT(cherrybombCountdown()));
    connect(walnutTimer,SIGNAL(timeout()),this,SLOT(walnutCountdown()));
    connect(repeaterTimer,SIGNAL(timeout()),this,SLOT(repeaterCountdown()));
    connect(chomperTimer,SIGNAL(timeout()),this,SLOT(chomperCountdown()));
    connect(snowpeashooterTimer,SIGNAL(timeout()),this,SLOT(snowpeashooterCountdown()));
    connect(potatomineTimer,SIGNAL(timeout()),this,SLOT(potatomineCountdown()));


    //Adds dynamic hud elements
    Hud = new GameHud;
    scene->addItem(Hud);

    //Creates Rect item used to cover cards during countdown so user knows when countdown finishes
    peashooterRect = new QGraphicsRectItem(peashooterCard->boundingRect());
    sunflowerRect = new QGraphicsRectItem(peashooterCard->boundingRect());
    cherrybombRect = new QGraphicsRectItem(peashooterCard->boundingRect());
    walnutRect = new QGraphicsRectItem(peashooterCard->boundingRect());
    chomperRect = new QGraphicsRectItem(peashooterCard->boundingRect());
    repeaterRect = new QGraphicsRectItem(peashooterCard->boundingRect());
    potatomineRect = new QGraphicsRectItem(peashooterCard->boundingRect());
    snowpeashooterRect = new QGraphicsRectItem(peashooterCard->boundingRect());

    /*Adding rectangles to the scene - Start */
    peashooterRect->setOpacity(0.3);
    peashooterRect->setBrush(QBrush(Qt::black));
    peashooterRect->setPos(peashooterCard->pos());
    scene->addItem(peashooterRect);

    sunflowerRect->setOpacity(0.3);
    sunflowerRect->setBrush(QBrush(Qt::black));
    sunflowerRect->setPos(sunflowerCard->pos());
    scene->addItem(sunflowerRect);

    cherrybombRect->setOpacity(0.3);
    cherrybombRect->setBrush(QBrush(Qt::black));
    cherrybombRect->setPos(cherrybombCard->pos());
    scene->addItem(cherrybombRect);

    walnutRect->setOpacity(0.3);
    walnutRect->setBrush(QBrush(Qt::black));
    walnutRect->setPos(walnutCard->pos());
    scene->addItem(walnutRect);

    chomperRect->setOpacity(0.3);
    chomperRect->setBrush(QBrush(Qt::black));
    chomperRect->setPos(chomperCard->pos());
    scene->addItem(chomperRect);

    repeaterRect->setOpacity(0.3);
    repeaterRect->setBrush(QBrush(Qt::black));
    repeaterRect->setPos(repeaterCard->pos());
    scene->addItem(repeaterRect);

    potatomineRect->setOpacity(0.3);
    potatomineRect->setBrush(QBrush(Qt::black));
    potatomineRect->setPos(potatomineCard->pos());
    scene->addItem(potatomineRect);

    snowpeashooterRect->setOpacity(0.3);
    snowpeashooterRect->setBrush(QBrush(Qt::black));
    snowpeashooterRect->setPos(snowpeashooterCard->pos());
    scene->addItem(snowpeashooterRect);

    /*End of adding graphics rect*/

    //Refresh rate of 20 ms
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkSunPoints()));
    timer->start(20);

    //Spawns new sun every 10 seconds
    sunSpawnTimer = new QTimer(this);
    connect(sunSpawnTimer,SIGNAL(timeout()),this,SLOT(spawnSun()));
    sunSpawnTimer->start(sunSpawnInterval);

    //Load level elements
    loadLevel();

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
    else if(potatomineCard->isSelected() && Sun::getSunPoints() >= 25)
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

void GameScreen::mouseMoveEvent(QMouseEvent *e)
{
    QGraphicsView::mouseMoveEvent(e);

    //Displays tooltip information for each plant selection card
    if(peashooterCard->isUnderMouse())
    {
        this->setToolTip("Pea Shooter\n Cost: 100");
    }
    else if(sunflowerCard->isUnderMouse())
        this->setToolTip("Sun Flower\n Cost: 50");
    else if(walnutCard->isUnderMouse())
        this->setToolTip("Wall Nut\n Cost: 50");
    else if(cherrybombCard->isUnderMouse())
        this->setToolTip("Cherry Bomb\n Cost: 150");
    else if(chomperCard->isUnderMouse())
        this->setToolTip("Chomper\n Cost: 150");
    else if(snowpeashooterCard->isUnderMouse())
        this->setToolTip("Snowpea Shooter\n Cost: 175");
    else if(repeaterCard->isUnderMouse())
        this->setToolTip("Repeater\n Cost: 200");
    else if(potatomineCard->isUnderMouse())
        this->setToolTip("Potato Mine\n Cost: 25");
    else
        this->setToolTip("");
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

                    peashooterCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                    peashooterTimer->start(Peashooter::seedingTime);
                    goto reset;
                }
                else if(mouseState == 2)
                {
                    Sunflower *sunflower = new Sunflower(&temp_rect);
                    scene->addItem(sunflower);
                    Sun::updateSunPoints(-sunflower->getCost());

                    sunflowerCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                    sunflowerTimer->start(Sunflower::seedingTime);
                    goto reset;
                }
                else if(mouseState == 3)
                {
                    Walnut *walnut = new Walnut(&temp_rect);
                    scene->addItem(walnut);
                    Sun::updateSunPoints(-walnut->getCost());

                    walnutCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                    walnutTimer->start(Walnut::seedingTime);
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

                    cherrybombCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                    cherrybombTimer->start(Cherrybomb::seedingTime);
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

                    chomperCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                    chomperTimer->start(Chomper::seedingTime);
                    goto reset;
                }
                else if(mouseState == 6)
                {
                    Peashooter *peashooter = new Peashooter(&temp_rect,true);
                    scene->addItem(peashooter);
                    Sun::updateSunPoints(-peashooter->getCost());

                    snowpeashooterCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                    snowpeashooterTimer->start(Peashooter::seedingTime);
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

                            repeaterCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                            repeaterTimer->start(Repeater::seedingTime);
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

                    potatomineCard->setFlag(QGraphicsItem::ItemIsSelectable,false);
                    potatomineTimer->start(Potatomine::seedingTime);
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

void GameScreen::loadLevel()
{
    QString file_name("/Users/Parth/Documents/QT/RvZ/rvz_levels.csv");

    QFile level_file(file_name);

    //Displays warning if file is not readable and exits program
    if(!level_file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(0,"Cannot execute RvZ","rvz_levels.csv does not exist or is unreadable!",
                             QMessageBox::Ok);
        return;
    }

    QTextStream read_level(&level_file);
    while(!read_level.atEnd())
    {
        QString temp_level;
        QStringList temp_list;

        temp_list = read_level.readLine().split(':');
        temp_level = temp_list.at(0);

        if(temp_level == playerLevel) //searches for current level
        {
            //Extracts level information from file
            zombieSequence = temp_list.at(1).split(',');
            activeRows = temp_list.at(2).toInt();
            startTime = temp_list.at(3).toDouble();
            startingInterval = temp_list.at(4).toDouble();
            intervalDecrement = temp_list.at(5).toDouble();

            goto close;
        }
    }

    close:
    level_file.close(); //closes file

    //Loading lawn from activeRows

    //Lawn plot properties
    const int lawn_x = 240;//location of where row 1 and column 1 plot is
    const int lawn_y = 245;
    const int lawn_plot_width = 80; //width of each plot
    const int lawn_plot_height = 96; //height of each plot
    lawnVector.resize(5); //max five rows

    //Generating 2D lawn vector (5x9)
    for(int i = 0; i < (int)lawnVector.size(); i++)
    {
        lawnVector.at(i).resize(9); //max number of columns

        for(int j = 0; j < (int)lawnVector.at(i).size(); j++)
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

    //Adding dead zones to the lawn to show inactive lanes
    if(activeRows == 5)
        return;

    //Creating inactive rects to use for drawing
    QRect inactive_area_1;
    QRect inactive_area_2;

    activeRows = 3;
    if(activeRows == 1)
    {
        //Top 2 rows
        inactive_area_1.setX(lawnVector[0][0].topX);
        inactive_area_1.setY(lawnVector[0][0].topY);
        inactive_area_1.setWidth(lawn_plot_width*9);
        inactive_area_1.setHeight(lawn_plot_height*2);

        //Bottom 2 rows
        inactive_area_2.setX(lawnVector[3][0].topX);
        inactive_area_2.setY(lawnVector[3][0].topY);
        inactive_area_2.setWidth(lawn_plot_width*9);
        inactive_area_2.setHeight(lawn_plot_height*2);
    }
    else if(activeRows == 3)
    {
        //Top row
        inactive_area_1.setX(lawnVector[0][0].topX);
        inactive_area_1.setY(lawnVector[0][0].topY);
        inactive_area_1.setWidth(lawn_plot_width*9);
        inactive_area_1.setHeight(lawn_plot_height);

        //Bottom row
        inactive_area_2.setX(lawnVector[4][0].topX);
        inactive_area_2.setY(lawnVector[4][0].topY);
        inactive_area_2.setWidth(lawn_plot_width*9);
        inactive_area_2.setHeight(lawn_plot_height);
    }

    //Creates visual representation on scene
    QGraphicsRectItem *deadArea = new QGraphicsRectItem(inactive_area_1);
    deadArea->setPen(QPen(Qt::transparent));
    deadArea->setBrush(QBrush(QColor(139,69,19)));
    deadArea->setOpacity(0.4);
    scene->addItem(deadArea);

    deadArea = new QGraphicsRectItem(inactive_area_2);
    deadArea->setPen(QPen(Qt::transparent));
    deadArea->setBrush(QBrush(QColor(139,69,19)));
    deadArea->setOpacity(0.4);
    scene->addItem(deadArea);

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

void GameScreen::checkSunPoints()
{
    if(Sun::getSunPoints() < 25)
    {
        peashooterCard->setPixmap(QPixmap(":/Images/peashooterCardGray"));
        sunflowerCard->setPixmap(QPixmap(":/Images/sunflowerCardGray"));
        cherrybombCard->setPixmap(QPixmap(":/Images/cherrybombCardGray"));
        walnutCard->setPixmap(QPixmap(":/Images/walnutCardGray"));
        repeaterCard->setPixmap(QPixmap(":/Images/repeaterCardGray"));
        chomperCard->setPixmap(QPixmap(":/Images/chomperCardGray"));
        potatomineCard->setPixmap(QPixmap(":/Images/potatomineCardGray"));
        snowpeashooterCard->setPixmap(QPixmap(":Images/snowpeaCardGray"));
    }
    else if(Sun::getSunPoints() < 50)
    {
        peashooterCard->setPixmap(QPixmap(":/Images/peashooterCardGray"));
        sunflowerCard->setPixmap(QPixmap(":/Images/sunflowerCardGray"));
        cherrybombCard->setPixmap(QPixmap(":/Images/cherrybombCardGray"));
        walnutCard->setPixmap(QPixmap(":/Images/walnutCardGray"));
        repeaterCard->setPixmap(QPixmap(":/Images/repeaterCardGray"));
        chomperCard->setPixmap(QPixmap(":/Images/chomperCardGray"));
        potatomineCard->setPixmap(QPixmap(":/Images/potatomineCard"));
        snowpeashooterCard->setPixmap(QPixmap(":Images/snowpeaCardGray"));
    }
    else if(Sun::getSunPoints() < 100)
    {
        peashooterCard->setPixmap(QPixmap(":/Images/peashooterCardGray"));
        sunflowerCard->setPixmap(QPixmap(":/Images/sunflowerCard"));
        cherrybombCard->setPixmap(QPixmap(":/Images/cherrybombCardGray"));
        walnutCard->setPixmap(QPixmap(":/Images/walnutCard"));
        repeaterCard->setPixmap(QPixmap(":/Images/repeaterCardGray"));
        chomperCard->setPixmap(QPixmap(":/Images/chomperCardGray"));
        potatomineCard->setPixmap(QPixmap(":/Images/potatomineCard"));
        snowpeashooterCard->setPixmap(QPixmap(":Images/snowpeaCardGray"));
    }
    else if(Sun::getSunPoints() < 150)
    {
        peashooterCard->setPixmap(QPixmap(":/Images/peashooterCard"));
        sunflowerCard->setPixmap(QPixmap(":/Images/sunflowerCard"));
        cherrybombCard->setPixmap(QPixmap(":/Images/cherrybombCardGray"));
        walnutCard->setPixmap(QPixmap(":/Images/walnutCard"));
        repeaterCard->setPixmap(QPixmap(":/Images/repeaterCardGray"));
        chomperCard->setPixmap(QPixmap(":/Images/chomperCardGray"));
        potatomineCard->setPixmap(QPixmap(":/Images/potatomineCard"));
        snowpeashooterCard->setPixmap(QPixmap(":Images/snowpeaCardGray"));
    }
    else if(Sun::getSunPoints() < 175)
    {
        peashooterCard->setPixmap(QPixmap(":/Images/peashooterCard"));
        sunflowerCard->setPixmap(QPixmap(":/Images/sunflowerCard"));
        cherrybombCard->setPixmap(QPixmap(":/Images/cherrybombCard"));
        walnutCard->setPixmap(QPixmap(":/Images/walnutCard"));
        repeaterCard->setPixmap(QPixmap(":/Images/repeaterCardGray"));
        chomperCard->setPixmap(QPixmap(":/Images/chomperCard"));
        potatomineCard->setPixmap(QPixmap(":/Images/potatomineCard"));
        snowpeashooterCard->setPixmap(QPixmap(":Images/snowpeaCardGray"));
    }
    else if(Sun::getSunPoints() < 200)
    {
        peashooterCard->setPixmap(QPixmap(":/Images/peashooterCard"));
        sunflowerCard->setPixmap(QPixmap(":/Images/sunflowerCard"));
        cherrybombCard->setPixmap(QPixmap(":/Images/cherrybombCard"));
        walnutCard->setPixmap(QPixmap(":/Images/walnutCard"));
        repeaterCard->setPixmap(QPixmap(":/Images/repeaterCardGray"));
        chomperCard->setPixmap(QPixmap(":/Images/chomperCard"));
        potatomineCard->setPixmap(QPixmap(":/Images/potatomineCard"));
        snowpeashooterCard->setPixmap(QPixmap(":Images/snowpeaCard"));
    }
    else
    {
        peashooterCard->setPixmap(QPixmap(":/Images/peashooterCard"));
        sunflowerCard->setPixmap(QPixmap(":/Images/sunflowerCard"));
        cherrybombCard->setPixmap(QPixmap(":/Images/cherrybombCard"));
        walnutCard->setPixmap(QPixmap(":/Images/walnutCard"));
        repeaterCard->setPixmap(QPixmap(":/Images/repeaterCard"));
        chomperCard->setPixmap(QPixmap(":/Images/chomperCard"));
        potatomineCard->setPixmap(QPixmap(":/Images/potatomineCard"));
        snowpeashooterCard->setPixmap(QPixmap(":Images/snowpeaCard"));
    }

    //Peashooter countdown
    if(peashooterTimer->remainingTime() == -1) //timer stopped
        peashooterRect->hide();
    else
        peashooterRect->show();


    //Sunflower countdown
    if(sunflowerTimer->remainingTime() == -1) //timer stopped
        sunflowerRect->hide();
    else
        sunflowerRect->show();

    //Cherrybomb countdown
    if(cherrybombTimer->remainingTime() == -1) //timer stopped
        cherrybombRect->hide();
    else
        cherrybombRect->show();

    //Walnut countdown
    if(walnutTimer->remainingTime() == -1) //timer stopped
        walnutRect->hide();
    else
        walnutRect->show();

    //Repeater countdown
    if(repeaterTimer->remainingTime() == -1) //timer stopped
        repeaterRect->hide();
    else
        repeaterRect->show();

    //Snowpea countdown
    if(snowpeashooterTimer->remainingTime() == -1) //timer stopped
        snowpeashooterRect->hide();
    else
        snowpeashooterRect->show();

    //Chomper countdown
    if(chomperTimer->remainingTime() == -1) //timer stopped
        chomperRect->hide();
    else
        chomperRect->show();

    //Potatomine countdown
    if(potatomineTimer->remainingTime() == -1) //timer stopped
        potatomineRect->hide();
    else
        potatomineRect->show();
}

void GameScreen::peashooterCountdown()
{
    peashooterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    peashooterTimer->stop();
}

void GameScreen::sunflowerCountdown()
{
    sunflowerCard->setFlag(QGraphicsItem::ItemIsSelectable);
    sunflowerTimer->stop();

}

void GameScreen::cherrybombCountdown()
{
    cherrybombCard->setFlag(QGraphicsItem::ItemIsSelectable);
    cherrybombTimer->stop();
}

void GameScreen::walnutCountdown()
{
    walnutCard->setFlag(QGraphicsItem::ItemIsSelectable);
    walnutTimer->stop();
}

void GameScreen::repeaterCountdown()
{
    repeaterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    repeaterTimer->stop();
}

void GameScreen::chomperCountdown()
{
    chomperCard->setFlag(QGraphicsItem::ItemIsSelectable);
    chomperTimer->stop();
}

void GameScreen::snowpeashooterCountdown()
{
    snowpeashooterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    snowpeashooterTimer->stop();
}

void GameScreen::potatomineCountdown()
{
    potatomineCard->setFlag(QGraphicsItem::ItemIsSelectable);
    potatomineTimer->stop();
}


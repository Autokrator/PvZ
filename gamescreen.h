#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QCloseEvent>
#include <QMessageBox>
#include "gamehud.h"
#include <vector>
#include <QTimer>
#include "peashooter.h"
#include "sunflower.h"
#include "walnut.h"
#include "cherrybomb.h"
#include "chomper.h"
#include "repeater.h"
#include "potatomine.h"
#include "regularzombie.h"
#include "coneheadzombie.h"
#include "newspaperzombie.h"
#include "bucketheadzombie.h"
#include "flagzombie.h"
#include "lawnmower.h"

class GameScreen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();
    //Sets the player info for the gamehud class to display
    void setPlayerInfo(QString name,QString level);
private:
    //Holds the basic properties for a lawn piece
    struct lawnPiece{
        int topX, topY, botX, botY;
    };
    //Holds the the 45 lawnpieces (struct) that make up the lawn
    std::vector< std::vector<lawnPiece> > lawnVector;


private:
    QGraphicsScene *scene; //Game scene, holds all items that make the game
    QTimer *timer; //Main timer that advances all QGraphicItems in the scene

    QTimer *sunSpawnTimer; //Used to trigger a sun spawn
    const int sunSpawnInterval; //The interval between each sun spawn
    Sun *sun; //Used to make a new sun object

    GameHud *Hud; //Used to make a hud object to display dynamic informatio
    QGraphicsPixmapItem *resetButton; //used to restart given level
    QCursor *mouseCursor; //Used to change cursor throughout various game scenarios
    int mouseState; /*Used to indicate plant selection
                                 0 = default, 1 = peashooter, 2 = sunflower... 8*/
    void closeEvent(QCloseEvent *event); //Custom function for when window is closed (Quit button)
    void mousePressEvent(QMouseEvent *e); //Custom function for mouse click events
    void mouseMoveEvent(QMouseEvent *e); //Custom function for mouse movement
    void addPlant(int m_x, int m_y); //Takes care of planting on the lawn
    void setDefaultCursor(); //Sets the mouse to a default cursor

    //Plant selection cards used to know which plant is selected or can be selected
    //QGraphicsRect Item that cover corresponding card while seeding timer is counting down
    QGraphicsPixmapItem *peashooterCard;        QGraphicsRectItem *peashooterRect;
    QGraphicsPixmapItem *sunflowerCard;         QGraphicsRectItem *sunflowerRect;
    QGraphicsPixmapItem *cherrybombCard;        QGraphicsRectItem *cherrybombRect;
    QGraphicsPixmapItem *walnutCard;            QGraphicsRectItem *walnutRect;
    QGraphicsPixmapItem *repeaterCard;          QGraphicsRectItem *repeaterRect;
    QGraphicsPixmapItem *chomperCard;           QGraphicsRectItem *chomperRect;
    QGraphicsPixmapItem *snowpeashooterCard;    QGraphicsRectItem *snowpeashooterRect;
    QGraphicsPixmapItem *potatomineCard;        QGraphicsRectItem *potatomineRect;

    //Timers used express each plant's post seeding period
    QTimer *peashooterTimer;
    QTimer *sunflowerTimer;
    QTimer *cherrybombTimer;
    QTimer *walnutTimer;
    QTimer *repeaterTimer;
    QTimer *chomperTimer;
    QTimer *snowpeashooterTimer;
    QTimer *potatomineTimer;

    //Level functions and members
    void loadLevel();           //Loads the lawn tile information for current level
                                   //Loads triggers zombie sequence for level
    QStringList zombieSequence; //Sequence information for current level
    int activeRows;                   //Number of active rows for current level
    double startTime;           //Time until first zombie spawn (in ms)
    double startingInterval;    //Time till second zombie spawn
    double intervalDecrement;   //The value by which the the starting interval is lowered
                                // for each successive zombie
    QTimer *spawnFirstZombie; //Used to spawn first zombie of the level
    QTimer *spawnNextZombie; //Used to spawn consequent zombies
    double zombieSquenceTime; //decremented each time a zombie is spawned
    bool lastZombieSpawned; //used to tell continous monitoring slot "checkSunPoints()" to
                            // also monitor Zombie::zombiesAlive so when it is 0, level can end
signals:
    void showMainWindow(); //Signals to show mainwindow (menu)
    void deleteGameWindow(); //Signals the mainwindow to delte gameWindow object
    void levelWin(bool);

private slots:
    void spawnSun(); //Connected to sunSpawnTimer, used to spawn new suns
    void checkSunPoints(); //Check sunpoints and adjusts plant selection cards accordingly

    //Seeding timer slots
    void peashooterCountdown();
    void sunflowerCountdown();
    void cherrybombCountdown();
    void walnutCountdown();
    void repeaterCountdown();
    void chomperCountdown();
    void snowpeashooterCountdown();
    void potatomineCountdown();

    //Zombie spawning slots
    void startZombieSpawning();
    void spawnZombie();

};

#endif // GAMESCREEN_H

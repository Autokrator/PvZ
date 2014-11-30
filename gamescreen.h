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
#include "regularzombie.h"

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
        bool isPlantable;
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

    GameHud *Hud; //Used to make a hud object to display dynamic information
    QString playerName; //Holds the current player information
    QString playerLevel; //Holds the current level information
    QCursor *mouseCursor; //Used to change cursor throughout various game scenarios
    int mouseState; /*Used to indicate plant selection
                                 0 = default, 1 = peashooter, 2 = sunflower... 8*/
    void closeEvent(QCloseEvent *event); //Custom function for when window is closed (Quit button)
    void mousePressEvent(QMouseEvent *e); //Custom function for mouse click events
    void addPlant(QMouseEvent *event); //Takes care of planting on the lawn
    void setDefaultCursor(); //Sets the mouse to a default cursor

    //Plant selection cards used to know which plant is selected or can be selected
    QGraphicsPixmapItem *peashooterCard;
    QGraphicsPixmapItem *sunflowerCard;
    QGraphicsPixmapItem *cherrybombCard;
    QGraphicsPixmapItem *walnutCard;
    QGraphicsPixmapItem *repeaterCard;
    QGraphicsPixmapItem *chomperCard;
    QGraphicsPixmapItem *snowpeashooterCard;
    QGraphicsPixmapItem *potatomineCard;

signals:
    void showMainWindow(); //Signals to show mainwindow (menu)
    void deleteGameWindow(); //Signals the mainwindow to delte gameWindow object

private slots:
    void spawnSun(); //Connected to sunSpawnTimer, used to spawn new suns

};

#endif // GAMESCREEN_H

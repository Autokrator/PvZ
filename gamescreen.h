#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QCloseEvent>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "gamehud.h"
#include <vector>
#include <QTimer>

class GameScreen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();
    void setPlayerInfo(QString name,QString level);
private:
    struct lawnPiece{
        bool isPlantable;
        int topX, topY, botX, botY;
    };

private:
    int sunPoints;
    void closeEvent(QCloseEvent *event);
    void displaySunPoints() const;
    QGraphicsScene *scene;
    QCursor *mouseCursor;
    std::vector< std::vector<lawnPiece> > lawnVector;
    QTimer *timer;
    QTimer *sunSpawnTimer;
    const int sunSpawnInterval;
    QTimer *destroySunTimer;
    QTimer *scoreTimer;
    Sun *light1;
    GameHud *Hud;
    QString playerName;
    QString playerLevel;
    int mouseState;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void addPlant(QMouseEvent *event);
    void setDefaultCursor();
    QGraphicsPixmapItem *peashooterCard;
    QGraphicsPixmapItem *sunflowerCard;
    QGraphicsPixmapItem *cherrybombCard;
    QGraphicsPixmapItem *walnutCard;
    QGraphicsPixmapItem *repeaterCard;
    QGraphicsPixmapItem *chomperCard;
    QGraphicsPixmapItem *snowpeashooterCard;
    QGraphicsPixmapItem *potatomineCard;


signals:
    void showMainWindow();
    void deleteGameWindow();

private slots:
    void spawnSun();

};

#endif // GAMESCREEN_H

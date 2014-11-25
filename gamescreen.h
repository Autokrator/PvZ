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
    int sunPoints;
    void closeEvent(QCloseEvent *event);
    void displaySunPoints() const;
    QGraphicsScene *scene;
    QCursor *mouseCursor;
    std::vector<Sun *> lights;
    QTimer *timer;
    QTimer *sunSpawnTimer;
    QTimer *scoreTimer;
    Sun *light1;
    GameHud *Hud;
    QGraphicsTextItem *sunPointsText;
    QString playerName;
    QString playerLevel;

signals:
    void showMainWindow();
    void deleteGameWindow();

private slots:
    void spawnSun();

};

#endif // GAMESCREEN_H

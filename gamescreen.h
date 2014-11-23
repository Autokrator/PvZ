#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QCloseEvent>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "sun.h"
#include <vector>
#include <QTimer>

class GameScreen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();
private:
    int sunPoints;
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void displaySunPoints() const;
    QGraphicsScene *scene;
    QCursor *mouseCursor;
    std::vector<Sun *> lights;
    QTimer *timer;
    QTimer *scoreTimer;
    Sun *light1;
    QGraphicsTextItem *sunPointsText;

signals:
    void showMainWindow();
    void deleteGameWindow();

private slots:
    void updateSunPoints();

};

#endif // GAMESCREEN_H

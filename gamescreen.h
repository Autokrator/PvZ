#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QCloseEvent>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>

class GameScreen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameScreen(QWidget *parent = 0);
    ~GameScreen();
private:
    void closeEvent(QCloseEvent *event);
    QGraphicsScene *scene;

signals:
    void showMainWindow();
    void deleteGameWindow();

public slots:

};

#endif // GAMESCREEN_H

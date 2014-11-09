#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newUserButton_clicked();

    void on_existUserButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
    GameWindow *gameUi; //game window for when to start the game
    QString userName;  //holds user name information
    QString userLevel; //holds level information for active user
    QString getStatusMessage(); //gets the status message
};

#endif // MAINWINDOW_H

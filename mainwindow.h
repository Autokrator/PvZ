#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include "newuserdialog.h"
#include "existinguserdialog.h"

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

    void deleteGameWindow(); //calls the destructor of game window object

    void deleteNewUserDialog(); //calls the destructor of new user dialog object

    void changeButtonState(bool); //enables and disables buttons

private:
    Ui::MainWindow *ui;
    GameWindow *gameUi; //game window for when to start the game
    NewUserDialog *newUserUi;
    QString userName;  //holds user name information
    QString userLevel; //holds level information for active user
    QString getStatusMessage(); //gets the status message
};

#endif // MAINWINDOW_H
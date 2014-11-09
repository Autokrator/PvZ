#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void setStatusMessage(const QString &message);
private:
    Ui::GameWindow *ui;
    void closeEvent(QCloseEvent *event);

signals:
    void showMainWindow(bool);

};

#endif // GAMEWINDOW_H

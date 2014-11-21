#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QTextStream>
#include <QFile>
#include <QStringList>

namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QWidget *parent = 0);
    ~NewUserDialog();
    QString getUserName() const;

private slots:
    void on_okButton_clicked();

private:
    Ui::NewUserDialog *ui;
    QString inputUserName; //holds valid username
    QStringList playerList; //holds list of players read from file
    void writeToPlayerFile(QString file_name); //updates player file after new player
    void readFromPlayerFile(QString file_name); //remembers previous players in file
    void closeEvent(QCloseEvent *event);


signals:
    void changeButtonState(bool);
    void deleteNewUserDialog();
};

#endif // NEWUSERDIALOG_H

#ifndef EXISTINGUSERDIALOG_H
#define EXISTINGUSERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>

namespace Ui {
class ExistingUserDialog;
}

class ExistingUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExistingUserDialog(QWidget *parent = 0);
    ~ExistingUserDialog();
    QString getUsername() const; //returns username to mainwindow
    QString getLevel() const; //returns level to mainwindow

private slots:
    void on_deleteButton_clicked();

    void on_selectButton_clicked();

    void on_deleteAllButton_clicked();

private:
    Ui::ExistingUserDialog *ui;
    QStringList playerList;
    QString inputUser; //holds valid username
    QString userLevel; //holds level for a user
    void readFromPlayerFile();
    void closeEvent(QCloseEvent *event);

signals:
    void changeButtonState(bool);
    void deleteExistingUserDialog();
};

#endif // EXISTINGUSERDIALOG_H

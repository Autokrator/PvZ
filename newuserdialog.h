#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QWidget *parent = 0);
    ~NewUserDialog();
    QString getUserName();

private slots:
    void on_okButton_clicked();

private:
    Ui::NewUserDialog *ui;
    QString inputUserName;
    void closeEvent(QCloseEvent *event);


signals:
    void showMainWindow(bool);
    void deleteNewUserDialog(bool);
};

#endif // NEWUSERDIALOG_H

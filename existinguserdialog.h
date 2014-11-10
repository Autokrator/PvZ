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

private slots:
    void on_deleteButton_clicked();

    void on_selectButton_clicked();

    void on_deleteAllButton_clicked();

private:
    Ui::ExistingUserDialog *ui;
    QStringList playerList;
    void readFromPlayerFile(QString file_name);
};

#endif // EXISTINGUSERDIALOG_H

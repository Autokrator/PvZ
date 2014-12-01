#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

bool isLevelFileValid();
void checkPlayerFile();

int main(int argc, char *argv[])
{

    //Construct application
    QApplication a(argc, argv);
    MainWindow w;

    checkPlayerFile();

    if(isLevelFileValid())
        w.show(); //displays mainwindow

    return a.exec();
}

bool isLevelFileValid()
{
    QString file_name = "/Users/Parth/Documents/QT/RvZ/rvz_levels.csv";
    QFile level_file(file_name);

    //Displays warning if file is not readable and exits program
    if(!level_file.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        QMessageBox::warning(0,"Cannot execute RvZ","rvz_levels.csv does not exist or is unreadable!",
                             QMessageBox::Ok);
        return 0;
    }
    else
        return 1;
}

void checkPlayerFile()
{
    QString file_name = "/Users/Parth/Documents/QT/RvZ/rvz_players.csv";
    QFile user_file(file_name);

    //Displays warning if file is not readable and exits program
    if(!user_file.open(QIODevice::ReadWrite|QIODevice::Text))
        return;
    else
    {
        QTextStream verifier(&user_file);
        while(!verifier.atEnd())
        {
            //Creates temporary text manipulation objects
            QStringList temp;
            QByteArray name_array,level_array;
            int level;

            //Splits line and saves the level information as char array
            temp = verifier.readLine().split(':');
            name_array = temp.at(1).toLatin1();
            level_array = temp.at(2).toLatin1();
            level = temp.at(2).toInt();

            //Checking if level is valid
            for(int i = 0; i < level_array.length(); i++)
            {
                //Checks if level is numeric and between 0 and 100
                if(!(level_array.at(i) > 47 && level_array.at(i) < 58) || (level < 0 && level > 100))
                {
                    //Displays warning if level is invalid
                    QMessageBox::warning(0,"User file discarded","Invalid level information! rvz_players.csv will be discarded!",
                                         QMessageBox::Ok);
                    user_file.resize(0); //clears file
                    goto close; //goes to close flag
                }
            }

            //Checking if name is valid
            for(int i = 0; i < name_array.length(); i++)
            {
                //Checks if level is numeric and between 0 and 100
                if(name_array.length() > 10)
                {
                    //Displays warning if level is invalid
                    QMessageBox::warning(0,"User file discarded","Invalid user information! rvz_players.csv will be discarded!",
                                         QMessageBox::Ok);
                    user_file.resize(0); //clears file
                    goto close; //goes to close flag
                }
            }
        }

    close: //closes file
    user_file.close();

    }
}

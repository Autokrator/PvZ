#include "mainwindow.h"
#include <QApplication>

bool isLevelFileValid();

int main(int argc, char *argv[])
{
    //Construct application
    QApplication a(argc, argv);
    MainWindow w;

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
    {
        QTextStream verifier(&level_file);
        while(!verifier.atEnd())
        {
            //Creates temporary text manipulation objects
            QStringList temp;
            QByteArray level_array;

            //Splits line and saves the level information as char array
            temp = verifier.readLine().split(':');
            level_array = temp.at(0).toLatin1();

            //Checking if level is valid
            for(int i = 0; i < level_array.length(); i++)
            {
                //Checks if level is numeric and between 0 and 100
                if(!(level_array.at(i) > 47 && level_array.at(i) < 58) || temp.at(0).toInt() > 100 ||
                        temp.at(0).toInt() < 0)
                {
                    //Displays warning if level is invalid
                    QMessageBox::warning(0,"Level file discarded","Invalid level information! rvz_levels.csv will be discarded!",
                                         QMessageBox::Ok);
                    level_file.resize(0); //clears file
                    goto close; //goes to close flag
                }
            }
        }

        close: //closes file
        level_file.close();
        return 1;
    }
}

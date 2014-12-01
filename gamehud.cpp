#include "gamehud.h"
#include <QFontDatabase>

GameHud::GameHud()
{
    //Default user info
    user = "Guest";
    level = "1";

    //Adds font to QtFontDataBase
    QFontDatabase::addApplicationFont(":/Font/handWritingFont");
}

GameHud::~GameHud()
{

}



QRectF GameHud::boundingRect() const
{
    return QRectF(0,0,1000,160);
}

void GameHud::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Sets up the font
    QFont font;
    font.setPointSize(20);
    font.setFamily("gunny rewritten");
    painter->setFont(font);

    //Draws the user and level information to the screen
    painter->drawText(140,55,user);
    painter->drawText(140,75,"Level: " + level);

    //Draws the current number of sun points to screen
    font.setPointSizeF(40);
    painter->setFont(font);
    painter->drawText(140,115,QString::number(Sun::getSunPoints()));

}

void GameHud::advance(int phase)
{
    if(!phase)
    {
        update();
        return;
    }
}


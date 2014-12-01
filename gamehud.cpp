#include "gamehud.h"
#include <QFontDatabase>

GameHud::GameHud()
{
    //Default user info
    user = "Guest";
    level = "1";

    //Adds font to QtFontDataBase
    QFontDatabase::addApplicationFont(":/Font/handWritingFont");

    //Adds all qgraphicsrects to the scene
 //   peashooterRect = new QGraphicsRectItem(peashooterCard->boundingRect());
//    sunflowerRect = new QGraphicsRectItem(peashooterCard->boundingRect());
//    cherrybombRect = new QGraphicsRectItem(peashooterCard->boundingRect());
//    walnutRect = new QGraphicsRectItem(peashooterCard->boundingRect());
//    chomperRect = new QGraphicsRectItem(peashooterCard->boundingRect());
//    repeaterRect = new QGraphicsRectItem(peashooterCard->boundingRect());
//    potatomineRect = new QGraphicsRectItem(peashooterCard->boundingRect());
//    snowpeashooterRect = new QGraphicsRectItem(peashooterCard->boundingRect());


}

GameHud::~GameHud()
{
//    delete peashooterRect;
//    delete sunflowerRect;
//    delete cherrybombRect;
//    delete walnutRect;
//    delete chomperRect;
//    delete repeaterRect;
//    delete potatomineRect;
//    delete snowpeashooterRect;
}

void GameHud::setPlantCards(QGraphicsPixmapItem *peashooter_card, QGraphicsPixmapItem *sunflower_card,
                            QGraphicsPixmapItem *cherrybomb_card, QGraphicsPixmapItem *walnut_card,
                            QGraphicsPixmapItem *repeater_card, QGraphicsPixmapItem *chomper_card,
                            QGraphicsPixmapItem *snowpeashooter_card, QGraphicsPixmapItem *potatomine_card)
{
    //Copying address location of each pointer to coreesponding QGraphicsPixmapItem
    peashooterCard = peashooter_card;
    sunflowerCard = sunflower_card;
    cherrybombCard = cherrybomb_card;
    walnutCard = walnut_card;
    repeaterCard = repeater_card;
    chomperCard = chomper_card;
    snowpeashooterCard = snowpeashooter_card;
    potatomineCard = potatomine_card;
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

void GameHud::cardOverlay()
{

}

#include "gamehud.h"
#include <QFontDatabase>

int GameHud::mouseState = 1;

GameHud::GameHud()
{
    //Default user info
    user = "Guest";
    level = "1";

    //Adds font to QtFontDataBase
    QFontDatabase::addApplicationFont(":/Font/handWritingFont");

    //Creates background for updating hud elements
    QPixmap score_Background_note(":/Images/scoreBackgroundNote");
    QPixmap score_Background(":/Images/scoreBackground");
    scene()->addPixmap(score_Background_note);
    scene()->addPixmap(score_Background)->setPos(score_Background.width(),0);
    scene()->addPixmap(score_Background)->setPos(score_Background.width()*2,0);

    /*Adding clickable plant icons*/

    //Aligning to y-point
    int y_alignment = 50;

    //Loading pixmap of each card
    peashooterCard = new QGraphicsPixmapItem(QPixmap(":/Images/peashooterCard"));
    sunflowerCard = new QGraphicsPixmapItem(QPixmap(":/Images/sunflowerCard"));
    walnutCard = new QGraphicsPixmapItem(QPixmap(":/Images/walnutCard"));
    cherrybombCard = new QGraphicsPixmapItem(QPixmap(":/Images/cherrybombCard"));

    //Setting their positions, making them selectable and adding them to the scene
    //peashooter
    peashooterCard->setPos(score_Background.width()+40,y_alignment);
    peashooterCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene()->addItem(peashooterCard);

    //sunflower Card
    sunflowerCard->setPos(peashooterCard->x()+50,y_alignment);
    sunflowerCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene()->addItem(sunflowerCard);

    //walnut Card
    walnutCard->setPos(sunflowerCard->x()+50,y_alignment);
    walnutCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene()->addItem(walnutCard);

    //cherrybomb Card
    cherrybombCard->setPos(walnutCard->x()+50,y_alignment);
    cherrybombCard->setFlag(QGraphicsItem::ItemIsSelectable);
    scene()->addItem(cherrybombCard);


    /*End of adding selectable cards to scene*/
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

    if(mouseState == 0)
        resetCardOpacities();
}

void GameHud::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mousePressEvent(e);

    //Checks to see which card(if any) is selected when mouse is pressed
    if(peashooterCard->isSelected() && Sun::getSunPoints() >= 100)
    {
        mouseState = 1; //Gives permission to plant peashooter

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/peashooterGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        peashooterCard->setOpacity(1);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        cherrybombCard->setOpacity(0.5);

        //Resets selection
        peashooterCard->setSelected(false);
    }
    else if(sunflowerCard->isSelected() && Sun::getSunPoints() >= 50)
    {
        mouseState = 2; //Gives permission to plant sunflower

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/sunflowerGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        sunflowerCard->setOpacity(1);
        peashooterCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
        cherrybombCard->setOpacity(0.5);

        //Resets selection
        sunflowerCard->setSelected(false);
    }
    else if(walnutCard->isSelected() && Sun::getSunPoints() >= 50)
    {
        mouseState = 3; //Gives permission to plant walnut

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/walnutGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        walnutCard->setOpacity(1);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        cherrybombCard->setOpacity(0.5);
    }
    else if(cherrybombCard->isSelected() && Sun::getSunPoints() >= 150)
    {
        mouseState = 4; //Gives permission to plant cherrybomb

        //Changes mouse cursor to reflect clicked plant
        delete mouseCursor;
        mouseCursor = new QCursor(QPixmap(":/Images/cherrybombGray"));
        this->setCursor(*mouseCursor);

        //Decreases opacity of other cards to indicate selected one is active
        cherrybombCard->setOpacity(1);
        peashooterCard->setOpacity(0.5);
        sunflowerCard->setOpacity(0.5);
        walnutCard->setOpacity(0.5);
    }
}

void GameHud::resetCardOpacities()
{
    peashooterCard->setOpacity(1);
    sunflowerCard->setOpacity(1);
    walnutCard->setOpacity(1);
    cherrybombCard->setOpacity(1);
}


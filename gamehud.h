#ifndef GAMEHUD_H
#define GAMEHUD_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "sun.h"

class GameHud : public QGraphicsItem
{
public:
    GameHud();
    ~GameHud();
    QString user;
    QString level;
    void setPlantCards(QGraphicsPixmapItem *peashooter_card,
                       QGraphicsPixmapItem *sunflower_card,
                       QGraphicsPixmapItem *cherrybomb_card,
                       QGraphicsPixmapItem *walnut_card,
                       QGraphicsPixmapItem *repeater_card,
                       QGraphicsPixmapItem *chomper_card,
                       QGraphicsPixmapItem *snowpeashooter_card,
                       QGraphicsPixmapItem *potatomine_card);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);

    //Plant selection cards used to know which plant is selected or can be selected
    QGraphicsPixmapItem *peashooterCard;        QGraphicsRectItem *peashooterRect;
    QGraphicsPixmapItem *sunflowerCard;         QGraphicsRectItem *sunflowerRect;
    QGraphicsPixmapItem *cherrybombCard;        QGraphicsRectItem *cherrybombRect;
    QGraphicsPixmapItem *walnutCard;            QGraphicsRectItem *walnutRect;
    QGraphicsPixmapItem *repeaterCard;          QGraphicsRectItem *repeaterRect;
    QGraphicsPixmapItem *chomperCard;           QGraphicsRectItem *chomperRect;
    QGraphicsPixmapItem *snowpeashooterCard;    QGraphicsRectItem *snowpeashooterRect;
    QGraphicsPixmapItem *potatomineCard;        QGraphicsRectItem *potatomineRect;

    void cardOverlay(); //displays dark zones over unplantable plants
};

#endif // GAMEHUD_H

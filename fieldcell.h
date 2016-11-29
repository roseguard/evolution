#ifndef FIELDCELL_H
#define FIELDCELL_H

#include <QGraphicsPixmapItem>

#include "defines.h"
#include "lifecell.h"

class LifeCell;

class FieldCell : public QGraphicsPixmapItem
{
public:
    FieldCell(QPixmap pix, QPixmap *foodPix, QPixmap *poisonPix, QPixmap *wallPix, bool isWall);
    bool    isWall();

    void    putFood();
    void    removeFood();
    bool    hasFood();

    void    putLife(LifeCell * cell);
    void    removeLife();
    bool    hasLife();

    void    putPoison();
    void    poisonToFood();
    bool    hasPoison();

    QPoint  getFieldPos();
    void    setFieldPos(QPoint pos);

    QGraphicsPixmapItem *paramsInfo;
public:
    QPixmap *_foodPix, *_poisonPix, *_wallPix;
private:
    quint8      _wall;
    bool        _food;
    bool        _poison;
    LifeCell    *_life;
    bool        _isLife;
    QPoint      _fieldPos;
};

#endif // FIELDCELL_H

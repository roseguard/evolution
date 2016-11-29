#include "fieldcell.h"
#include <time.h>

FieldCell::FieldCell(QPixmap pix, QPixmap *foodPix, QPixmap *poisonPix, QPixmap *wallPix, bool isWall) : QGraphicsPixmapItem(pix)
{
    _wall = isWall;
    _poison = false;
    _food = false;
    _life = Q_NULLPTR;
    _isLife = false;
    _fieldPos = QPoint(0,0);
    _foodPix = foodPix;
    _poisonPix = poisonPix;
    paramsInfo = new QGraphicsPixmapItem(this);
    if(isWall)
        paramsInfo->setPixmap(*wallPix);
}

bool FieldCell::isWall()
{
    return _wall;
}

void FieldCell::putFood()
{
    paramsInfo->setPixmap(*_foodPix);
    paramsInfo->show();
    _food = true;
    _poison = false;
}

void FieldCell::removeFood()
{
    paramsInfo->hide();
    _food = false;
}

bool FieldCell::hasFood()
{
    return _food;
}

void FieldCell::putLife(LifeCell *cell)
{
    if(_poison)
    {
        cell->killCell();
        _poison = false;
        paramsInfo->hide();
        cell->_viewer->loosers.append(cell);
        return;
    }
    else if(_food)
    {
        cell->feedCell();
        _food = false;
        paramsInfo->hide();
    }
    _life = cell;
    _isLife = true;
}

void FieldCell::removeLife()
{
    _life = Q_NULLPTR;
    _isLife = false;
}

bool FieldCell::hasLife()
{
    return _isLife;
}

void FieldCell::putPoison()
{
    _food = false;
    paramsInfo->setPixmap(*_poisonPix);
    paramsInfo->show();
    _poison = true;
}

bool FieldCell::hasPoison()
{
    return _poison;
}

void FieldCell::poisonToFood()
{
    if(_poison)
    {
        _poison = false;
        paramsInfo->setPixmap(*_foodPix);
        _food = true;
    }
}

QPoint FieldCell::getFieldPos()
{
    return _fieldPos;
}

void FieldCell::setFieldPos(QPoint pos)
{
    _fieldPos = pos;
}

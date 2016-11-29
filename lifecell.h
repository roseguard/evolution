#ifndef LIFECELL_H
#define LIFECELL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

#include "defines.h"
#include "evolution.h"

#define private public

class Evolution;

class LifeCell : public QGraphicsPixmapItem
{
public:
    LifeCell(QPixmap pix, QPoint fieldPos, quint8 DNA[], Evolution *viewer);
    LifeCell(LifeCell* beforeAge);

private:
    QGraphicsTextItem   *_healthItem;
    quint8              _health;
    QPoint              _fieldPos;

    bool                _isDead;


    quint8              codePoint=0;
    quint8              codeSteps=0;
    quint8              toNextCommand=1;

    quint8              turnedSide = 3;
public:

    QGraphicsTextItem   *_DNAInfo;
    quint8               _DNA[maxMemory];
    Evolution           *_viewer;
    quint32             survived = 0;
public:
    void    feedCell();
    void    killCell();
    bool    isDead();

    void    decrementHealth();
    void    incrementHealth();
    quint8  getHealth();

    QPoint  getFieldPos();
    void    moveToFieldPos(QPoint newPos);

    bool    runCode();
    void    move(QString way);
    int     check(QString way);
    void    changePoison(QString way);

    void    changeTurning();
    void    makeMutations();

    void mousePressEvent(QMouseEvent *event);
};

#endif // LIFECELL_H

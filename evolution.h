#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <QWidget>
#include <QDesktopWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include "time.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include "defines.h"
#include "fieldcell.h"
#include "lifecell.h"

class LifeCell;
class FieldCell;

class Evolution : public QGraphicsView
{
    Q_OBJECT

public:
    Evolution(QWidget *parent = 0);
    ~Evolution();

    QDesktopWidget      desk;

    QGraphicsScene      *scene;
    QGraphicsPixmapItem *background;
    FieldCell           *fields[fieldSizeX][fieldSizeY];
    QVector<LifeCell*>  lifes;
    QVector<LifeCell*>  loosers;
    QVector<LifeCell*>  newAge;
    QTimer              *stepsTimer;

    int                 forTest = 0;
    quint8              speed = 10;

    QSqlDatabase    *db;
    QSqlQuery       *query;

    int pixW, pixH;
    bool MayStep = false;
    QGraphicsTextItem   *speedItem;

    QPixmap *foods, *poisons, *walls;

public:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void newStep();
    void nextAge();
};

#endif // EVOLUTION_H

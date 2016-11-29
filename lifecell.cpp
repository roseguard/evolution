#include "lifecell.h"
#include <time.h>
#include <QDebug>

LifeCell::LifeCell(QPixmap pix, QPoint fieldPos, quint8 DNA[maxMemory], Evolution *viewer) : QGraphicsPixmapItem(pix)
{
    _health = startHealth;
    _healthItem = new QGraphicsTextItem(QString::number(_health), this);
    _fieldPos = fieldPos;

    for(int i = 0; i < maxMemory; i++)
    {
        _DNA[i] = DNA[i];
    }

    _isDead = false;
    _viewer = viewer;
    _DNAInfo = new QGraphicsTextItem(this);
}

LifeCell::LifeCell(LifeCell *beforeAge) : QGraphicsPixmapItem(beforeAge->pixmap())
{
    qsrand(time(NULL));
    _health = startHealth;
    _healthItem = new QGraphicsTextItem(QString::number(_health), this);
    _fieldPos = beforeAge->_fieldPos;

    for(int i = 0; i < maxMemory; i++)
    {
        _DNA[i] = beforeAge->_DNA[i];
    }


    _isDead = false;
    _viewer = beforeAge->_viewer;
    _DNAInfo = new QGraphicsTextItem(this);
}

bool LifeCell::runCode()
{
    survived++;
    codePoint = 0;
    codeSteps = 0;
    while(codeSteps<maxCodeSteps)
    {
        if(codePoint==maxMemory)
            codePoint = 0;
        if(_DNA[codePoint]<64)
        {
            toNextCommand = 1;
            codePoint = _DNA[codePoint];
            codeSteps++;
            continue;
        }
        switch(_DNA[codePoint])
        {
        case(moveRight):    move("right"); codePoint+=toNextCommand; codeSteps = maxCodeSteps ;  break;
        case(moveLeft):     move("left");  codePoint+=toNextCommand; codeSteps = maxCodeSteps ;  break;
        case(moveUp):       move("up");    codePoint+=toNextCommand; codeSteps = maxCodeSteps ;  break;
        case(moveDown):     move("down");  codePoint+=toNextCommand; codeSteps = maxCodeSteps ;  break;

        case(checkRight):   codePoint+=check("right"); codeSteps+=1; break;
        case(checkLeft):    codePoint+=check("left");  codeSteps+=1; break;
        case(checkUp):      codePoint+=check("up");    codeSteps+=1; break;
        case(checkDown):    codePoint+=check("down");  codeSteps+=1; break;

        case(poisonRight):  changePoison("right"); codePoint+=toNextCommand; codeSteps+=1; break;
        case(poisonLeft):   changePoison("left");  codePoint+=toNextCommand; codeSteps+=1; break;
        case(poisonUp):     changePoison("up");    codePoint+=toNextCommand; codeSteps+=1; break;
        case(poisonDown):   changePoison("down");  codePoint+=toNextCommand; codeSteps+=1; break;
        }
        if(codePoint>=commandSize)
            codePoint-=commandSize;
    }
    return true;
}

void LifeCell::move(QString way)
{
    int tempX = _fieldPos.x(), tempY = _fieldPos.y();
    if(way=="right")        // відбираємо координати куди буде направлено метод
        tempX++;
    else if(way=="left")
        tempX--;
    else if(way=="up")
        tempY--;
    else if(way=="down")
        tempY++;

    if((tempX < 0) || (tempX >= fieldSizeX))          //перевірка чи не виходить за поле це поле
        return;
    if((tempY < 0) || (tempY >= fieldSizeY))
        return;

    if(!_viewer->fields[tempX][tempY]->isWall() && !_viewer->fields[tempX][tempY]->hasLife())
    {
        setPos(_viewer->fields[tempX][tempY]->pos());
        _fieldPos = _viewer->fields[tempX][tempY]->getFieldPos();
        _viewer->fields[tempX][tempY]->putLife(this);
    }
}

int LifeCell::check(QString way)
{
    int tempX = _fieldPos.x(), tempY = _fieldPos.y();
    if(way=="right")        // відбираємо координати куди буде направлено метод
        tempX++;
    else if(way=="left")
        tempX--;
    else if(way=="up")
        tempY--;
    else if(way=="down")
        tempY++;

    if((tempX < 0) || (tempX >= fieldSizeX))          //перевірка чи не виходить за поле це поле
        return itsWall;
    if((tempY < 0) || (tempY >= fieldSizeY))
        return itsWall;


    if(_viewer->fields[tempX][tempY]->isWall())
    {
        toNextCommand = itsMax - itsWall + 1;
        return itsWall;
    }
    else if(_viewer->fields[tempX][tempY]->hasPoison())
    {
        toNextCommand = itsMax - itsPoison + 1;
        return itsPoison;
    }
    else if(_viewer->fields[tempX][tempY]->hasFood())
    {
        toNextCommand = itsMax - itsFood + 1;
        return itsFood;
    }
    else if(_viewer->fields[tempX][tempY]->hasLife())
    {
        toNextCommand = itsMax - itsCreature + 1;
        return itsCreature;
    }
    else
    {
        toNextCommand = itsMax - itsEmpty + 1;
        return itsEmpty;
    }
}

void LifeCell::changePoison(QString way)
{
    int tempX = _fieldPos.x(), tempY = _fieldPos.y();
    if(way=="right")        // відбираємо координати куди буде направлено метод
        tempX++;
    else if(way=="left")
        tempX--;
    else if(way=="up")
        tempY--;
    else if(way=="down")
        tempY++;

    if((tempX < 0) || (tempX >= fieldSizeX))          //перевірка чи не виходить за поле це поле
        return;
    if((tempY < 0) || (tempY >= fieldSizeY))
        return;

    if(_viewer->fields[tempX][tempY]->hasPoison())
    {
        _viewer->fields[tempX][tempY]->poisonToFood();
    }
}

bool LifeCell::isDead()
{
    return _isDead;
}

void LifeCell::feedCell()
{
    _health+=livesFromFood;
    _healthItem->setPlainText(QString::number(_health));
}

void LifeCell::killCell()
{
    _isDead = true;
    hide();
}

void LifeCell::decrementHealth()
{
    _health -= livesPerIteration;
    _healthItem->setPlainText(QString::number(_health));
}

void LifeCell::incrementHealth()
{
    _health += livesFromFood;
    _healthItem->setPlainText(QString::number(_health));
}

quint8 LifeCell::getHealth()
{
    return _health;
}

QPoint LifeCell::getFieldPos()
{
    return _fieldPos;
}

void LifeCell::moveToFieldPos(QPoint newPos)
{
    quint8 tempx = newPos.x() - _fieldPos.x();
    quint8 tempy = newPos.y() - _fieldPos.y();
    _fieldPos = newPos;
    moveBy(tempx*pixmap().width(), tempy*pixmap().height());
}

void LifeCell::mousePressEvent(QMouseEvent *event)
{
    QString datas;
    datas.append("<div style='background-color:#000000; color : green; '>");
    for(int i = 1; i < maxMemory+1; i++)
    {
        datas.append(" | " + QString::number(_DNA[i-1]));
        if(_DNA[i-1]<10)
            datas.append("_");
        if(i%16==0)
        {
            datas.append("<br>");
        }
    }
    datas.push_back("</div></div>");
    _DNAInfo->setHtml(datas);
    _DNAInfo->show();
}

void LifeCell::makeMutations()
{
    _DNA[qrand()%maxMemory] = qrand()%commandSize;
}

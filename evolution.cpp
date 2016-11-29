#include "evolution.h"
#include <QDir>
#include <QSqlError>

Evolution::Evolution(QWidget *parent)
    : QGraphicsView(parent)
{
    qDebug() << QDir::currentPath();
    qsrand(time(NULL));
    thread()->msleep(1000);
    scene = new QGraphicsScene(this);
    setScene(scene);

    poisons = new QPixmap(QPixmap(":img/poison.png").scaled(desk.width()/fieldSizeX*0.80, desk.height()/fieldSizeY*0.80));
    foods = new QPixmap(QPixmap(":img/food.png").scaled(desk.width()/fieldSizeX*0.80, desk.height()/fieldSizeY*0.80));
    walls = new QPixmap(QPixmap(":img/wall.jpg").scaled(desk.width()/fieldSizeX*0.80, desk.height()/fieldSizeY*0.80));
    QPixmap pix = QPixmap(":img/cell.jpg").scaled(desk.width()/fieldSizeX*0.95, desk.height()/fieldSizeY*0.95);

    background = new QGraphicsPixmapItem(QPixmap(":img/back.png").scaled(desk.width(), desk.height()));
    scene->addItem(background);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pixW = pix.width();
    pixH = pix.height();
    for(int x = 0; x < fieldSizeX; x++)
    {
        for(int y = 0; y < fieldSizeY; y++)
        {
            fields[x][y] = new FieldCell(pix, foods, poisons, walls, qrand()%100>wallsSeed);
            fields[x][y]->setPos(x*pixW, y*pixH);
            fields[x][y]->setFieldPos(QPoint(x,y));
            scene->addItem(fields[x][y]);
        }
    }
    int fieldX = 0, fieldY = 0;

    pix = QPixmap(":img/life.jpg").scaled(desk.width()/(fieldSizeX+10), desk.height()/(fieldSizeY+10));
    LifeCell *newLife;

    for(int i = 0; i < lifesAtStart; i++)
    {
        quint8 startDNA[maxMemory];
        for(int i = 0; i < maxMemory; i++)
        {
            startDNA[i] = qrand()%commandSize;
            while(startDNA[i]==i)
                startDNA[i] = qrand()%commandSize;
        }
        while(true)
        {
            fieldX = rand()%fieldSizeX;
            fieldY = rand()%fieldSizeY;
            if(!fields[fieldX][fieldY]->isWall() && !fields[fieldX][fieldY]->hasLife())
            {
                newLife = new LifeCell(pix, QPoint(fieldX, fieldY), startDNA, this);
                newLife->setPos(fieldX*pixW, fieldY*pixH);
                fields[fieldX][fieldY]->putLife(newLife);
                lifes.append(newLife);
                scene->addItem(newLife);
                break;
            }
        }
    }
    speedItem = new QGraphicsTextItem;
    speedItem->setHtml(("<div style='background-color:#000000; color : green; '>" + QString::number(speed) + "</div>"));
    speedItem->setPos((fieldSizeX+1)*fields[0][0]->pixmap().width(), 30);
    scene->addItem(speedItem);

//    newLife->_DNA[0] = 20;

//    newLife->_DNA[10] = 75;
//    newLife->_DNA[11] = 67;

//    newLife->_DNA[20] = 68;
//    newLife->_DNA[21] = 30;
//    newLife->_DNA[22] = 30;
//    newLife->_DNA[23] = 30;
//    newLife->_DNA[24] = 64;
//    newLife->_DNA[25] = 30;

//    newLife->_DNA[30] = 69;
//    newLife->_DNA[31] = 40;
//    newLife->_DNA[32] = 40;
//    newLife->_DNA[33] = 40;
//    newLife->_DNA[34] = 65;
//    newLife->_DNA[35] = 40;

//    newLife->_DNA[40] = 70;
//    newLife->_DNA[41] = 50;
//    newLife->_DNA[42] = 50;
//    newLife->_DNA[43] = 50;
//    newLife->_DNA[44] = 66;
//    newLife->_DNA[45] = 50;

//    newLife->_DNA[50] = 71;
//    newLife->_DNA[51] = 15;
//    newLife->_DNA[52] = 67;
//    newLife->_DNA[53] = 10;
//    newLife->_DNA[54] = 67;
//    newLife->_DNA[55] = 15;

    db = new QSqlDatabase;
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("./datas");
    db->open();
    query = new QSqlQuery(*db);
    if(db->tables().length()<1)
    {
        query->exec("CREATE TABLE evolution(age INT PRIMARY KEY, firstDNA VARCHAR, firstLifeTime INT,"
                    "secondDNA varchar, secondLifeTime INT,"
                    "thirdDNA VARCHAR, thirdLifeTime INT,"
                    "fourthDNA varchar, fourthLifeTime INT)");
    }
    else if(db->tables().first()=="evolution")
    {
        query->exec("select max(evolution.age), evolution.firstDNA, evolution.secondDNA, evolution.thirdDNA, evolution.fourthDNA from evolution;");
        while(query->next())
        {
            forTest = query->value(0).toInt();
            QStringList tempList0 = query->value(1).toString().split(" ");
            QStringList tempList1 = query->value(2).toString().split(" ");
            QStringList tempList2 = query->value(3).toString().split(" ");
            QStringList tempList3 = query->value(4).toString().split(" ");
            int intList[4][maxMemory];
            qDebug() << tempList1;
            for(int i = 0; i < maxMemory; i++)
            {
                intList[0][i] = QString(tempList0.at(i)).toInt();
                intList[1][i] = QString(tempList1.at(i)).toInt();
                intList[2][i] = QString(tempList2.at(i)).toInt();
                intList[3][i] = QString(tempList3.at(i)).toInt();
            }
            for(int i = 0; i < lifesAtStart; i++)
            {
                int temp = i%4;
                for(int j = 0; j < maxMemory; j++)
                {
                    lifes.at(i)->_DNA[j] = intList[temp][j];
                }
            }
        }
    }

    stepsTimer = new QTimer(this);
}

Evolution::~Evolution()
{
    for(int x = 0; x < fieldSizeX; x++)
    {
        for(int y = 0; y < fieldSizeY; y++)
        {
            delete fields[x][y];
        }
    }
    for(int i = 0; i < lifes.length(); i++)
        delete lifes.at(i);
    delete foods;
    delete poisons;
    delete walls;
    delete speedItem;

    db->close();
    delete db;
    delete query;
}

void Evolution::newStep()
{
    if(loosers.length()==lifes.length())
    {
        nextAge();
    }

    if(qrand()%100>50)
    {
        int tempX = qrand()%fieldSizeX;
        int tempY = qrand()%fieldSizeY;
        if(!fields[tempX][tempY]->isWall() && !fields[tempX][tempY]->hasLife())
            fields[tempX][tempY]->putFood();
    }
    if(qrand()%100>80)
    {
        int tempX = qrand()%fieldSizeX;
        int tempY = qrand()%fieldSizeY;
        if(!fields[tempX][tempY]->isWall() && !fields[tempX][tempY]->hasLife())
            fields[tempX][tempY]->putPoison();
    }

    for(int i = 0; i < lifes.length(); i++)
    {
        if(!lifes.at(i)->isDead())
        {
            lifes.at(i)->runCode();
            lifes.at(i)->decrementHealth();
            if(lifes.at(i)->getHealth()<=0)
            {
                lifes.at(i)->killCell();
                loosers.append(lifes.at(i));
            }
        }
    }

    if(MayStep)
        stepsTimer->singleShot(speed ,this, SLOT(newStep()));
}

void Evolution::nextAge()
{
    for(int x = 0; x < fieldSizeX; x++)
        for(int y = 0; y < fieldSizeY; y++)
            delete fields[x][y];
    QPixmap pix = QPixmap(":img/cell.jpg").scaled(desk.width()/fieldSizeX*0.95, desk.height()/fieldSizeY*0.95);
    for(int x = 0; x < fieldSizeX; x++)
    {
        for(int y = 0; y < fieldSizeY; y++)
        {
            fields[x][y] = new FieldCell(pix, foods, poisons, walls, qrand()%100>wallsSeed);
            fields[x][y]->setPos(x*pixW, y*pixH);
            fields[x][y]->setFieldPos(QPoint(x,y));
            scene->addItem(fields[x][y]);
        }
    }
    for(int i = 0; i < lifes.length(); i++)
        scene->removeItem(lifes.at(i));
    newAge.clear();
    LifeCell *best[4];
    best[0] = loosers.at(loosers.length()-1);
    best[1] = loosers.at(loosers.length()-2);
    best[2] = loosers.at(loosers.length()-3);
    best[3] = loosers.at(loosers.length()-4);

    QString best0, best1, best2, best3;             // тут вносяться найкращі результати минулого покоління в таблицю
    for(int i = 0; i < maxMemory; i++)
    {
        best0.append(QString::number(best[0]->_DNA[i]));
        best0.append(" ");
        best1.append(QString::number(best[1]->_DNA[i]));
        best1.append(" ");
        best2.append(QString::number(best[2]->_DNA[i]));
        best2.append(" ");
        best3.append(QString::number(best[3]->_DNA[i]));
        best3.append(" ");
    }
    query->exec("INSERT INTO evolution(age,"
                " firstDNA, firstLifeTime,"
                "secondDNA, secondLifeTime,"
                "thirdDNA, thirdLifeTime,"
                "fourthDNA, fourthLifeTime)"
                "values(" + QString::number(forTest) + ", " +
                "'" + best0 + "'" + ", " + best[0]->survived + ", " +
                "'" + best1 + "'" + ", " + best[1]->survived + ", " +
                "'" + best2 + "'" + ", " + best[2]->survived + ", " +
                "'" + best3 + "'" + ", " + best[3]->survived + ")");

    int whichone = 0;
    int fieldX, fieldY;
    LifeCell *newLife;
    for(int i = 0; i < lifesAtStart; i++)
    {
        while(true)
        {
            fieldX = rand()%fieldSizeX;
            fieldY = rand()%fieldSizeY;
            if(!fields[fieldX][fieldY]->isWall() && !fields[fieldX][fieldY]->hasLife() && !fields[fieldX][fieldY]->hasPoison())
            {
                newLife = new LifeCell(best[whichone]);
                newLife->_fieldPos = QPoint(fieldX, fieldY);
                newLife->setPos(fieldX*pixW, fieldY*pixH);
                if(i>3)
                    newLife->makeMutations();
                fields[fieldX][fieldY]->putLife(newLife);
                newAge.append(newLife);
                scene->addItem(newLife);

                whichone++;
                if(whichone>3)
                    whichone=0;
                break;
            }
        }
    }
    for(int i = 0; i < lifes.length(); i++)
        delete lifes.at(i);
    lifes.clear();
    lifes = newAge;
    loosers.clear();
}

void Evolution::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem *tempItem = scene->itemAt(event->pos(), QTransform());
    if(tempItem==NULL)
        return;
    for(int i = 0; i < lifes.length(); i++)
    {
        if((QGraphicsItem*)lifes.at(i)==tempItem)
        {
            lifes.at(i)->mousePressEvent(event);
            return;
        }
        if((QGraphicsTextItem*)lifes.at(i)->_DNAInfo==tempItem)
        {
            lifes.at(i)->_DNAInfo->hide();
            return;
        }
    }
}

void Evolution::keyPressEvent(QKeyEvent *event)
{
    if(event->text()=="+")
    {
        speed+=10;
        speedItem->setHtml(("<div style='background-color:#000000; color : green; '>" + QString::number(speed) + "</div>"));
    }
    else if(event->text()=="-")
    {
        speed-=10;
        speedItem->setHtml(("<div style='background-color:#000000; color : green; '>" + QString::number(speed) + "</div>"));
    }
    else if(event->key() == Qt::Key_Space && MayStep)
    {
        MayStep = false;
    }
    else if(event->key() == Qt::Key_Space && !MayStep)
    {
        MayStep = true;
        newStep();
    }

}

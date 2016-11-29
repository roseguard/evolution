#include "evolution.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Evolution w;
    qsrand(time(NULL));
    w.showFullScreen();

    return a.exec();
}

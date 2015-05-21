#include "mapmaker.h"
#include <QApplication>
#include "updater.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapMaker w;
    Updater *u = new Updater();
    w.getTerrainPainter()->setUpdater(u);
    u->connect(u,SIGNAL(update()),w.getTerrainPainter(),SLOT(paintMap()));
    w.show();
    u->start();

    return a.exec();
}

#include "mapsize.h"
#include "ui_mapsize.h"

MapSize::MapSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapSize)
{
    ui->setupUi(this);
}

MapSize::~MapSize()
{
    if (ui)delete ui;
}

int MapSize::getHeightOfNewMap()
{
    return ui->altoget->value();
}

int MapSize::getWidthOfNewMap()
{
    return ui->anchoget->value();
}

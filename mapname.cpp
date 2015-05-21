#include "mapname.h"
#include "ui_mapname.h"
#include <QMessageBox>
MapName::MapName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapName)
{
    ui->setupUi(this);
}

QString MapName::nameOfMap() const
{
    return _nameOfMap;
}

void MapName::setNameOfMap(QString pName)
{
    _nameOfMap = pName;
}

MapName::~MapName()
{
    delete ui;
}

void MapName::accept()
{
    QMessageBox mensajeError(this);
    _nameOfMap = ui->nameget->text();
    if (_nameOfMap.compare("") != 0){
        QDialog::accept();
    }
    else{
        mensajeError.about(this,"Error: no hay un nombre especificado","Inserte un nombre para el mapa");
    }
}

void MapName::reject()
{

}

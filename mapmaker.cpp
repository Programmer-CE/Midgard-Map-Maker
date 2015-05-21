#include "mapmaker.h"
#include "ui_mapmaker.h"
#include "iostream"
#include "terrainpainter.h"
#include <QFileSystemWatcher>
#include "mapname.h"
#include "mapsize.h"
MapMaker::MapMaker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapMaker),path("")
{
    ui->setupUi(this);
    if (ui->addTileset->isChecked())mouseAction = true;
    else mouseAction = false;
    if(ui->tierra->isChecked()) tilesetActive = false;
    else tilesetActive = true;
    ui->widget->setMapMaker(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setMaximumSize(ui->widget->minimumSize());
    setMaximumSize(ui->scrollAreaWidgetContents->minimumSize());
    _saveAsShortCut = new QShortcut(ui->actionGardarComo->shortcut(),this);
    connect(_saveAsShortCut,SIGNAL(activated()),ui->actionGardarComo,SLOT(trigger()));
    _saveShortCut = new QShortcut(ui->actionGuardar->shortcut(),this);
    connect(_saveShortCut,SIGNAL(activated()),ui->actionGuardar,SLOT(trigger()));
    _newShortCut = new QShortcut(ui->actionNuevo->shortcut(),this);
    connect(_newShortCut,SIGNAL(activated()),ui->actionNuevo,SLOT(trigger()));
    _openShortCut = new QShortcut(ui->actionAbrir->shortcut(),this);
    connect(_openShortCut,SIGNAL(activated()),ui->actionAbrir,SLOT(trigger()));
    _helpShortCut = new QShortcut(ui->actionAyuda->shortcut(),this);
    connect(_helpShortCut,SIGNAL(activated()),ui->actionAyuda,SLOT(trigger()));
}

bool MapMaker::getMouseAction()
{
    return mouseAction;
}

bool MapMaker::getTileSetActive()
{
    return tilesetActive;
}

TerrainPainter *MapMaker::getTerrainPainter()
{
    return ui->widget;
}

MapMaker::~MapMaker()
{
    delete ui;
}


void MapMaker::closeEvent(QCloseEvent *e)
{
    ui->widget->unactivateUpdater();
    QWidget::closeEvent(e);
}
void MapMaker::setActiveTileSet()
{
    if(ui->tierra->isChecked()) tilesetActive = false;
    else tilesetActive = true;
}

void MapMaker::changeMouseAction()
{
    if (ui->addTileset->isChecked())mouseAction = true;
    else mouseAction = false;

}

void MapMaker::saveData()
{
    MapName nameToSave(this);
    nameToSave.exec();
    nameOfMap = nameToSave.nameOfMap();
    path = _file.getSaveFileName(this,"xml","","xml (*.xml *.XML)");
    if (path.compare("") != 0){
        if (!path.endsWith(".xml"))path.append(".xml");
        ui->widget->saveMap(path,nameOfMap);
        this->setWindowTitle(nameOfMap);
    }
}

void MapMaker::simpleSaveData()
{
    if (path.compare("") != 0){
        ui->widget->saveMap(path,nameOfMap);
    }
    else{
        saveData();
    }
}

void MapMaker::createNewMap()
{
    MapSize ms;
    ms.exec();
    if (ms.result() == MapSize::Accepted){
        ui->widget->newMatrix(ms.getWidthOfNewMap(),ms.getHeightOfNewMap());
        path = "";
    }
    /**
    ui->scrollArea->setMaximumSize(ui->widget->minimumSize());
    setMaximumSize(ui->scrollAreaWidgetContents->minimumSize());
    */
}

void MapMaker::loadData()
{
    path = _file.getOpenFileName(this,"","","xml (*.xml *.XML)");
    if (path.compare("") != 0){
        ui->widget->loadMap(path);
        nameOfMap = ui->widget->mapName();
        this->setWindowTitle(nameOfMap);
    }
    ui->scrollArea->setMaximumSize(ui->widget->minimumSize());
    setMaximumSize(ui->scrollAreaWidgetContents->minimumSize());
}

void MapMaker::on_actionAyuda_triggered()
{
    QMessageBox help;
    help.about(this,"Ayuda", "Este programa es un creador de mapas para el proyecto Midgard, consulte la documentacion en <a href=\"https://github.com/Programmer-CE/Midgard-Map-Maker\">Midgar Map Maker Project</a> ");
}

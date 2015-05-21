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
    _helpOpen = false;
    connect(&_dialog,SIGNAL(finished(int)),this,SLOT(closedHelpDialog()));
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

void MapMaker::on_actionManual_de_uso_triggered()
{
    if (!_helpOpen){
        _helpOpen = true;
        _dialog.show();
    }
}

void MapMaker::closeEvent(QCloseEvent *e)
{
    ui->widget->unactivateUpdater();
    QWidget::closeEvent(e);
}

void MapMaker::closedHelpDialog()
{
    _helpOpen = false;
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

void MapMaker::on_printbutton_clicked()
{
    ui->widget->printMatrix();
}

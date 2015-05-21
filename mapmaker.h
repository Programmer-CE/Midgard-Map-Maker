#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <QMainWindow>
#include <QDialog>
#include "terrainpainter.h"
#include <QFileDialog>
#include <qshortcut.h>
#include <QMessageBox>
namespace Ui {
class MapMaker;
}

class MapMaker : public QMainWindow
{
    Q_OBJECT
    bool _helpOpen;
    QDialog _dialog;
    bool tilesetActive;//false tierra, true bosque
    bool mouseAction;// false remove, true agregar
    QFileDialog _file;
    QString path,nameOfMap;
    QShortcut * _saveAsShortCut;
public:
    explicit MapMaker(QWidget *parent = 0);
    bool getMouseAction();
    bool getTileSetActive();
    TerrainPainter *getTerrainPainter();
    ~MapMaker();

private slots:
    void on_actionManual_de_uso_triggered();
    void on_printbutton_clicked();

protected:
    void closeEvent(QCloseEvent *);
public slots:
    void closedHelpDialog();
    void setActiveTileSet();
    void changeMouseAction();
    void saveData();
    void simpleSaveData();
    void createNewMap();
    void loadData();
private:
    Ui::MapMaker *ui;
};

#endif // MAPMAKER_H

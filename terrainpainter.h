#ifndef TERRAINPAINTER_H
#define TERRAINPAINTER_H

#include <QWidget>
#include "updater.h"
#include <QMutex>
class MapMaker;
class TerrainPainter : public QWidget
{
    Q_OBJECT
    MapMaker *_mapMaker;
    Updater *_updater;
    QPixmap forest,terrain;
    static const int dimensionesCelda = 16;
    int ancho = 64;
    int alto = 64;
    bool **terrainMatrix;
    bool pressedB;
    QString _mapName;
    QMutex mutLocker;
    void deleteMatrix(bool **pMatrix, int pWidth,int pHeight);
    bool** initToDefaultMatrix(int pWidth,int pHeight);
public:
    explicit TerrainPainter(QWidget *parent = 0);
    void setMapMaker(MapMaker *pMapMaker);
    Updater *updater() const;
    void setUpdater(Updater *updater);
    void unactivateUpdater();
    void saveMap(QString name,QString pNameOfMap);
    void loadMap(QString name);
    void newMatrix(int width, int height);
    virtual ~TerrainPainter();
    QString mapName() const;
    void printMatrix();
    void setMapName(const QString &mapName);

signals:

public slots:
    void paintMap();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

};

#endif // TERRAINPAINTER_H

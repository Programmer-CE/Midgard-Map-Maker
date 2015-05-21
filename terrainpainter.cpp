#include "terrainpainter.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <iostream>
#include "mapmaker.h"
#include <QCloseEvent>
#include <QDragMoveEvent>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QScrollArea>
#include <QDebug>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXml/QXmlDTDHandler>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QMessageBox>
Updater *TerrainPainter::updater() const
{
    return _updater;
}

void TerrainPainter::setUpdater(Updater *updater)
{
    _updater = updater;
}

void TerrainPainter::unactivateUpdater()
{
    _updater->stop();
    while(_updater->isRunning())continue;
    delete _updater;
    _updater = 0;
}

void TerrainPainter::saveMap(QString pPath,QString pNameOfMap)
{
    QDomDocument qdd;
    QDomElement root = qdd.createElement("map");
    root.setAttribute("name",pNameOfMap);
    root.setAttribute("width",ancho);
    root.setAttribute("height",alto);

    qdd.appendChild(root);
    QString s;
    QVariant qv;
    QDomElement node = qdd.createElement("row");
    for (int x = 0; x < alto; x++){
        node = qdd.createElement("row");
        for(int y = 0; y < ancho; y++){
            s.append(terrainMatrix[y][x]?"1":"0");
        }
        node.setAttribute("xrow",s);
        root.appendChild(node);
        s = "";
    }


    QFile file(pPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){

    }
    else{
        QTextStream qts(&file);
        qts << qdd.toString();
        file.close();
    }


}

void TerrainPainter::loadMap(QString pPath)
{
    QMessageBox em;
    QFile file(pPath);
    QFile filescheme(":/scheme/esquema.xsd");
    QXmlSchema schema;
    QDomDocument qdd;
    QString nametmp;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //em.showMessage("error, no se pudo abrir el archivo");
        em.about(_mapMaker,"Error", "El documento no pudo abrirse");
    }
    else{
        if (!filescheme.open(QIODevice::ReadOnly | QIODevice::Text)){
            em.about(_mapMaker,"Error", "No se pudo llevar a cabo la operacion, vuelva a intentar.");
        }
        else{
            schema.load(&filescheme);
            if ( schema.isValid() ) {
                QXmlSchemaValidator validator( schema );

                if ( validator.validate(QUrl(QString("file://").append(pPath)))) {
                    if (!qdd.setContent(&file)){
                        em.about(_mapMaker,"Error", "No se pudo llevar a cabo la operacion, vuelva a intentar.");
                    }
                    else{
                        QDomElement root = qdd.firstChildElement();
                        nametmp = root.attributes().namedItem("name").nodeValue();
                        QString s;
                        QVariant qv;
                        QDomNodeList node = root.elementsByTagName("row");
                        int width = root.attributes().namedItem("width").nodeValue().toInt();
                        int height = root.attributes().namedItem("height").nodeValue().toInt();
                        bool **xmlMap = initToDefaultMatrix(height,width);
                        bool error = false;
                        for (int x = 0; x < height; x++){
                            s =node.at(x).attributes().item(0).nodeValue();
                            if (s.size() == width){
                                for (int y = 0; y < s.size(); y++){
                                    if (s.at(y) == QChar('0')){
                                        xmlMap[y][x] = false;
                                    }
                                    else{
                                        xmlMap[y][x] = true;
                                    }
                                }
                            }
                            else{
                                error = true;
                                break;
                            }
                        }
                        if (error){
                            deleteMatrix(xmlMap,height,width);
                            xmlMap = 0;
                            em.about(_mapMaker,"error", "El ancho es de una de las filas no es correcto,  el documento esta corrupto");
                        }
                        else{
                            mutLocker.lock();
                            deleteMatrix(terrainMatrix,alto,ancho);
                            terrainMatrix = xmlMap;
                            _mapName = nametmp;
                            ancho = width;
                            alto = height;
                            if (parent()){
                                ((QWidget*)parent())->resize(ancho*dimensionesCelda,alto*dimensionesCelda);
                                ((QWidget*)parent())->setMinimumSize(ancho*dimensionesCelda,alto*dimensionesCelda);
                                ((QWidget*)parent())->setMaximumSize(ancho*dimensionesCelda,alto*dimensionesCelda);
                            }
                            mutLocker.unlock();
                        }
                    }
                } else {
                    em.about(_mapMaker,"error", "Documento es invalido");
                }
            } else {
                em.about(_mapMaker,"error", "Error de programacion, el esquema montado es erroneo, reporte el error en la pagina <a href=\"https://github.com/Programmer-CE/Midgard-Map-Maker/issues\"> Midgard Map Maker </a>");
            }
        }
    }

}

void TerrainPainter::newMatrix(int width, int height)
{
    mutLocker.lock();
    delete terrainMatrix;
    std::cout << "ancho: " << width << " alto:" << height << std::endl;
    terrainMatrix = initToDefaultMatrix(height,width);
    alto = height;
    ancho = width;
    if (parent()){
        ((QWidget*)parent())->resize((ancho)*dimensionesCelda,(alto)*dimensionesCelda);
        ((QWidget*)parent())->setMinimumSize((ancho)*dimensionesCelda,(alto)*dimensionesCelda);
        ((QWidget*)parent())->setMaximumSize((ancho)*dimensionesCelda,(alto)*dimensionesCelda);
    }
    std::cout << "ancho-self: " << ancho << " alto-self:" << alto << std::endl;
    mutLocker.unlock();
}

TerrainPainter::~TerrainPainter()
{
    deleteMatrix(terrainMatrix,alto,ancho);

}


void TerrainPainter::paintMap()
{
    repaint();
}

QString TerrainPainter::mapName() const
{
    return _mapName;
}


void TerrainPainter::setMapName(const QString &mapName)
{
    _mapName = mapName;
}
void TerrainPainter::deleteMatrix(bool **pMatrix, int pWidth,int pHeight)
{
    for (int x = 0; x < pHeight; x++){
        delete [] pMatrix[x];
        pMatrix[x] = 0;
    }
    delete [] pMatrix;
}

bool **TerrainPainter::initToDefaultMatrix(int pWidth,int pHeight)
{
    bool **pMatrix = 0;
    pMatrix = new bool*[pHeight];
    for (int x = 0; x < pHeight; x++){
        pMatrix[x] = new bool[pWidth];
        for (int y = 0; y < pWidth; y++){
            pMatrix[x][y] = false;
        }
    }
    return pMatrix;
}

TerrainPainter::TerrainPainter(QWidget *parent) :
    QWidget(parent), terrain(":/images/t.jpg"), forest(":/images/v.jpg")
{
    _mapMaker = 0;
    pressedB = false;
    qDebug() << rect();
    if (parent){
        parent->resize(ancho*dimensionesCelda,alto*dimensionesCelda);
        parent->setMinimumSize(ancho*dimensionesCelda,alto*dimensionesCelda);
        parent->setMaximumSize(ancho*dimensionesCelda,alto*dimensionesCelda);
    }
    terrainMatrix = initToDefaultMatrix(ancho,alto);
}

void TerrainPainter::setMapMaker(MapMaker *pMapMaker)
{
    _mapMaker = pMapMaker;
}

void TerrainPainter::paintEvent(QPaintEvent *)
{
    mutLocker.lock();
    QPainter p;
    bool current = 0;
    p.begin(this);
    p.fillRect(rect(),Qt::black);
    for (int x = 0; x < ancho; x++){
        for(int y = 0; y < alto; y++){
            current = terrainMatrix[x][y];
            if (!current){
                p.drawPixmap(x*dimensionesCelda,y*dimensionesCelda,dimensionesCelda,dimensionesCelda,terrain);
            }
            else if (current){
                p.drawPixmap(x*dimensionesCelda,y*dimensionesCelda,dimensionesCelda,dimensionesCelda,forest);
            }
        }
    }
    p.end();
    mutLocker.unlock();
}

void TerrainPainter::mousePressEvent(QMouseEvent *m)
{
    pressedB = true;
    QRect matriz(0,0,ancho*dimensionesCelda,alto*dimensionesCelda);
    if (pressedB && matriz.contains(m->pos())){
        if(_mapMaker->getMouseAction()){
            if (!_mapMaker->getTileSetActive()){
                terrainMatrix[m->x()/dimensionesCelda][m->y()/dimensionesCelda] = false;
            }
            else{
                terrainMatrix[m->x()/dimensionesCelda][m->y()/dimensionesCelda] = true;
            }
        }
        else{
            terrainMatrix[m->x()/dimensionesCelda][m->y()/dimensionesCelda] = false;
        }
    }
}

void TerrainPainter::mouseReleaseEvent(QMouseEvent *)
{
    pressedB = false;
}

void TerrainPainter::mouseMoveEvent(QMouseEvent *e)
{
    QRect matriz(0,0,ancho*dimensionesCelda,alto*dimensionesCelda);
    if (pressedB && matriz.contains(e->pos())){
        if(_mapMaker->getMouseAction()){
            if (!_mapMaker->getTileSetActive()){
                terrainMatrix[e->x()/dimensionesCelda][e->y()/dimensionesCelda] = false;
            }
            else{
                terrainMatrix[e->x()/dimensionesCelda][e->y()/dimensionesCelda] = true;
            }
        }
        else{
            terrainMatrix[e->x()/dimensionesCelda][e->y()/dimensionesCelda] = false;
        }
    }
}

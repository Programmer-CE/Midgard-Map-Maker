#ifndef TERRAINPAINTER_H
#define TERRAINPAINTER_H

#include <QWidget>
#include "updater.h"
#include <QMutex>
class MapMaker;
/**
 * @brief Clase TerrainPainter, se encarga de pintar el mapa y gestionarlo asi como de
 * guardarlo o cargar un mapa de un disco rigido
 *
 */
class TerrainPainter : public QWidget
{
    Q_OBJECT
    MapMaker *_mapMaker; /**< TODO */
    Updater *_updater; /**< TODO */
    QPixmap forest,terrain; /**< TODO */
    static const int dimensionesCelda = 16; /**< TODO */
    int ancho = 64; /**< TODO */
    int alto = 64; /**< TODO */
    bool **terrainMatrix; /**< TODO */
    bool pressedB; /**< TODO */
    QString _mapName; /**< TODO */
    QMutex mutLocker; /**< TODO */
    /**
     * @brief Se encarga de eliminar una matriz, en memoria dinamica
     *
     * @param pMatrix la matriz a eliminar
     * @param pWidth es el largo de la matriz
     * @param pHeight es el largo de las listas dentro de la matriz
     */
    void deleteMatrix(bool **pMatrix, int pWidth,int pHeight);
    /**
     * @brief Se encarga de inicializar una matriz en valores cero
     *
     * @param pWidth el ancho deseado
     * @param pHeight es el alto deseado
     * @return la matriz creada en memoria dinamica
     */
    bool** initToDefaultMatrix(int pWidth,int pHeight);
public:
    /**
     * @brief Es el contructor por defecto
     *
     * @param parent
     */
    explicit TerrainPainter(QWidget *parent = 0);
    /**
     * @brief Es el metodo que se encarga de setear el creador de mapas
     *
     * @param pMapMaker Es el creado de mapa
     */
    void setMapMaker(MapMaker *pMapMaker);
    /**
     * @brief Es el qthread que se encarga llamar al metodo de pintado del mapa
     *
     * @return el qthread que se encarga de actualizar
     */
    Updater *updater() const;
    /**
     * @brief Setea el qthread
     *
     * @param updater es el qthread a utilizar
     */
    void setUpdater(Updater *updater);
    /**
     * @brief se encarga de desactivar el qthread
     *
     */
    void unactivateUpdater();
    /**
     * @brief Se encarga de guardar el mapa en xml
     *
     * @param name es el nombre representativo del mapa
     * @param pPath es la direccion en la que se guardara el mapa
     */
    void saveMap(QString pPath,QString pNameOfMap);
    /**
     * @brief Se encarga de cargar un mapa, si el archivo es invalido se arrojara un
     * dialogo que indique el problema con el archivo
     *
     * @param pPath es la direccion del archivo a cargar
     */
    void loadMap(QString pPath);
    /**
     * @brief Crea una matriz nueva intercambiandola con la anterior
     *
     * @param width es la cantidad de columnas deseadas, cada columna representa un conjunto de
     * celdas
     * @param height es la cantidad filas deseadas, cada fila representa un conjunto de
     * celdas
     */
    void newMatrix(int width, int height);
    /**
     * @brief Es el destructor
     *
     */
    virtual ~TerrainPainter();
    /**
     * @brief Retorna el nombre representativo del mapa
     *
     * @return El nombre representativo del mapa
     */
    QString mapName() const;
    /**
     * @brief Setea el nombre representativo del mapa
     *
     * @param mapName
     */
    void setMapName(const QString &mapName);

signals:

public slots:
    void paintMap();
protected:
    /**
     * @brief Se encarga de printar el mapa
     *
     * @param
     */
    void paintEvent(QPaintEvent *);
    /**
     * @brief Se encarga de gestionar los eventos de mouse del tipo presionar
     *
     * @param MouseEvent Es el evento
     */
    void mousePressEvent(QMouseEvent *);
    /**
     * @brief Es el metodo que se encarga de gestionar los eventos de mouse del tipo
     * soltar
     *
     * @param MouseEvent Es el evento
     */
    void mouseReleaseEvent(QMouseEvent *);
    /**
     * @brief Es el metodo que se encarga de gestionar los eventos demouse del tipo mover
     *
     * @param MouseEvent Es el evento
     */
    void mouseMoveEvent(QMouseEvent *);

};

#endif // TERRAINPAINTER_H

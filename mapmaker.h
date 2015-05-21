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

/**
 * @brief Clase MapMaker es la clase que actua con el usuario, es una ventana con algunos botones
 * con los que se puede editar un mapa del programa Midgard, el proyecto Midgard se puede
 * encontrar en el siguiente hipervinculo
 * @link https://github.com/Programmer-CE/Midgard-Project
 *
 */
class MapMaker : public QMainWindow
{
    Q_OBJECT
    bool tilesetActive;//false tierra, true bosque /**< TODO */
    bool mouseAction;// false remove, true agregar /**< TODO */
    QFileDialog _file; /**< TODO Es el visor de archivos*/
    QString path,nameOfMap; /**< TODO es el la direccion del archivo en uso archivo y nombre del mapa, respectivamente*/
    /**< TODO shortcuts para la interfaz*/
    QShortcut * _saveAsShortCut;
    QShortcut * _saveShortCut; /**< TODO */
    QShortcut * _openShortCut; /**< TODO */
    QShortcut * _newShortCut; /**< TODO */
    QShortcut * _helpShortCut; /**< TODO */
public:
    /**
     * @brief Es el constructor inicializa un mapa por defecto de tamanio 64 celdas por 64 celdas
     *
     * @param parent es el complemtento en el que se ejecutara esta ventana
     */
    explicit MapMaker(QWidget *parent = 0);
    /**
     * @brief Obtiene la accion del mouse
     *
     * @return true si la accion es agregar, false si la accion es quitar
     */
    bool getMouseAction();
    /**
     * @brief Retorna la bandera que indica que tipo de elemento desea insertarse
     *
     * @return true si se desea insertar bosque, que es un obstaculo, y false si se desea
     * insertar tierra o terreno que no es un obstaculo
     */
    bool getTileSetActive();
    /**
     * @brief Obtiene objeto que se encarga de pintar el mapa
     *
     * @return TerrainPainter es el objeto que se encaga de pintar el mapa
     */
    TerrainPainter *getTerrainPainter();
    /**
     * @brief Es el destructor y liberador de memoria
     *
     */
    ~MapMaker();

private slots:

    /**
     * @brief Es la accion que permite visualizar la ayuda sobre este programa
     */
    void on_actionAyuda_triggered();

protected:
    /**
     * @brief Es el evento que se encarga de cerrar el la ventana correctamente
     *
     * @param pCloseEvent Es el evento de cierre
     */
    void closeEvent(QCloseEvent *pCloseEvent);
public slots:
    /**
     * @brief Setea el tipo de celda a insertar depende de las opciones de radiobutton
     * con las etiquetas tierra y bosque
     *
     */
    void setActiveTileSet();
    /**
     * @brief Es la accion del mouse borra los elementos de bosque en las celdas del mapa
     *
     */
    void changeMouseAction();
    /**
     * @brief Arroja una ventana que solicita el nombre del mapa con la cual se quiere representar,
     * luego arroja otra
     * ventana de buscador de archivos con el cual se solicita la direccion a guardar del mapa
     * si se selecciono una direccion de guardado se procede a guardar un xml en la direccion
     * solicitada. No es necesario colocar la extension del archivo ya que esta se coloca
     * automaticamente. El archivo guardado es un xml aun asi si el usuario no lo desea
     *
     */
    void saveData();
    /**
     * @brief Se encarga de guardar los cambios en el mismo archivo, se recomienda que se
     * use el shortcut Alt+G
     *
     */
    void simpleSaveData();
    /**
     * @brief Se encarga de crear un nuevo mapa de un tamanio seleccionado
     *
     */
    void createNewMap();
    /**
     * @brief Se encarga de abrir un archivo xml si este sigue con el standar definido en
     * el xml schema llamado esquema.xsd entonces el archivo es cargado a memoria de lo
     * contrario el archivo no se abre y se arroja un dialogo con el respectivo texto
     *
     */
    void loadData();
private:
    Ui::MapMaker *ui; /**< TODO */
};

#endif // MAPMAKER_H

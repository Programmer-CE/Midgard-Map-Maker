#ifndef MAPNAME_H
#define MAPNAME_H

#include <QDialog>

namespace Ui {
class MapName;
}

/**
 * @brief Es un dialogo que se encarga de obtener el nombre del mapa esto es un nombre
 * representativo para el controlardor servidores en el proyecto Midgard, este dialogo
 * es arrojado cuando se guarda un archivo por primera vez
 *
 */
class MapName : public QDialog
{
    Q_OBJECT
    QString _nameOfMap; /**< TODO */
public:
    /**
     * @brief Es el constructor por defecto
     *
     * @param parent
     */
    explicit MapName(QWidget *parent = 0);
    /**
     * @brief Retorna el nombre representativo del mapa
     *
     * @return el nombre representativo del mapa
     */
    QString nameOfMap() const;
    /**
     * @brief Setea el nombre del mapa
     *
     * @param pName es el nombre a setear
     */
    void setNameOfMap(QString pName);
    /**
     * @brief Es el destructor, limpia la memoria
     *
     */
    ~MapName();
public slots:
    /**
     * @brief se sobrescribe si no existe un nombre representativo para el mapa entonces
     * se arroja un dialogo con un mensaje indicando que debe insertarse un nombre, se acepta
     * el dialogo si se inserta un nombre
     *
     */
    void accept();
    /**
     * @brief no hace nada pues no se puede rechazar el dialogo, la unica forma de que
     * el dialogo se "quite" es aceptandolo
     *
     */
    void reject();
private:
    Ui::MapName *ui; /**< TODO */
};

#endif // MAPNAME_H

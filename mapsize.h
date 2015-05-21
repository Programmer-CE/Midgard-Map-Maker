#ifndef MAPSIZE_H
#define MAPSIZE_H

#include <QDialog>

namespace Ui {
class MapSize;
}

/**
 * @brief Es un dialogo que se encarga de obtener el tamanio del nuevo mapa a crear
 *
 */
class MapSize : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Es el constructor por defecto
     *
     * @param parent
     */
    explicit MapSize(QWidget *parent = 0);
    /**
     * @brief Es el destructor
     *
     */
    ~MapSize();
    /**
     * @brief Obtiene el tamanio de la altura del mapa, esta altura esta dada en numero de
     * celdas
     *
     * @return la cantidad de celdas verticalmente
     */
    int getHeightOfNewMap();
    /**
     * @brief Obtiene el tamanio de la anchura del mapa, la anchura se da en celdas de mapa
     *
     * @return la cantidad de celdas horizontalmente
     */
    int getWidthOfNewMap();

private:
    Ui::MapSize *ui; /**< TODO */
};

#endif // MAPSIZE_H

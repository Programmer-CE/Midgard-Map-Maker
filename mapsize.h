#ifndef MAPSIZE_H
#define MAPSIZE_H

#include <QDialog>

namespace Ui {
class MapSize;
}

class MapSize : public QDialog
{
    Q_OBJECT

public:
    explicit MapSize(QWidget *parent = 0);
    ~MapSize();
    int getHeightOfNewMap();
    int getWidthOfNewMap();

private:
    Ui::MapSize *ui;
};

#endif // MAPSIZE_H

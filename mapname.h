#ifndef MAPNAME_H
#define MAPNAME_H

#include <QDialog>

namespace Ui {
class MapName;
}

class MapName : public QDialog
{
    Q_OBJECT
    QString _nameOfMap;
public:
    explicit MapName(QWidget *parent = 0);
    QString nameOfMap() const;
    void setNameOfMap(QString pName);
    ~MapName();
public slots:
    void accept();
    void reject();
private:
    Ui::MapName *ui;
};

#endif // MAPNAME_H

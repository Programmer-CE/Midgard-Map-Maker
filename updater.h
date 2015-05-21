#ifndef UPDATER_H
#define UPDATER_H
#include "qthread.h"
class Updater:public QThread
{
    Q_OBJECT
    bool _isRunning;
public:
    explicit Updater(QObject *parent = 0);
    void run();
    void stop();
signals:
    void update();
};

#endif // UPDATER_H

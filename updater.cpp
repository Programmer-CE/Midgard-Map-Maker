#include "updater.h"

Updater::Updater(QObject *parent)
{
}

void Updater::run()
{
    _isRunning = true;
    while(_isRunning){
        emit update();
        msleep(42);
    }
}

void Updater::stop()
{
    _isRunning = false;
}

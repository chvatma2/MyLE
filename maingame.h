#ifndef MAINGAME_H
#define MAINGAME_H

#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

class MainGame
{
public:
    MainGame();

    void run();
    void init();

private:
    MainWindow * m_window;
};

#endif // MAINGAME_H

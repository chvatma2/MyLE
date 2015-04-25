#include "maingame.h"

MainGame::MainGame() : m_window(nullptr)
{
}

void MainGame::init()
{
    m_window = new MainWindow;
    m_window->setWindowTitle("My Little Engine");
    m_window->showFullScreen();
}

void MainGame::run()
{
    init();
    m_window->show();
}

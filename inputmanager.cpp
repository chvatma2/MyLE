#include "inputmanager.h"
#include <iostream>

InputManager::InputManager(QObject* parent) : QObject(parent)
{

}

void InputManager::keyPressed(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Tab:
        std::cout << "tab pressed" << std::endl;
        break;
    }
}

void InputManager::keyReleased(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Tab:
        std::cout << "tab released" << std::endl;
        break;
    }
}

void InputManager::mouseMoved(QMouseEvent *event)
{
    //std::cout << "X:" << event->localPos().x() << " Y:" << event->localPos().y() << std::endl;
}


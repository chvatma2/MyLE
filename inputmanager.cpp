#include "inputmanager.h"
#include <iostream>

using namespace MyLE;

InputManager::InputManager(QObject* parent) : QObject(parent)
{

}

void InputManager::setOwnerWindow(QWidget *owner)
{
    m_owner = owner;
}

void InputManager::keyPressed(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Tab:
        std::cout << "tab pressed" << std::endl;
        break;
    case Qt::Key_F11:
        if(m_owner->isFullScreen())
            m_owner->showMaximized();
        else
            m_owner->showFullScreen();
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


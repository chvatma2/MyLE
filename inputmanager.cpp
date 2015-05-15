#include "inputmanager.h"
#include <iostream>

using namespace MyLE;

InputManager::InputManager() : QObject()
{

}

void InputManager::keyPressed(QKeyEvent *event)
{
    m_PressedKeys.insert(event->key());
}

void InputManager::keyReleased(QKeyEvent *event)
{
        m_PressedKeys.remove(event->key());

}

void InputManager::mouseMoved(QMouseEvent *event)
{
    m_MousePosition.setX(event->localPos().x());
    m_MousePosition.setY(event->localPos().y());
}

void InputManager::mouseButtonPressed(QMouseEvent *event)
{
    m_PressedButtons.insert(event->button());
}

void InputManager::mouseButtonReleased(QMouseEvent *event)
{
    m_PressedButtons.remove(event->button());
}

bool InputManager::isKeyPressed(Qt::Key key) const
{
    return m_PressedKeys.contains(key);
}

bool InputManager::isButtonPressed(Qt::MouseButton button) const
{
    return m_PressedButtons.contains(button);
}

QVector2D InputManager::getMousePosition() const
{
    return m_MousePosition;
}


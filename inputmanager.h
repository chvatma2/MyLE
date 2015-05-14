#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>
#include <QKeyEvent>
#include "glwidget.h"

namespace MyLE
{

class GLWidget;

class InputManager : public QObject
{
    Q_OBJECT

public:
    InputManager(QObject* parent);

public slots:
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);
    void mouseMoved(QMouseEvent* event);
    void mouseButtonPressed(QMouseEvent* event);
    void mouseButtonReleased(QMouseEvent* event);

    bool isKeyPressed(Qt::Key key) const;
    bool isButtonPressed(Qt::MouseButton button) const;

    QVector2D getMousePosition() const;

private:
    QSet<int> m_PressedKeys;
    QSet<int> m_PressedButtons;

    QVector2D m_MousePosition;
};

}
#endif // INPUTMANAGER_H

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>
#include <QKeyEvent>

class InputManager : public QObject
{
    Q_OBJECT

public:
    InputManager(QObject* parent);

public slots:
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);
    void mouseMoved(QMouseEvent* event);
};

#endif // INPUTMANAGER_H

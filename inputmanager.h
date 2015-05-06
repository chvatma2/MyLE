#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QObject>
#include <QKeyEvent>
#include <QWidget>

namespace MyLE
{

class InputManager : public QObject
{
    Q_OBJECT

public:
    InputManager(QObject* parent);
    void setOwnerWindow(QWidget* owner);

public slots:
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);
    void mouseMoved(QMouseEvent* event);

private:
    QWidget* m_owner;
};

}
#endif // INPUTMANAGER_H

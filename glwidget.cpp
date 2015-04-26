#include "glwidget.h"
#include <QScreen>
#include <QApplication>
#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_inputManager = new InputManager(this);
}

void GLWidget::paintGL()
{

}

void GLWidget::resizeGL(int w, int h)
{
    this->resize(w, h);
}

void GLWidget::initializeGL()
{
    QScreen* currentScreen = QApplication::screens().at(0);
    resizeGL(currentScreen->availableGeometry().width(), currentScreen->availableGeometry().height());
    m_refreshRate = currentScreen->refreshRate();
    m_timer = new QTimer(this);
    m_timer->setTimerType(Qt::PreciseTimer);
    m_timer->start(1000/m_refreshRate);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(refresh()));
    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)), m_inputManager, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(keyReleaseEvent(QKeyEvent*)), m_inputManager, SLOT(keyReleased(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)), m_inputManager, SLOT(mouseMoved(QMouseEvent*)));

    this->setMouseTracking(true);

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);


}

void GLWidget::refresh()
{
    repaint();
}

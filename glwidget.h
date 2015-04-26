#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include "inputmanager.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    void paintGL();
    void resizeGL(int w, int h);
    void initializeGL();

private slots:
    void refresh();

private:
    qreal m_refreshRate;
    QTimer* m_timer;
    InputManager* m_inputManager;

signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // GLWIDGET_H

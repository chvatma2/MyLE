#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QTime>
#include "inputmanager.h"
#include "sprite.h"
#include "vertex.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Compatibility
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();
    void paintGL();
    void resizeGL(int w, int h);
    void initializeGL();

private slots:
    void refresh();
    void printFPS();

private:
    qreal m_refreshRate;
    QTimer m_redrawTimer;
    InputManager* m_inputManager;
    Sprite * m_sprite;
    QOpenGLShaderProgram * m_shader;
    GLfloat m_time;
    QTimer m_fpsTimer;
    int m_frameCounter;

    void connectSlotsSignals();
    void initScreen();
    void initTimers();
    void initShaders();


signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // GLWIDGET_H

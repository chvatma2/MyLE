#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QColor>
#include "inputmanager.h"
#include "sprite.h"
#include "vertex.h"
#include "resourcemanager.h"
#include "camera2d.h"
#include "spritebatch.h"

namespace MyLE
{

class InputManager;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();

    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void initializeGL() Q_DECL_OVERRIDE;

    void setClearColor(const QColor& color);
    void setActiveCamera(Camera2D* camera) {m_ActiveCamera = camera;}
    void refresh();

    Camera2D* m_ActiveCamera;

private slots:
    void printFPS();

private:
    QTimer m_FPSTimer;
    InputManager* m_InputManager;
    QOpenGLShaderProgram * m_Shader;
    GLfloat m_Time;
    QColor m_ClearColor;

    ResourceManager m_ResourceManager;
    QOpenGLTexture * m_TestTexture;

    int m_FrameCounter;

    SpriteBatch m_SpriteBatch;


    void connectSlotsSignals();
    void initScreen();
    void initTimers();
    void initShaders();
    void processInput();


signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

}
#endif // GLWIDGET_H

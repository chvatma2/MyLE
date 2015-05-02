#include "glwidget.h"
#include <QScreen>
#include <QApplication>
#include <iostream>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_time(0), m_frameCounter(0)
{
    m_inputManager = new InputManager(this);
    QSurfaceFormat f = this->format();
    f.setMajorVersion(3);
    f.setMinorVersion(3);
    f.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    f.setSwapInterval(1);
    this->setFormat(f);
}

GLWidget::~GLWidget()
{
    delete m_sprite;
}

void GLWidget::paintGL()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->bind();

    m_time += 0.01f;
    m_shader->setUniformValue("time", m_time);

    m_sprite->draw(m_shader);
    m_shader->release();

    m_frameCounter++;
}

void GLWidget::resizeGL(int w, int h)
{
    this->resize(w, h);
}

void GLWidget::connectSlotsSignals()
{
    connect(&m_redrawTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    connect(&m_fpsTimer, SIGNAL(timeout()), this, SLOT(printFPS()));
    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)), m_inputManager, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(keyReleaseEvent(QKeyEvent*)), m_inputManager, SLOT(keyReleased(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)), m_inputManager, SLOT(mouseMoved(QMouseEvent*)));
}

void GLWidget::initScreen()
{
    QScreen* currentScreen = QApplication::screens().at(0);
    resizeGL(currentScreen->availableGeometry().width(), currentScreen->availableGeometry().height());
    m_refreshRate = currentScreen->refreshRate();
}

void GLWidget::initTimers()
{
    m_redrawTimer.setTimerType(Qt::PreciseTimer);
    m_fpsTimer.setTimerType(Qt::PreciseTimer);

    if(format().swapInterval() == -1)
    {
        qDebug() << "Swap interval -1";
        m_redrawTimer.setInterval(1000/m_refreshRate);
    }
    else
    {
        m_redrawTimer.setInterval(0);
    }
    m_fpsTimer.setInterval(5000);

    m_redrawTimer.start();
    m_fpsTimer.start();

}

void GLWidget::initShaders()
{
    m_shader = new QOpenGLShaderProgram(this);
    if( m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resources/vertshader.vert"))
        qDebug() << "Vertex shader compiled succesfuly";
    if (m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resources/fragshader.frag"))
        qDebug() << "Fragment shader compiled succesfuly";
    m_shader->bindAttributeLocation("vertexPosition", 0);
    m_shader->bindAttributeLocation("vertexColor", 1);
    m_shader->link();
}

void GLWidget::initializeGL()
{
    initScreen();
    connectSlotsSignals();
    initTimers();

    this->setMouseTracking(true);

    initializeOpenGLFunctions();

    initShaders();

    glClearColor(0.0, 0.0, 1.0, 1.0);

    m_sprite = new Sprite(-0.5f, -0.5f, 1.0f, 1.0f);
}

void GLWidget::refresh()
{
    repaint();
}

void GLWidget::printFPS()
{
    qDebug() << "FPS: " << m_frameCounter/5;
    m_frameCounter = 0;
}

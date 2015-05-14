#include "glwidget.h"
#include <QScreen>
#include <QApplication>
#include <iostream>
#include <QDebug>

using namespace MyLE;

const float SCALE_SPEED = 0.1f;
const float CAMERA_SPEED = 2.0f;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_ActiveCamera(NULL), m_Shader(0), m_Time(0), m_ClearColor(Qt::darkBlue), m_FrameCounter(0)
{
    m_InputManager = new InputManager(this);
}

GLWidget::~GLWidget()
{
    makeCurrent();

    delete m_Shader;

    doneCurrent();
}

void GLWidget::setClearColor(const QColor &color)
{
    m_ClearColor = color;
    update();
}

void GLWidget::paintGL()
{
    processInput();

    glClearColor(m_ClearColor.redF(), m_ClearColor.greenF(), m_ClearColor.blueF(), m_ClearColor.alphaF());
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(m_Shader->uniformLocation("testTexture"), 0);

    m_Time += 0.01f;
    m_Shader->setUniformValue("time", m_Time);
    m_Shader->setUniformValue("P", m_ActiveCamera->getViewMatrix());

    glActiveTexture(GL_TEXTURE0);

    m_SpriteBatch.begin();

    m_SpriteBatch.draw(QVector4D(0.0f, 0.0f , 50.0f, 50.0f),
                       QVector4D(0.0f, 0.0f, 1.0f, 1.0f),
                       m_ResourceManager.loadTexture("resources/textures/starwars/xwing.png")->textureId(),
                       0.0f,
                       QColor(255, 255, 0));

//    m_SpriteBatch.draw(QVector4D(50.0f, 0.0f , 50.0f, 50.0f),
//                       QVector4D(0.0f, 0.0f, 1.0f, 1.0f),
//                       m_ResourceManager.loadTexture("resources/textures/JimmyJump/CharacterRight_Standing.png")->textureId(),
//                       0.0f,
//                       QColor(255, 255, 0));

    m_SpriteBatch.end();
    m_SpriteBatch.renderBatch();

    m_FrameCounter++;

}

void GLWidget::resizeGL(int w, int h)
{
    this->resize(w, h);
    m_ActiveCamera->setScreenSize(w, h);
}

void GLWidget::connectSlotsSignals()
{
    connect(&m_FPSTimer, SIGNAL(timeout()), this, SLOT(printFPS()));
    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)), m_InputManager, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(keyReleaseEvent(QKeyEvent*)), m_InputManager, SLOT(keyReleased(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)), m_InputManager, SLOT(mouseMoved(QMouseEvent*)));
    connect(this, SIGNAL(mousePressEvent(QMouseEvent*)), m_InputManager, SLOT(mouseButtonPressed(QMouseEvent*)));
    connect(this, SIGNAL(mouseReleaseEvent(QMouseEvent*)), m_InputManager, SLOT(mouseButtonReleased(QMouseEvent*)));
}

void GLWidget::initScreen()
{
    QScreen* currentScreen = QApplication::screens().at(0);
    resizeGL(currentScreen->availableGeometry().width(), currentScreen->availableGeometry().height());
}

void GLWidget::initTimers()
{
    m_FPSTimer.setInterval(5000);

    m_FPSTimer.start();

}

void GLWidget::initShaders()
{
    m_Shader = new QOpenGLShaderProgram(this);
    if( m_Shader->addShaderFromSourceFile(QOpenGLShader::Vertex, "resources/shaders/vertshader.vert"))
        qDebug() << "Vertex shader compiled succesfuly";
    if (m_Shader->addShaderFromSourceFile(QOpenGLShader::Fragment, "resources/shaders/fragshader.frag"))
        qDebug() << "Fragment shader compiled succesfuly";
    m_Shader->bindAttributeLocation("vertexPosition", 0);
    m_Shader->bindAttributeLocation("vertexColor", 1);
    m_Shader->bindAttributeLocation("vertexUV", 2);
    m_Shader->link();
    m_Shader->bind();
    m_Shader->setUniformValue("testTexture", 0);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    qDebug() << "Opengl version: " << (char*)glGetString(GL_VERSION);

    initScreen();
    connectSlotsSignals();
    initTimers();

    this->setMouseTracking(true);

    initShaders();

    qDebug() << "Height: " << height();
    qDebug() << "Width: " << width();
//    m_Sprites.push_back(new Sprite(0.0f, 0.0f, width()/2.0f, height()/2.0f, "resources/textures/JimmyJump/CharacterRight_Standing.png", m_ResourceManager));
//    m_Sprites.push_back(new Sprite(width()/2.0f, 0.0f, width()/2.0f, height()/2.0f, "resources/textures/JimmyJump/CharacterRight_Standing.png", m_ResourceManager));
//    m_Sprites.push_back(new Sprite(-1.0f, -1.0f, 1.0f, 1.0f, "resources/textures/JimmyJump/CharacterRight_Standing.png", m_ResourceManager));
//    m_Sprites.push_back(new Sprite(0.0f, -1.0f, 1.0f, 1.0f, "resources/textures/JimmyJump/CharacterRight_Standing.png", m_ResourceManager));

    m_ActiveCamera->setScreenSize(width(), height());

    m_SpriteBatch.init(m_Shader);

    //ALPHA
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLWidget::refresh()
{
    repaint();
}

void GLWidget::printFPS()
{
    qDebug() << "FPS: " << m_FrameCounter/5;
    m_FrameCounter = 0;
}

void GLWidget::processInput()
{
    if(m_InputManager->isKeyPressed(Qt::Key_W))
        m_ActiveCamera->setPosition(m_ActiveCamera->getPosition() + QVector2D(0, -CAMERA_SPEED));
    if(m_InputManager->isKeyPressed(Qt::Key_S))
        m_ActiveCamera->setPosition(m_ActiveCamera->getPosition() + QVector2D(0, CAMERA_SPEED));
    if(m_InputManager->isKeyPressed(Qt::Key_A))
        m_ActiveCamera->setPosition(m_ActiveCamera->getPosition() + QVector2D(CAMERA_SPEED, 0.0f));
    if(m_InputManager->isKeyPressed(Qt::Key_D))
        m_ActiveCamera->setPosition(m_ActiveCamera->getPosition() + QVector2D(-CAMERA_SPEED, 0.0f));
    if(m_InputManager->isKeyPressed(Qt::Key_Q))
        m_ActiveCamera->changeScaleBy(SCALE_SPEED);
    if(m_InputManager->isKeyPressed(Qt::Key_E))
        m_ActiveCamera->changeScaleBy(-SCALE_SPEED);
    if(m_InputManager->isKeyPressed(Qt::Key_F11))
    {
        if(isFullScreen())
            showMaximized();
        else
            showFullScreen();
    }
    if(m_InputManager->isButtonPressed(Qt::LeftButton))
    {
        qDebug() << "Shooting x=" << m_ActiveCamera->convertScreenPosition(m_InputManager->getMousePosition());
    }
}

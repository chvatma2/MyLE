#include "sprite.h"

using namespace MyLE;

Sprite::Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, const QString& texturePath, ResourceManager& resourceManager)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_vbo(0)
{
    initializeOpenGLFunctions();
    Vertex vertexes[6];
    vertexes[0].set(x + width, y + height, 0, 255, 0, 255, 1.0, 1.0);
    vertexes[1].set(x, y + height, 255, 0, 0, 255, 0.0, 1.0);
    vertexes[2].set(x, y, 255, 0, 0, 255, 0.0, 0.0);
    vertexes[3].set(x, y, 255, 0, 0, 255, 0.0, 0.0);
    vertexes[4].set(x + width, y, 255, 0, 0, 255, 1.0, 0.0);
    vertexes[5].set(x + width, y + height, 0, 0, 255, 255, 1.0, 1.0 );

    m_texture = resourceManager.loadTexture(texturePath);

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();

    m_vbo->bind();

    m_vbo->allocate(vertexes, sizeof(vertexes));

}

Sprite::~Sprite()
{
    m_vbo->destroy();
    delete m_vbo;
}


void Sprite::draw (QOpenGLShaderProgram* program)
{
    m_vbo->bind();
    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->enableAttributeArray(2);

    program->setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, position), 2, sizeof(Vertex));
    program->setAttributeBuffer(1, GL_UNSIGNED_BYTE, offsetof(Vertex, color), 4, sizeof(Vertex));
    program->setAttributeBuffer(2, GL_FLOAT, offsetof(Vertex, uv), 2, sizeof(Vertex));

    m_texture->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    program->disableAttributeArray(0);
    program->disableAttributeArray(1);
    program->disableAttributeArray(2);
    m_vbo->release();

}

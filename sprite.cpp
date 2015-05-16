#include "sprite.h"

using namespace MyLE;

Sprite::Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, const QString& texturePath, ResourceManager& resourceManager)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_vbo(0)
{
    initializeOpenGLFunctions();
    Vertex vertexes[6];
//    vertexes[0].set(x + width, y + height, 0, 255, 0, 255, 1.0f, 1.0f);
//    vertexes[1].set(x, y + height, 255, 0, 0, 255, 0.0f, 1.0f);
//    vertexes[2].set(x, y, 255, 0, 0, 255, 0.0f, 0.0f);
//    vertexes[3].set(x, y, 255, 0, 0, 255, 0.0f, 0.0f);
//    vertexes[4].set(x + width, y, 255, 0, 0, 255, 1.0f, 0.0f);
//    vertexes[5].set(x + width, y + height, 0, 0, 255, 255, 1.0f, 1.0f);

    for (int i=0; i<6; i++)
    {
        qDebug() << "Vertex " << i << " x=" << vertexes[i].position.x;
        qDebug() << "Vertex " << i << " y=" << vertexes[i].position.y;
    }

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
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    program->setAttributeBuffer(1, GL_UNSIGNED_BYTE, offsetof(Vertex, color), 4, sizeof(Vertex));
//    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    program->setAttributeBuffer(2, GL_FLOAT, offsetof(Vertex, uv), 2, sizeof(Vertex));
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

//    m_texture->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    program->disableAttributeArray(0);
    program->disableAttributeArray(1);
    program->disableAttributeArray(2);
    m_vbo->release();

}

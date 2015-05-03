#include "sprite.h"

Sprite::Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, QOpenGLTexture *texture)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_vbo(0), m_texture(texture)
{
    initializeOpenGLFunctions();
    m_vertexes[0].set(x + width, y + height, 0, 255, 0, 255, 1.0, 1.0);
    m_vertexes[1].set(x, y + height, 255, 0, 0, 255, 0.0, 1.0);
    m_vertexes[2].set(x, y, 255, 0, 0, 255, 0.0, 0.0);
    m_vertexes[3].set(x, y, 255, 0, 0, 255, 0.0, 0.0);
    m_vertexes[4].set(x + width, y, 255, 0, 0, 255, 1.0, 0.0);
    m_vertexes[5].set(x + width, y + height, 0, 0, 255, 255, 1.0, 1.0 );

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();

    m_vbo->bind();
    //Upload the data to the GPU
    m_vbo->allocate(m_vertexes, sizeof(m_vertexes));
}

Sprite::~Sprite()
{
    m_vbo->destroy();
    delete m_vbo;
}


void Sprite::draw (QOpenGLShaderProgram* program)
{
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

}

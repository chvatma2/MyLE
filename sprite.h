#ifndef SPRITE_H
#define SPRITE_H

#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector>
#include <QDebug>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "vertex.h"
#include "resourcemanager.h"

namespace MyLE
{

class Sprite : protected QOpenGLFunctions
{
public:
    Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height, const QString &texturePath, ResourceManager& resourceManager);
    ~Sprite();
    void draw (QOpenGLShaderProgram* program);

private:
    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_width;
    GLfloat m_height;

    QOpenGLBuffer* m_vbo;
    GLuint m_texture;
};

}

#endif // SPRITE_H

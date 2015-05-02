#ifndef SPRITE_H
#define SPRITE_H

#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector>
#include <QDebug>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QOpenGLShaderProgram>
#include "vertex.h"

class Sprite : protected QOpenGLFunctions_3_3_Compatibility
{
public:
    Sprite(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    ~Sprite();
    void draw (QOpenGLShaderProgram* program);

private:
    GLfloat m_x;
    GLfloat m_y;
    GLfloat m_width;
    GLfloat m_height;

    Vertex m_vertexes[6];
    QOpenGLBuffer* m_vbo;
};

#endif // SPRITE_H

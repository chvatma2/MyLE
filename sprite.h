#ifndef SPRITE_H
#define SPRITE_H

#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector>
#include <QDebug>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "vertex.h"
#include "resourcemanager.h"

class Sprite : protected QOpenGLFunctions_3_3_Compatibility
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
    QOpenGLTexture* m_texture;
};

#endif // SPRITE_H

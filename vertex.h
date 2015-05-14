#ifndef VERTEX
#define VERTEX

#include <QOpenGLFunctions>

namespace MyLE
{

struct Position
{
    GLfloat x;
    GLfloat y;
};

struct Color
{
    GLubyte red;
    GLubyte green;
    GLubyte blue;
    GLubyte alpha;
};

struct UV
{
    GLfloat u;
    GLfloat v;
};

struct Vertex
{
    Position position;
    Color color;
    UV uv;
    void setPosition(GLfloat posX, GLfloat posY)
    {
        position.x = posX;
        position.y = posY;
    }
    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {
        color.red = r;
        color.green = g;
        color.blue = b;
        color.alpha = a;
    }
    void setUV(GLfloat u, GLfloat v)
    {
        uv.u = u;
        uv.v = v;
    }
};

}

#endif // VERTEX


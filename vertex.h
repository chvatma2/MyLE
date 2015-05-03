#ifndef VERTEX
#define VERTEX

#include <QOpenGLFunctions_3_3_Compatibility>

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
    void set(GLfloat posX, GLfloat posY, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat u, GLfloat v)
    {
        position.x = posX;
        position.y = posY;
        color.red = r;
        color.green = g;
        color.blue = b;
        color.alpha = a;
        uv.u = u;
        uv.v = v;
    }
};

#endif // VERTEX


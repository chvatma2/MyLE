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

struct Vertex
{
    Position position;
    Color color;
    void set(GLfloat posX, GLfloat posY, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {
        position.x = posX;
        position.y = posY;
        color.red = r;
        color.green = g;
        color.blue = b;
        color.alpha = a;
    }
};

#endif // VERTEX


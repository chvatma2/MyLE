#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <algorithm>

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QColor>
#include <QVector4D>
#include <vector>
#include <QOpenGLShaderProgram>
#include "vertex.h"
#include "resourcemanager.h"

namespace MyLE
{

enum class GlyphSortType
{
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

struct Glyph
{
    GLuint texture;
    float depth;
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
};

class RenderBatch
{
public:
    RenderBatch(GLuint offset, GLuint vertCount, GLuint texture);

    GLuint m_Offset;
    GLuint m_VerticesCount;
    GLuint m_Textureid;
};

class SpriteBatch : public QOpenGLFunctions
{
public:
    SpriteBatch();

    void init(QOpenGLShaderProgram* program, ResourceManager* resManager);
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();
    void draw(const QVector4D &destRectangle, const QVector4D &uvRectangle, GLuint texture, float depth, const QColor& color);
    void renderBatch();

private:
    void createRenderBatches();
    void createVertexArray(QOpenGLShaderProgram *program);
    void sortGlyphs();
    static bool compareFrontToBack(Glyph* g1, Glyph* g2);
    static bool compareBackToFront(Glyph* g1, Glyph* g2);
    static bool compareTexture(Glyph* g1, Glyph* g2);

    QOpenGLBuffer m_VBO;
    QOpenGLVertexArrayObject m_VAO;
    QVector<Glyph*> m_Glyphs;
    std::vector<RenderBatch> m_RenderBatches;
    GlyphSortType m_SortType;
    ResourceManager* m_ResourceManager;
};

}

#endif // SPRITEBATCH_H

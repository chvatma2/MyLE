#include "spritebatch.h"

using namespace MyLE;

SpriteBatch::SpriteBatch()
{

}

void SpriteBatch::init(QOpenGLShaderProgram* program, ResourceManager* resManager)
{
    initializeOpenGLFunctions();
    createVertexArray(program);
    m_ResourceManager = resManager;
}

void SpriteBatch::begin(GlyphSortType sortType)
{
    m_SortType = sortType;
    m_RenderBatches.clear();
    for(int i = 0; i < m_Glyphs.size(); i++)
        delete m_Glyphs[i];
    m_Glyphs.clear();
}

void SpriteBatch::end()
{
    sortGlyphs();
    createRenderBatches();
}

void SpriteBatch::draw(const QVector4D &destRectangle, const QVector4D &uvRectangle, QString texture, float depth, const QColor &color)
{
    Glyph* newGlyph = new Glyph;

    newGlyph->texture = m_ResourceManager->loadTexture(texture)->textureId();
    newGlyph->depth = depth;

    newGlyph->topLeft.setColor(color.red(), color.green(), color.blue(), color.alpha());
    newGlyph->topLeft.setPosition(destRectangle.x(), destRectangle.y() + destRectangle.w());
    newGlyph->topLeft.setUV(uvRectangle.x(), uvRectangle.y() + uvRectangle.w());

    newGlyph->bottomLeft.setColor(color.red(), color.green(), color.blue(), color.alpha());
    newGlyph->bottomLeft.setPosition(destRectangle.x(), destRectangle.y());
    newGlyph->bottomLeft.setUV(uvRectangle.x(), uvRectangle.y());

    newGlyph->bottomRight.setColor(color.red(), color.green(), color.blue(), color.alpha());
    newGlyph->bottomRight.setPosition(destRectangle.x() + destRectangle.z(), destRectangle.y());
    newGlyph->bottomRight.setUV(uvRectangle.x() + uvRectangle.z(), uvRectangle.y());

    newGlyph->topRight.setColor(color.red(), color.green(), color.blue(), color.alpha());
    newGlyph->topRight.setPosition(destRectangle.x() + destRectangle.z(), destRectangle.y() + destRectangle.w());
    newGlyph->topRight.setUV(uvRectangle.x() + uvRectangle.z(), uvRectangle.y() + uvRectangle.w());

    m_Glyphs.push_back(newGlyph);
}

void SpriteBatch::renderBatch()
{
    m_VAO.bind();

    for(unsigned int i = 0; i < m_RenderBatches.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D,  m_RenderBatches[i].m_Textureid);
        glDrawArrays(GL_TRIANGLES, m_RenderBatches[i].m_Offset, m_RenderBatches[i].m_VerticesCount);
    }
    m_VAO.release();
}

void SpriteBatch::createRenderBatches()
{
    std::vector<Vertex> vertices;
    vertices.resize(m_Glyphs.size() * 6);

//    if(m_Glyphs.empty())
//        return;

    int offset = 0;
    int currentVertex = 0;

    for(int currentGlyph = 0; currentGlyph < m_Glyphs.size(); currentGlyph++)
    {
        if(currentGlyph == 0 || m_Glyphs[currentGlyph]->texture != m_Glyphs[currentGlyph - 1]->texture)
        {
            m_RenderBatches.emplace_back(offset, 6, m_Glyphs[currentGlyph]->texture);
       }
        else
        {
            m_RenderBatches.back().m_VerticesCount += 6;
        }
        vertices[currentVertex++] = m_Glyphs[currentGlyph]->topLeft;
        vertices[currentVertex++] = m_Glyphs[currentGlyph]->bottomLeft;
        vertices[currentVertex++] = m_Glyphs[currentGlyph]->bottomRight;
        vertices[currentVertex++] = m_Glyphs[currentGlyph]->bottomRight;
        vertices[currentVertex++] = m_Glyphs[currentGlyph]->topRight;
        vertices[currentVertex++] = m_Glyphs[currentGlyph]->topLeft;
        offset += 6;
    }
    m_VBO.bind();
    m_VBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    m_VBO.allocate(nullptr, vertices.size() * sizeof(Vertex));
    m_VBO.allocate(vertices.data(), vertices.size() * sizeof(Vertex));

    m_VBO.release();
}

void SpriteBatch::createVertexArray(QOpenGLShaderProgram* program)
{
    m_VAO.create();
    m_VAO.bind();

    m_VBO.create();
    m_VBO.bind();

    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    program->enableAttributeArray(2);

    program->setAttributeBuffer(0, GL_FLOAT, offsetof(Vertex, position), 2, sizeof(Vertex));
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    program->setAttributeBuffer(1, GL_UNSIGNED_BYTE, offsetof(Vertex, color), 4, sizeof(Vertex));
//    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    program->setAttributeBuffer(2, GL_FLOAT, offsetof(Vertex, uv), 2, sizeof(Vertex));
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));


    m_VAO.release();
}

void SpriteBatch::sortGlyphs()
{
    switch(m_SortType)
    {
    case GlyphSortType::TEXTURE:
        std::sort(m_Glyphs.begin(), m_Glyphs.end(), compareTexture);
        break;
    case GlyphSortType::BACK_TO_FRONT:
        std::sort(m_Glyphs.begin(), m_Glyphs.end(), compareBackToFront);
        break;
    case GlyphSortType::FRONT_TO_BACK:
        std::sort(m_Glyphs.begin(), m_Glyphs.end(), compareFrontToBack);
        break;
    default:
        qDebug() << "Sort Glyphs invalid sort type";
    }
}

bool SpriteBatch::compareFrontToBack(Glyph *g1, Glyph *g2)
{
    return (g1->depth < g2->depth);
}

bool SpriteBatch::compareBackToFront(Glyph *g1, Glyph *g2)
{
    return (g1->depth > g2->depth);
}

bool SpriteBatch::compareTexture(Glyph *g1, Glyph *g2)
{
    return (g1->texture < g2->texture);
}


RenderBatch::RenderBatch(GLuint offset, GLuint vertCount, GLuint texture)
    : m_Offset(offset), m_VerticesCount(vertCount), m_Textureid(texture)
{

}

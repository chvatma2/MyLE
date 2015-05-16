#include "texturecache.h"

using namespace MyLE;

TextureCache::TextureCache()
{
}

GLuint TextureCache::getTexture(const QString& filePath)
{
    if(m_TextureMap.contains(filePath))
        return m_TextureMap.value(filePath)->textureId();

    QImage image;
    if( !image.load(filePath) )
        qDebug() << "Could not load texture " << filePath;
    QOpenGLTexture* texture = new QOpenGLTexture(image.mirrored());

    m_TextureMap.insert(filePath, texture);
    return texture->textureId();
}

void TextureCache::deleteTextures()
{
    foreach(QOpenGLTexture* texture, m_TextureMap)
        delete texture;
}

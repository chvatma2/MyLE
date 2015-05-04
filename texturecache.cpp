#include "texturecache.h"

TextureCache::TextureCache()
{

}

QOpenGLTexture* TextureCache::getTexture(const QString& filePath)
{
    QHash<QString, QOpenGLTexture*>::const_iterator it = m_textureMap.find(filePath);
    if(it != m_textureMap.end())
        return it.value();

    QImage image;
    if( !image.load(filePath) )
        qDebug() << "Could not load texture " << filePath;
    QOpenGLTexture* texture = new QOpenGLTexture(image.mirrored());

    m_textureMap.insert(filePath, texture);
    return texture;
}

void TextureCache::deleteTextures()
{
    foreach(QOpenGLTexture* texture, m_textureMap)
        delete texture;
}

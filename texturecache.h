#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <QHash>
#include <QOpenGLTexture>
#include <QDebug>

class TextureCache
{
public:
    TextureCache();
    QOpenGLTexture* getTexture(const QString &filePath);
    void deleteTextures();

private:
    QHash<QString, QOpenGLTexture*> m_textureMap;
};

#endif // TEXTURECACHE_H

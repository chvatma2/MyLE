#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <QHash>
#include <QOpenGLTexture>
#include <QDebug>
#include <QString>

namespace MyLE
{

class TextureCache
{
public:
    TextureCache();

    GLuint getTexture(const QString& filePath);
    void deleteTextures();

private:
    QHash<QString, QOpenGLTexture*> m_TextureMap;
};

}

#endif // TEXTURECACHE_H

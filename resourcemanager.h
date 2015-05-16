#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QFile>
#include <QImage>
#include <QVector>
#include <QOpenGLTexture>
#include "texturecache.h"

namespace MyLE
{

class ResourceManager
{
public:
    ResourceManager();

    void deleteTextures();

    GLuint loadTexture(const QString& fileName);
private:
    TextureCache m_textureCache;
};

}

#endif // RESOURCEMANAGER_H

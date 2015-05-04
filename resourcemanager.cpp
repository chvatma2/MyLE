#include "resourcemanager.h"
#include <QDebug>

ResourceManager::ResourceManager()
{

}

void ResourceManager::deleteTextures()
{
    m_textureCache.deleteTextures();
}

QOpenGLTexture* ResourceManager::loadTexture(const QString& fileName)
{
    return m_textureCache.getTexture(fileName);
}

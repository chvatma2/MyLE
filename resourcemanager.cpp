#include "resourcemanager.h"
#include <QDebug>

using namespace MyLE;

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

#include "resourcemanager.h"

ResourceManager::ResourceManager()
{

}

void ResourceManager::loadTexture(QString fileName, QOpenGLTexture* texture)
{
    texture = new QOpenGLTexture(QImage(fileName).mirrored());
}

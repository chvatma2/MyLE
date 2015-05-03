#include "resourcemanager.h"
#include <QDebug>

ResourceManager::ResourceManager()
{

}

void ResourceManager::loadTexture(QString fileName, QOpenGLTexture*& texture)
{
    texture = new QOpenGLTexture(QImage (fileName).mirrored());
//    texture->bind();
//    texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
//    texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
//    texture->setMagnificationFilter(QOpenGLTexture::Linear);
//    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
//    texture->generateMipMaps();
//    texture->release();
}

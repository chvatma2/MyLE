#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QFile>
#include <QImage>
#include <QVector>
#include <QOpenGLTexture>

class ResourceManager
{
public:
    ResourceManager();
    bool readTextToBuffer(QFile file);
    void loadTexture(QString fileName, QOpenGLTexture* texture);
};

#endif // RESOURCEMANAGER_H

#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <QVector2D>
#include <QMatrix4x4>

namespace MyLE
{

class Camera2D
{
public:
    Camera2D(int width, int height);

    void update( );

    QVector2D convertScreenPosition(QVector2D screenPosition);

    void setPosition(const QVector2D& newPosition) {m_Position = newPosition; m_NeedsMatrixUpdate = true;}
    QVector2D getPosition() {return m_Position;}

    void setScale(float newScale) {m_Scale = newScale; m_NeedsMatrixUpdate = true;}
    void changeScaleBy(float change);
    float getScale() {return m_Scale;}

    QMatrix4x4 getViewMatrix() {return m_ViewMatrix;}

    void setScreenSize(float width, float height);

private:
    float m_Scale;
    QVector2D m_Position;
    QMatrix4x4 m_ViewMatrix;
    QMatrix4x4 m_OrthographicMatrix;
    bool m_NeedsMatrixUpdate;
    float m_ScreenWidth;
    float m_ScreenHeight;

};

}

#endif // CAMERA2D_H

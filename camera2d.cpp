#include "camera2d.h"

using namespace MyLE;

Camera2D::Camera2D(int width, int height) : m_Scale(1.0f), m_Position(0.0f, 0.0f), m_NeedsMatrixUpdate(true)
{
    setScreenSize(width, height);
}

void Camera2D::update()
{
    if(m_NeedsMatrixUpdate)
    {
            m_ViewMatrix = m_OrthographicMatrix;

        m_ViewMatrix.translate(-m_Position.x() + m_ScreenWidth/2.0f, -m_Position.y() + m_ScreenHeight/2.0f, 0.0f);

        QMatrix4x4 scaleMatrix;
        scaleMatrix.scale(m_Scale, m_Scale);
        m_ViewMatrix = scaleMatrix * m_ViewMatrix;
        m_NeedsMatrixUpdate = false;
    }
}

QVector2D Camera2D::convertScreenPosition(QVector2D screenPosition)
{
    screenPosition.setY(m_ScreenHeight - screenPosition.y());
    screenPosition -= QVector2D(m_ScreenWidth/2, m_ScreenHeight/2);
    screenPosition /= m_Scale;
    screenPosition += m_Position;
    return screenPosition;
}

void Camera2D::changeScaleBy(float change)
{
    if(m_Scale + change >= 0.3f && m_Scale + change <= 10.0f)
    {
        m_NeedsMatrixUpdate = true;
        m_Scale += change;
    }
}

void Camera2D::setScreenSize(float width, float height)
{
    m_ScreenWidth = width;
    m_ScreenHeight = height;
    m_NeedsMatrixUpdate = true;

    m_OrthographicMatrix.setToIdentity();
    m_OrthographicMatrix.ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    m_OrthographicMatrix.optimize();
    m_NeedsMatrixUpdate = true;
}

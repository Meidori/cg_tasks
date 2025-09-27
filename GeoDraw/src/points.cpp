#include "points.h"

Points::Points(QObject* parent)
    : QObject(parent), 
      m_firstPoint(NAN, NAN, NAN), 
      m_secondPoint(NAN, NAN, NAN),
      m_thirdPoint(NAN, NAN, NAN) 
{}

void Points::setFirstPoint(const QVector3D& point)
{
    if (m_firstPoint == point) return;
    m_firstPoint = point;
    emit pointsChanged();
}

void Points::setSecondPoint(const QVector3D& point)
{
    if (m_secondPoint == point) return;
    m_secondPoint = point;
    emit pointsChanged();
}

void Points::setThirdPoint(const QVector3D& point)
{
    if (m_thirdPoint == point) return;
    m_thirdPoint = point;
    emit pointsChanged();
}

int Points::pointsCount()
{
    bool isFirstEmpty = std::isnan(m_firstPoint.x()) && std::isnan(m_firstPoint.y()) && std::isnan(m_firstPoint.z());
    if (isFirstEmpty) return 0;

    bool isSecondEmpty = std::isnan(m_secondPoint.x()) && std::isnan(m_secondPoint.y()) && std::isnan(m_secondPoint.z());
    if (isSecondEmpty) return 1;
    
    bool isThirdEmpty = std::isnan(m_thirdPoint.x()) && std::isnan(m_thirdPoint.y()) && std::isnan(m_thirdPoint.z());
    if (isThirdEmpty) return 2;

    return 3;
}

void Points::removeLastPoint()
{
    int pts = pointsCount();
    bool changed = false;
    
    if (pts == 0) return;
    else if (pts == 1)
    {
        m_firstPoint = QVector3D(NAN, NAN, NAN);
        changed = true;
    }
    else if (pts == 2)
    {
        m_secondPoint = QVector3D(NAN, NAN, NAN);
        changed = true;
    }
    else if (pts == 3)
    {
        m_thirdPoint = QVector3D(NAN, NAN, NAN);
        changed = true;
    }

    if (changed) emit pointsChanged();
}

void Points::removeAllPoints()
{
    m_firstPoint = QVector3D(NAN, NAN, NAN);
    m_secondPoint = QVector3D(NAN, NAN, NAN);
    m_thirdPoint = QVector3D(NAN, NAN, NAN);
    emit pointsChanged();
}

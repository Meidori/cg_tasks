#include "points.h"
#include <QDebug>

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
    calcHeight();
    calcMedian();
    calcBisector();
    emit pointsChanged();
}

void Points::calcHeight()
{
    double x1 = m_firstPoint.x();
    double y1 = m_firstPoint.y();
    double x2 = m_secondPoint.x();
    double y2 = m_secondPoint.y();
    double x3 = m_thirdPoint.x();
    double y3 = m_thirdPoint.y();

    if ((x2 - x1) * (y3 - y1) == (y2 - y1) * (x3 - x1)) return;

    m_A1 = y1 - y2;
    m_B1 = x2 - x1;
    m_C1 = x1 * y2 - x2 * y1;

    double x4 = (m_B1*m_B1*x3 - m_A1*m_B1*y3 - m_A1*m_C1) / (std::pow(m_A1, 2) + std::pow(m_B1, 2));
    double y4 = (m_A1*m_A1*y3 - m_A1*m_B1*x3 - m_B1*m_C1) / (std::pow(m_A1, 2) + std::pow(m_B1, 2));

    m_Ah = y2 - y4;
    m_Bh = x4 - x2;
    m_Ch = x2 * y4 - x4 * y2;

    m_heightPoint = QVector3D(x4, y4, 1);

    emit pointsChanged();
}

void Points::calcMedian()
{
    double x1 = m_firstPoint.x();
    double y1 = m_firstPoint.y();
    double x2 = m_secondPoint.x();
    double y2 = m_secondPoint.y();
    double x3 = m_thirdPoint.x();
    double y3 = m_thirdPoint.y();

    if ((x2 - x1) * (y3 - y1) == (y2 - y1) * (x3 - x1)) return;

    m_A1 = y2 - y1;
    m_B1 = x1 - x2;
    m_C1 = x2 * y1 - x1 * y2;

    double mid_x = (x1 + x2) / 2.0;
    double mid_y = (y1 + y2) / 2.0;
    
    m_Am = mid_y - y3;
    m_Bm = x3 - mid_x;
    m_Cm = mid_x * y3 - x3 * mid_y;

    double determinant = m_A1 * m_Bm - m_Am * m_B1;
    
    if (fabs(determinant) < 1e-10) return;
    
    double x4 = (m_B1 * m_Cm - m_Bm * m_C1) / determinant;
    double y4 = (m_Am * m_C1 - m_A1 * m_Cm) / determinant;

    m_medianPoint = QVector3D(x4, y4, 1);
    emit pointsChanged();
}

void Points::calcBisector()
{
    double x1 = m_firstPoint.x();
    double y1 = m_firstPoint.y();
    double x2 = m_secondPoint.x();
    double y2 = m_secondPoint.y();
    double x3 = m_thirdPoint.x();
    double y3 = m_thirdPoint.y();

    if ((x2 - x1) * (y3 - y1) == (y2 - y1) * (x3 - x1)) return;

    m_A1 = y2 - y1;
    m_B1 = x1 - x2;
    m_C1 = x2 * y1 - x1 * y2;

    m_A2 = y3 - y2;
    m_B2 = x2 - x3;
    m_C2 = x3 * y2 - x2 * y3; 

    double d1 = std::sqrt(std::pow(x2 - x3, 2) + std::pow(y2 - y3, 2));  // distance 2 - 3
    double d2 = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));  // distance 2 - 1

    double x_bisector = (d1 * x1 + d2 * x3) / (d1 + d2);
    double y_bisector = (d1 * y1 + d2 * y3) / (d1 + d2);

    m_bisectorPoint = QVector3D(x_bisector, y_bisector, 1);

    m_Ab = y_bisector - y2;
    m_Bb = x2 - x_bisector;
    m_Cb = x_bisector * y2 - x2 * y_bisector;
        
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
        m_heightPoint = QVector3D(NAN, NAN, NAN);
        m_medianPoint = QVector3D(NAN, NAN, NAN);
        m_bisectorPoint = QVector3D(NAN, NAN, NAN);

        m_A1 = NAN; m_B1 = 0; m_C1 = 0;
        m_A2 = NAN; m_B2 = 0; m_C2 = 0;

        m_Ah = NAN; m_Bh = 0; m_Ch = 0;
        m_Am = NAN; m_Bm = 0; m_Cm = 0;
        m_Ab = NAN; m_Bb = 0; m_Cb = 0;

        changed = true;
    }

    if (changed) emit pointsChanged();
}

void Points::removeAllPoints()
{
    m_firstPoint = QVector3D(NAN, NAN, NAN);
    m_secondPoint = QVector3D(NAN, NAN, NAN);
    m_thirdPoint = QVector3D(NAN, NAN, NAN);
    m_heightPoint = QVector3D(NAN, NAN, NAN);
    m_medianPoint = QVector3D(NAN, NAN, NAN);
    m_bisectorPoint = QVector3D(NAN, NAN, NAN);
    
    m_A1 = NAN; m_B1 = 0; m_C1 = 0;
    m_A2 = NAN; m_B2 = 0; m_C2 = 0;

    m_Ah = NAN; m_Bh = 0; m_Ch = 0;
    m_Am = NAN; m_Bm = 0; m_Cm = 0;
    m_Ab = NAN; m_Bb = 0; m_Cb = 0;
    
    emit pointsChanged();
}

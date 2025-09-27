#pragma once

#include <QObject>
#include <QVector3D>
#include <QPainter>
#include <cmath>

class Points : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector3D firstPoint READ firstPoint WRITE setFirstPoint NOTIFY pointsChanged)
    Q_PROPERTY(QVector3D secondPoint READ secondPoint WRITE setSecondPoint NOTIFY pointsChanged)
    Q_PROPERTY(QVector3D thirdPoint READ thirdPoint WRITE setThirdPoint NOTIFY pointsChanged)
    Q_PROPERTY(QVector3D heightPoint READ heightPoint NOTIFY pointsChanged)
    // Q_PROPERTY(QVector3D medianPoint READ medianPoint NOTIFY pointsChanged)
    // Q_PROPERTY(QVector3D bisectorPoint READ bisectorPoint NOTIFY pointsChanged)

public:
    Points(QObject* parent = nullptr);

    QVector3D firstPoint() { return m_firstPoint; }
    QVector3D secondPoint() { return m_secondPoint; }
    QVector3D thirdPoint() { return m_thirdPoint; }
    QVector3D heightPoint() { return m_heightPoint; }
    QVector3D medianPoint() { return m_medianPoint; }
    QVector3D bisectorPoint() { return m_bisectorPoint; }

    void setFirstPoint(const QVector3D& point);
    void setSecondPoint(const QVector3D& point);
    void setThirdPoint(const QVector3D& point);

    Q_INVOKABLE int pointsCount();
    Q_INVOKABLE void removeLastPoint();
    Q_INVOKABLE void removeAllPoints();

    void calcHeight(); 

signals:
    void pointsChanged();

private:
    QVector3D m_firstPoint;
    QVector3D m_secondPoint;
    QVector3D m_thirdPoint;

    double A1;
    double B1;
    double C1;
    
    QVector3D m_heightPoint = QVector3D(NAN, NAN, NAN);
    QVector3D m_medianPoint = QVector3D(NAN, NAN, NAN);
    QVector3D m_bisectorPoint = QVector3D(NAN, NAN, NAN);
};

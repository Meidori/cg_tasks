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

public:
    Points(QObject* parent = nullptr);

    QVector3D firstPoint() { return m_firstPoint; }
    QVector3D secondPoint() { return m_secondPoint; }
    QVector3D thirdPoint() { return m_thirdPoint; }

    void setFirstPoint(const QVector3D& point);
    void setSecondPoint(const QVector3D& point);
    void setThirdPoint(const QVector3D& point);

    Q_INVOKABLE int pointsCount();
    Q_INVOKABLE void removeLastPoint();
    Q_INVOKABLE void removeAllPoints();

signals:
    void pointsChanged();

private:
    QVector3D m_firstPoint;
    QVector3D m_secondPoint;
    QVector3D m_thirdPoint;
};

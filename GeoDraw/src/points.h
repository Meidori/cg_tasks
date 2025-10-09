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
    Q_PROPERTY(QVector3D medianPoint READ medianPoint NOTIFY pointsChanged)
    Q_PROPERTY(QVector3D bisectorPoint READ bisectorPoint NOTIFY pointsChanged)

    Q_PROPERTY(double A1 READ A1 NOTIFY pointsChanged)
    Q_PROPERTY(double B1 READ B1 NOTIFY pointsChanged)
    Q_PROPERTY(double C1 READ C1 NOTIFY pointsChanged)
    Q_PROPERTY(double A2 READ A2 NOTIFY pointsChanged)
    Q_PROPERTY(double B2 READ B2 NOTIFY pointsChanged)
    Q_PROPERTY(double C2 READ C2 NOTIFY pointsChanged)

    Q_PROPERTY(double Ah READ Ah NOTIFY pointsChanged)
    Q_PROPERTY(double Bh READ Bh NOTIFY pointsChanged)
    Q_PROPERTY(double Ch READ Ch NOTIFY pointsChanged)
    Q_PROPERTY(double Am READ Am NOTIFY pointsChanged)
    Q_PROPERTY(double Bm READ Bm NOTIFY pointsChanged)
    Q_PROPERTY(double Cm READ Cm NOTIFY pointsChanged)
    Q_PROPERTY(double Ab READ Ab NOTIFY pointsChanged)
    Q_PROPERTY(double Bb READ Bb NOTIFY pointsChanged)
    Q_PROPERTY(double Cb READ Cb NOTIFY pointsChanged)

public:
    Points(QObject* parent = nullptr);

    QVector3D firstPoint() { return m_firstPoint; }
    QVector3D secondPoint() { return m_secondPoint; }
    QVector3D thirdPoint() { return m_thirdPoint; }
    QVector3D heightPoint() { return m_heightPoint; }
    QVector3D medianPoint() { return m_medianPoint; }
    QVector3D bisectorPoint() { return m_bisectorPoint; }

    double A1() { return m_A1; }
    double B1() { return m_B1; }
    double C1() { return m_C1; }

    double A2() { return m_A2; }
    double B2() { return m_B2; }
    double C2() { return m_C2; }

    double Ah() { return m_Ah; }
    double Bh() { return m_Bh; }
    double Ch() { return m_Ch; }

    double Am() { return m_Am; }
    double Bm() { return m_Bm; }
    double Cm() { return m_Cm; }

    double Ab() { return m_Ab; }
    double Bb() { return m_Bb; }
    double Cb() { return m_Cb; }


    void setFirstPoint(const QVector3D& point);
    void setSecondPoint(const QVector3D& point);
    void setThirdPoint(const QVector3D& point);

    Q_INVOKABLE int pointsCount();
    Q_INVOKABLE void removeLastPoint();
    Q_INVOKABLE void removeAllPoints();

    void calcHeight(); 
    void calcMedian();
    void calcBisector();

signals:
    void pointsChanged();

private:
    QVector3D m_firstPoint;
    QVector3D m_secondPoint;
    QVector3D m_thirdPoint;

    double m_A1 = NAN, m_B1 = NAN, m_C1 = NAN;
    double m_A2 = NAN, m_B2 = NAN, m_C2 = NAN;
    
    QVector3D m_heightPoint = QVector3D(NAN, NAN, NAN);
    QVector3D m_medianPoint = QVector3D(NAN, NAN, NAN);
    QVector3D m_bisectorPoint = QVector3D(NAN, NAN, NAN);

    double m_Ah = NAN, m_Bh = NAN, m_Ch = NAN;
    double m_Am = NAN, m_Bm = NAN, m_Cm = NAN;
    double m_Ab = NAN, m_Bb = NAN, m_Cb = NAN;
};

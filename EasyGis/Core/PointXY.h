#pragma once

#include <QPointF>
#include <QString>

class PointXY
{
public:
    PointXY();
    PointXY(double x, double y);
    PointXY(const QPointF& p);

    double& x();
    double& y();
    const double& x() const;
    const double& y() const;

    PointXY operator*(double v) const;
    PointXY& operator*=(double v);

    QPointF toPointF() const;
    QString toString() const;

private:
    double m_X;
    double m_Y;
};


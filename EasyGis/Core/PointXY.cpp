#include "PointXY.h"

PointXY::PointXY()
    : PointXY(0, 0)
{
}

PointXY::PointXY(double x, double y)
    : m_X(x)
    , m_Y(y)
{
}

PointXY::PointXY(const QPointF& p)
    : PointXY(p.x(), p.y())
{
}

double& PointXY::x()
{
    return m_X;
}

double& PointXY::y()
{
    return m_Y;
}

const double& PointXY::x() const
{
    return m_X;
}

const double& PointXY::y() const
{
    return m_Y;
}

PointXY PointXY::operator*(double v) const
{
    return PointXY{ m_X * v, m_Y * v };
}

PointXY& PointXY::operator*=(double v)
{
    m_X *= v;
    m_Y *= v;
    return *this;
}

QPointF PointXY::toPointF() const
{
    return QPointF{ m_X, m_Y };
}

QString PointXY::toString() const
{
    return QString{ u8"{%1, %2}" }
        .arg(m_X, 0, 'f', 4)
        .arg(m_Y, 0, 'f', 4);
}

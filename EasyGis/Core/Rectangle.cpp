#include "Rectangle.h"

#include <ios>

Rectangle::Rectangle()
    : m_Xmin(0)
    , m_Ymin(0)
    , m_Xmax(0)
    , m_Ymax(0)
{
}

Rectangle::Rectangle(double minX, double minY, double maxX, double maxY)
    : m_Xmin(minX)
    , m_Ymin(minY)
    , m_Xmax(maxX)
    , m_Ymax(maxY)
{
}

double& Rectangle::xMin()
{
    return m_Xmin;
}

double& Rectangle::yMin()
{
    return m_Ymin;
}

double& Rectangle::xMax()
{
    return m_Xmax;
}

double& Rectangle::yMax()
{
    return m_Ymax;
}

const double& Rectangle::xMin() const
{
    return m_Xmin;
}

const double& Rectangle::yMin() const
{
    return m_Ymin;
}

const double& Rectangle::xMax() const
{
    return m_Xmax;
}

const double& Rectangle::yMax() const
{
    return m_Ymax;
}

void Rectangle::set(double minX, double minY, double maxX, double maxY)
{
    m_Xmin = minX;
    m_Ymin = minY;
    m_Xmax = maxX;
    m_Ymax = maxY;
}

void Rectangle::set(const PointXY& center, double width, double height)
{
    double nw_h = width * 0.5;
    double nh_h = height * 0.5;
    set(center.x() - nw_h, center.y() - nh_h, center.x() + nw_h, center.y() + nh_h);
}

double Rectangle::width() const
{
    return m_Xmax - m_Xmin;
}

double Rectangle::height() const
{
    return m_Ymax - m_Ymin;
}

double Rectangle::area() const
{
    return (m_Xmax - m_Xmin) * (m_Ymax - m_Ymin);
}

PointXY Rectangle::leftTop() const
{
    return PointXY{ m_Xmin, m_Ymax };
}

PointXY Rectangle::rightBottom() const
{
    return PointXY{ m_Xmax, m_Ymin };
}

PointXY Rectangle::center() const
{
    return PointXY{ m_Xmin + width() * 0.5, m_Ymin + height() * 0.5 };
}

void Rectangle::scale(double scaleFactor, const PointXY* center)
{
    double centerX;
    double centerY;

    if(center)
    {
        centerX = center->x();
        centerY = center->y();
    }
    else
    {
        centerX = m_Xmin + width() * 0.5;
        centerY = m_Ymin + height() * 0.5;
    }

    double newWidth = width() * scaleFactor;
    double newHeight = height() * scaleFactor;
    double nw_h = newWidth * 0.5;
    double nh_h = newHeight * 0.5;

    set(centerX - nw_h, centerY - nh_h, centerX + nw_h, centerY + nh_h);
}

Rectangle Rectangle::scaled(double scaleFactor, const PointXY* center) const
{
    Rectangle scaledRect = Rectangle(*this);
    scaledRect.scale(scaleFactor, center);
    return scaledRect;
}

bool Rectangle::operator!=(const Rectangle& r) const
{
    return m_Xmin != r.xMin()
        || m_Xmax != r.xMax()
        || m_Ymin != r.yMin()
        || m_Ymax != r.yMax();
}

Rectangle Rectangle::operator+(const PointXY& v) const
{
    const double xmin = m_Xmin + v.x();
    const double xmax = m_Xmax + v.x();
    const double ymin = m_Ymin + v.y();
    const double ymax = m_Ymax + v.y();
    return Rectangle(xmin, ymin, xmax, ymax);
}

Rectangle Rectangle::operator-(const PointXY& v) const
{
    const double xmin = m_Xmin - v.x();
    const double xmax = m_Xmax - v.x();
    const double ymin = m_Ymin - v.y();
    const double ymax = m_Ymax - v.y();
    return Rectangle(xmin, ymin, xmax, ymax);
}

Rectangle& Rectangle::operator+=(const PointXY& v)
{
    m_Xmin += v.x();
    m_Xmax += v.x();
    m_Ymin += v.y();
    m_Ymax += v.y();
    return *this;
}

Rectangle& Rectangle::operator-=(const PointXY& v)
{
    m_Xmin -= v.x();
    m_Xmax -= v.x();
    m_Ymin -= v.y();
    m_Ymax -= v.y();
    return *this;
}

QString Rectangle::toString() const
{
    return QString{ u8"×óÉÏ½Ç: %1\nÓÒÏÂ½Ç: %2" }
        .arg(leftTop().toString())
        .arg(rightBottom().toString());
}

void Rectangle::checkRange()
{
    if(area() > WGS84.area())
    {
        *this = WGS84;
        return;
    }

    double w = width();
    double h = height();

    if(m_Xmin < WGS84.xMin())
    {
        m_Xmin = WGS84.xMin();
        m_Xmax = m_Xmin + w;
    }
    if(m_Xmax > WGS84.xMax())
    {
        m_Xmax = WGS84.xMax();
        m_Xmin = m_Xmax - w;
    }
    if (m_Ymin < WGS84.yMin())
    {
        m_Ymin = WGS84.yMin();
        m_Ymax = m_Ymin + h;
    }
    if (m_Ymax > WGS84.yMax())
    {
        m_Ymax = WGS84.yMax();
        m_Ymin = m_Ymax - h;
    }

}

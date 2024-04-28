#pragma once

#include <cmath>
#include <limits>
#include <algorithm>

#include "PointXY.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(double minX, double minY, double maxX, double maxY);

    double& xMin();
    double& yMin();
    double& xMax();
    double& yMax();

    const double& xMin() const;
    const double& yMin() const;
    const double& xMax() const;
    const double& yMax() const;

    void set(double minX, double minY, double maxX, double maxY);
    void set(const PointXY& center, double width, double height);

    double width() const;
    double height() const;
    double area() const;

    PointXY leftTop() const;
    PointXY rightBottom() const;
    PointXY center() const;

    void scale(double scaleFactor, const PointXY* center = nullptr);
    Rectangle scaled(double scaleFactor, const PointXY* center = nullptr) const;

    bool operator!=(const Rectangle& r) const;
    Rectangle operator+(const PointXY& v) const;
    Rectangle operator-(const PointXY& v) const;
    Rectangle& operator+=(const PointXY& v);
    Rectangle& operator-=(const PointXY& v);

    QString toString() const;

    void checkRange();

private:
    double m_Xmin;
    double m_Ymin;
    double m_Xmax;
    double m_Ymax;
};

static const Rectangle WGS84 = { -20037508.3427892439067364,-20037508.3427892476320267, 20037508.3427892439067364,20037508.3427892476320267 };
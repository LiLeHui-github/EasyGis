#include "Vector3D.h"

Vector3D::Vector3D()
    : m_X(0)
    , m_Y(0)
    , m_Z(0)
{
}

Vector3D::Vector3D(double x, double y, double z)
    : m_X(x)
    , m_Y(y)
    , m_Z(z)
{
}

double& Vector3D::x()
{
    return m_X;
}

double& Vector3D::y()
{
    return m_Y;
}

double& Vector3D::z()
{
    return m_Z;
}

const double& Vector3D::x() const
{
    return m_X;
}

const double& Vector3D::y() const
{
    return m_Y;
}

const double& Vector3D::z() const
{
    return m_Z;
}

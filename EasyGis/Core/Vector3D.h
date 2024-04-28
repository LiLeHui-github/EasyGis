#pragma once

class Vector3D
{
public:
    Vector3D();
    Vector3D(double x, double y, double z);

    double& x();
    double& y();
    double& z();
    const double& x() const;
    const double& y() const;
    const double& z() const;

private:
    double m_X;
    double m_Y;
    double m_Z;
};


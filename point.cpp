#include "point.h"

Point::Point(double a, double b, double c) :
    x(a), y(b), z(c) {}

Point::Point(QList<double> v) :
    x(v[0]), y(v[1]), z(v[2]) {}

Point::Point() :
    x(0.0), y(0.0), z(0.0){}

Point Point::operator+(Point p)
{
    return Point(p.x + x, p.y + y, p.z + z);
}

Point Point::operator-(Point p)
{
    return Point(p.x - x, p.y - y, p.z - z);
}

Point Point::operator*(double val)
{
    return Point(x * val, y * val, z * val);
}

Point Point::operator*(Point p)
{
    return Point(p.x * x, p.y * y, p.z * z);
}

Point Point::operator/(double val)
{
    return Point(x/val, y/val, z/val);
}

double Point::dot(Point p)
{
    return p.x * x + p.y * y + p.z * z;
}

double Point::norm2()
{
    return qSqrt(x*x + y*y + z*z);
}

void Point::normalize(double val)
{
    double norm = qAbs(x) + qAbs(y) + qAbs(z);

    x = (x * val) / norm;
    y = (y * val) / norm;
    z = (z * val) / norm;
}







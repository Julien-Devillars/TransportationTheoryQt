#ifndef POINT_H
#define POINT_H

#include <QList>
#include <QtMath>

class Point
{

public:
    Point(double a, double b, double c);

    Point(QList<double> v);
    Point();

    Point operator+(Point p);
    Point operator-(Point p);
    Point operator*(double val);
    Point operator*(Point p);
    Point operator/(double val);

    double dot(Point p);
    double norm2();
    void normalize(double val);

    double x;
    double y;
    double z;
};

#endif // POINT_H

#ifndef _GEOMETRY_HEADER
#define _GEOMETRY_HEADER

struct Point
{
public:
    Point();
    Point(double x, double y);

    double x() const;
    double y() const;
    double dim(std::size_t d) const;
private:
    double p_x, p_y;
};

Point::Point()
{
    p_x = 0;
    p_y = 0;
}

Point::Point(double x, double y): p_x(x), p_y(y) {}

double Point::x() const
{
    return p_x;
}

double Point::y() const
{
    return p_y;
}

double Point::dim(std::size_t d) const
{
    if (d == 0)
        return p_x;
    else if (d == 1)
    {
        return p_y;
    }
    return -1;
}

struct Range
{
    Range() {};
    Range(double mi, double ma): p_min(mi), p_max(ma) {};

    double min() const;
    double max() const;
private:
    double p_min, p_max;
};

double Range::min() const
{
    return p_min;
}

double Range::max() const
{
    return p_max;
}

struct Rectangle
{
    Rectangle(double xMin, double xMax, double yMin, double yMax);

    Range dim(std::size_t d) const;
private:
    double p_xMin, p_xMax, p_yMin, p_yMax;
};

Rectangle::Rectangle(double xMin, double xMax, double yMin, double yMax):
    p_xMin(xMin), p_xMax(xMax), p_yMin(yMin), p_yMax(yMax) {}

Range Rectangle::dim(std::size_t d) const
{
    if (d == 0)
        return Range(p_xMin, p_xMax);
    else if (d == 1)
        return Range(p_yMin, p_yMax);
    return Range();
}

#endif

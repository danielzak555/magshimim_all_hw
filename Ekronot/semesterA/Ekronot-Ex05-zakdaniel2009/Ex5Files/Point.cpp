#include "Point.h"
#include <cmath>

Point::Point()
	: _x(0), _y(0)
{
}

Point::Point(double x, double y)
	: _x(x), _y(y)
{
}


Point Point::operator+(const Point& other) const {
	return Point(_x + other._x, _y + other._y);
}
Point& Point::operator+=(const Point& other) {
	this->_x += other._x;
	this->_y += other._y;
	return *this;
}

double Point::getX() const {
	return _x;
}
double Point::getY() const {
	return _y;
}

double Point::distance(const Point& other) const{
	return sqrt(pow(other._x - _x, 2) + pow(other._y - _y, 2));
}
#include "Polygon.h"

Polygon::Polygon(const std::string& type, const std::string& name) 
	:Shape(name, type)
{
}


std::vector<Point> Polygon::getPoints() const {
	return _points;
}

double Polygon::getPerimeter() const {
	double perimeter = 0.0;
	int i = 0;
	for (i = 0; i < _points.size() - 1; i++) {
		perimeter += _points[i].distance(_points[i + 1]);
	}
	perimeter += _points[i].distance(_points[0]);
	return perimeter;
}
void Polygon::move(const Point& other) {
	int i = 0;
	for (i = 0; i < _points.size(); i++) {
		_points[i] += other;
	}
}
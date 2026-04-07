#include "Triangle.h"
#include <cmath>

Triangle::Triangle(const Point& a, const Point& b, const Point& c, const std::string& type, const std::string& name)
	:Polygon(type, name)
{
	if ((b.getY() - a.getY()) * (c.getX() - b.getX()) - (c.getY() - b.getY()) * (b.getX() - a.getX()) == 0) {
		exit(1);
	}
	else {
		_points.push_back(a);
		_points.push_back(b);
		_points.push_back(c);
	}
}


double Triangle::getArea() const {
	double a = _points[0].distance(_points[1]);
	double b = _points[1].distance(_points[2]);
	double c = _points[2].distance(_points[0]);
	double s = (a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));

}

//////////////////////////////////////////////////////////////////////////////
// Canvas and Cimg cannot be used on Linux, 								//
// please make sure to leave it commented if you want test to run on GitLab //
// You can remove comments when you run your exercise locally on Windows .  //
//////////////////////////////////////////////////////////////////////////////

// void Triangle::draw(const Canvas& canvas)
// {
// 	canvas.draw_triangle(_points[0], _points[1], _points[2]);
// }

// void Triangle::clearDraw(const Canvas& canvas)
// {
// 	canvas.clear_triangle(_points[0], _points[1], _points[2]);
// }

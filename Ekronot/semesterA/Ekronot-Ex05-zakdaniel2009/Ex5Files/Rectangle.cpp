#include "Rectangle.h"

myShapes::Rectangle::Rectangle(const Point& a, const double length, const double width, const std::string& type, const std::string& name) 
	: Polygon(type, name), _a(a)
{
	if (length == 0 || width == 0) {
		exit(1);
	}
	else {
		_length = std::abs(length);
		_width = std::abs(width);
		_points.push_back(_a);
		_points.push_back(Point(_a.getX() + _length, _a.getY()));
		_points.push_back(Point(_a.getX() + _length, _a.getY() + _width));
		_points.push_back(Point(_a.getX(), _a.getY() + _width));
	}
}


double myShapes::Rectangle::getArea() const {
	return _length * _width;
}

//////////////////////////////////////////////////////////////////////////////
// Canvas and Cimg cannot be used on Linux, 								//
// please make sure to leave it commented if you want test to run on GitLab //
// You can remove comments when you run your exercise locally on Windows .  //
//////////////////////////////////////////////////////////////////////////////

// void myShapes::Rectangle::draw(const Canvas& canvas)
// {
// 	canvas.draw_rectangle(_points[0], _points[1]);
// }

// void myShapes::Rectangle::clearDraw(const Canvas& canvas)
// {
// 	canvas.clear_rectangle(_points[0], _points[1]);
// }



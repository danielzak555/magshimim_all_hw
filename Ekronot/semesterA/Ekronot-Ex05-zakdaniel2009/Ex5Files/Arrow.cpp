#include "Arrow.h"
 

Arrow::Arrow(const Point& a, const Point& b, const std::string& type, const std::string& name)
	: Shape(name, type)
{
	if (a.getX() == b.getX() && a.getY() == b.getY()) {
		exit(1);
	}
	_source = a;
	_destination = b;
}


// Getters
Point Arrow::getSource() const {
	return _source;
}
Point Arrow::getDestination() const {
	return _destination;
}

double Arrow::getArea() const {
	return 0.0;
}
double Arrow::getPerimeter() const {
	return _source.distance(_destination);
}
void Arrow::move(const Point& other) {
	_source += other;
	_destination += other;
}

//////////////////////////////////////////////////////////////////////////////
// Canvas and Cimg cannot be used on Linux, 								//
// please make sure to leave it commented if you want test to run on GitLab //
// You can remove comments when you run your exercise locally on Windows .  //
//////////////////////////////////////////////////////////////////////////////

// void Arrow::draw(const Canvas& canvas)
// {
// 	canvas.draw_arrow(_points[0], _points[1]);
// }
// void Arrow::clearDraw(const Canvas& canvas)
// {
// 	canvas.clear_arrow(_points[0], _points[1]);
// }



#include "Circle.h"

Circle::Circle(const Point& center, const double radius, const std::string& type, const std::string& name) 
	: Shape(name, type), _center(center)
{
	if (radius <= 0) {
		exit(1);
	}
	_radius = radius;
}


// Getters
Point Circle::getCenter() const {
	return _center;

}
double Circle::getRadius() const {
	return _radius;
}

double Circle::getArea() const {
	return PI * _radius * _radius;
}
double Circle::getPerimeter() const {
	return 2 * PI * _radius;
}
void Circle::move(const Point& other) {
	_center += other;
}


//////////////////////////////////////////////////////////////////////////////
// Canvas and Cimg cannot be used on Linux, 								//
// please make sure to leave it commented if you want test to run on GitLab //
// You can remove comments when you run your exercise locally on Windows .  //
//////////////////////////////////////////////////////////////////////////////

// void Circle::draw(const Canvas& canvas)
// {
// 	canvas.draw_circle(getCenter(), getRadius());
// }

// void Circle::clearDraw(const Canvas& canvas)
// {
// 	canvas.clear_circle(getCenter(), getRadius());
// }



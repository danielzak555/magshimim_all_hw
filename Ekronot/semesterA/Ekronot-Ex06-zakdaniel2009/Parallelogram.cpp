#include "Parallelogram.h"
#include "ShapeException.h"
#include <iostream>


Parallelogram::Parallelogram(std::string col, std::string nam, int h, int w, double ang, double ang2):Quadrilateral(col, nam, h, w) {
	 setAngle(ang, ang2);
}
void Parallelogram::draw()
{
	std::cout <<getName()<< std::endl << getColor() << std::endl << "Height is " << getHeight() << std::endl<< "Width is " << getWidth() << std::endl
		<< "Angles are: " << getAngle()<<","<<getAngle2()<< std::endl <<"Area is "<<CalArea(getWidth(),getHeight())<< std::endl;
}

double Parallelogram::CalArea(double w, double h) {
	if (w < 0 || h < 0)
	{
		throw ShapeException();
	}
	return w*h;
}
void Parallelogram::setAngle(double ang, double ang2) {
	if (!((ang == 0 && ang2 == 180) || (ang > 0 && ang < 180 && ang2 > 0 && ang2 < 180))) {
		throw ShapeException();
	}
	angle = ang;
	angle2 = ang2;
}
double Parallelogram::getAngle() {
	return angle;
}
double Parallelogram::getAngle2() {
		return angle2;
	}

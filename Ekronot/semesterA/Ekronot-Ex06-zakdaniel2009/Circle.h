#pragma once
#include "Shape.h"

class Circle: public Shape {

public:
	void draw();
	double CalArea();
	double CalCircumference();
	Circle(std::string, std::string, double);
	void setRad(double rad);
	double getRad();
private:
	double radius;


};
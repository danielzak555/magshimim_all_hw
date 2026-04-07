#pragma once

#include "Shape.h"


class Quadrilateral :public Shape {
public:
	void draw();
	double CalArea();
	//Quadrilateral();
	Quadrilateral(std::string, std::string, int, int);
	double CalPerimater();
	double getCalPerimater();
	void setHeight(int h);
	void setWidth(int w);
	int getHeight();
	int getWidth();


private:
	int width;
	int height;

};
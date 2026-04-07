#pragma once
#include "Quadrilateral.h"
#include <iostream>

class Parallelogram : public Quadrilateral {

public:
	Parallelogram(std::string col, std::string nam, int h, int w, double ang, double ang2);
	void draw();

		void setAngle(double, double);
		double getAngle2();
		double getAngle();
		double CalArea(double w, double h);
private:
	double angle;
	double angle2;






};
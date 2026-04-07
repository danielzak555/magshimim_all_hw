#pragma once

#include "Shape.h"
#include "Point.h"

#define PI 3.14

class Circle : public Shape
{
public:

	// Constructor
	Circle(const Point& center, const double radius,const std::string& type, const std::string& name);


	// Getters
	Point getCenter() const;
	double getRadius() const;
	
	double getArea() const override;
	double getPerimeter() const override;
	void move(const Point& other) override;

	//////////////////////////////////////////////////////////////////////////////
	// Canvas and Cimg cannot be used on Linux, 								//
	// please make sure to leave it commented if you want test to run on GitLab //
	// You can remove comments when you run your exercise locally on Windows .  //
	//////////////////////////////////////////////////////////////////////////////

	// virtual void draw(const Canvas& canvas);
	// virtual void clearDraw(const Canvas& canvas);

private:

	Point _center;
	double _radius;

};
#pragma once
#include "Shape.h"

class Arrow : public Shape
{
public:

	// Constructor
	Arrow(const Point& a, const Point& b, const std::string& type, const std::string& name);


	// Getters
	Point getSource() const;
	Point getDestination() const;

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

	Point _source;
	Point _destination;
};
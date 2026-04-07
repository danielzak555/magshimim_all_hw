#pragma once
#include "Polygon.h"


namespace myShapes
{
	// Calling it MyRectangle becuase Rectangle is taken by global namespace.
	class Rectangle : public Polygon
	{
	public:

		// Constructor
		// There's a need only for the top left corner 
		Rectangle(const Point& a, const double length, const double width, const std::string& type, const std::string& name);


		double getArea() const override;

		//////////////////////////////////////////////////////////////////////////////
		// Canvas and Cimg cannot be used on Linux, 								//
		// please make sure to leave it commented if you want test to run on GitLab //
		// You can remove comments when you run your exercise locally on Windows .  //
		//////////////////////////////////////////////////////////////////////////////

		// virtual void draw(const Canvas& canvas);
		// virtual void clearDraw(const Canvas& canvas);

	private:
	
		Point _a;
		double _length;
		double _width;

	};
}
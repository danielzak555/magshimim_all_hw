 #include "Polygon.h"
#include <string>

class Triangle : public Polygon
{
public:

	// Constructor
	Triangle(const Point& a, const Point& b, const Point& c, const std::string& type, const std::string& name);

	
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
	Point _b;
	Point _c;
};
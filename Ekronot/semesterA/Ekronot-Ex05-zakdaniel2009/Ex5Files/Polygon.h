#pragma once

#include "Shape.h"
#include "Point.h"
#include <vector>

class Polygon : public Shape
{
public:

	// Constructor
	Polygon(const std::string& type, const std::string& name);

	// Destructor
	virtual ~Polygon() = default;

	// Getters
	std::vector<Point> getPoints() const;

	double getPerimeter() const override;
	void move(const Point& other) override;

protected:
	std::vector<Point> _points;
};
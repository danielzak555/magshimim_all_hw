#pragma once
#include "Shape.h"
#include "ShapeException.h"

class Hexagon : public Shape {
private:
    double side;
public:
    Hexagon(std::string col, std::string nam, double s);
    void setSide(double s);
    double getSide();
    double CalArea() override;
    void draw() override;
};

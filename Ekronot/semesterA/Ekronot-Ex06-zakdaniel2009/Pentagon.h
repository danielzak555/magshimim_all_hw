#pragma once
#include "Shape.h"
#include "MathUtils.h"
#include "ShapeException.h"
#include <iostream>

class Pentagon : public Shape {
private:
    double side;
public:
    Pentagon(std::string col, std::string nam, double s);

    void setSide(double s);

    double getSide();

    double CalArea() override;

    void draw() override;
};

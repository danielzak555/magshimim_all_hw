#include "Hexagon.h"
#include "MathUtils.h"
#include <iostream>

Hexagon::Hexagon(std::string col, std::string nam, double s) : Shape(col, nam) {
    setSide(s);
}

void Hexagon::setSide(double s) {
    if (s <= 0) throw ShapeException();
    side = s;
}

double Hexagon::getSide() {
    return side; 
}

double Hexagon::CalArea() {
    return MathUtils::CalHexagonArea(side);
}

void Hexagon::draw() {
    std::cout << "Hexagon: " << getName() << "\nColor: " << getColor()
        << "\nSide: " << side << "\nArea: " << CalArea() << std::endl;
}

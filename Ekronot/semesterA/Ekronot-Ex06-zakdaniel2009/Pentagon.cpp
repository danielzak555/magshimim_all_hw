#include "Pentagon.h"
#include "MathUtils.h"
#include <iostream>

Pentagon::Pentagon(std::string col, std::string nam, double s) : Shape(col, nam) {
    setSide(s);
}

void Pentagon::setSide(double s) {
    if (s <= 0) throw ShapeException();
    side = s;
}

double Pentagon::getSide() { 
    return side; 
}

double Pentagon::CalArea() {
    return MathUtils::CalPentagonArea(side);
}

void Pentagon::draw() {
    std::cout << "Pentagon: " << getName() << "\nColor: " << getColor()
        << "\nSide: " << side << "\nArea: " << CalArea() << std::endl;
}

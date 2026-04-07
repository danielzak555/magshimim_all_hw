#include "Shape.h"
#include <iostream>

Shape::Shape(const std::string& name, const std::string& type)
	: _type(type), _name(name)
{
}


// Getters
std::string Shape::getType() const {
	return _type;
}
std::string Shape::getName() const {
	return _name;
}

// Methods
void Shape::printDetails() const {
	std::cout << _type << "    " << _name << "    " << this->getArea() << "    " << this->getPerimeter() << "\n";
}
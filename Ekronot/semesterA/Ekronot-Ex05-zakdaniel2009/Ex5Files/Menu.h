#pragma once
#include "Shape.h"
#include "Canvas.h"
#include <vector>

class Menu
{
public:
	Menu();
	~Menu();

	void run();

private:

	void printMainMenu() const;
	void printShapeTypes() const;
	void printShapeSubMenu() const;

	void addNewShape();
	void addCircle();
	void addRectangle();
	void addTriangle();
	void addArrow();

	void interactWithShape();
	void moveShape(Shape* shape);
	void removeShape(int index);

	void deleteAllShapes();

	void listShapes() const;

	Canvas _canvas;
	std::vector<Shape*> _shapes;
};
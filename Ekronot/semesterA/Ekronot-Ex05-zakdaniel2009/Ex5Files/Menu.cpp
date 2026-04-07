#include "Menu.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Arrow.h"
#include <iostream>

namespace myShapes {
	class Rectangle;
}


Menu::Menu()
{
}

Menu::~Menu()
{
	deleteAllShapes();
}


void Menu::printMainMenu() const
{
	std::cout << "Enter 0 to add a new shape.\n";
	std::cout << "Enter 1 to modify or get information from a current shape.\n";
	std::cout << "Enter 2 to delete all of the shapes.\n";
	std::cout << "Enter 3 to exit.\n";
}

void Menu::printShapeTypes() const
{
	std::cout << "Enter 0 to add a circle.\n";
	std::cout << "Enter 1 to add an arrow.\n";
	std::cout << "Enter 2 to add a triangle.\n";
	std::cout << "Enter 3 to add a rectangle.\n";
}

void Menu::printShapeSubMenu() const
{
	std::cout << "Enter 0 to move the shape\n";
	std::cout << "Enter 1 to get its details.\n";
	std::cout << "Enter 2 to remove the shape.\n";
}

void Menu::listShapes() const
{
	if (_shapes.empty())
	{
		std::cout << "\nNo shapes available.\n";
		return;
	}
	for (size_t i = 0; i < _shapes.size(); ++i)
	{
		std::cout << "Enter " << i << "for " << _shapes[i]->getName() << " (" << _shapes[i]->getType() << ")\n";
	}
}


void Menu::addNewShape()
{
	printShapeTypes();
	int choice;
	std::cin >> choice;


	switch (choice)
	{
	case 0: addCircle(); break;
	case 1: addArrow(); break;
	case 2: addTriangle(); break;
	case 3: addRectangle(); break;
	default: std::cout << "Invalid shape type.\n"; break;
	}
}

void Menu::addCircle()
{
	double x, y, r;
	std::string name;
	std::cout << "Please enter X:\n";
	std::cin >> x;
	std::cout << "Please enter Y:\n";
	std::cin >> y;
	std::cout << "Please enter radius:\n";
	std::cin >> r;
	std::cout << "Please enter the name of the shape:\n";
	std::cin >> name;

	Shape* s = new Circle(Point(x, y), r, "Circle", name);
	_shapes.push_back(s);

	// s->draw(_canvas); 

}

void Menu::addRectangle()
{
	double x, y, len, wid;
	std::string name;
	std::cout << "Enter the X of the to left corner:\n";
	std::cin >> x;
	std::cout << "Enter the Y of the to left corner:\n";
	std::cin >> y;
	std::cout << "Please enter the length of the shape:\n";
	std::cin >> len;
	std::cout << "Please enter the width of the shape:\n";
	std::cin >> wid;
	std::cout << "Please enter the name of the shape:\n";
	std::cin >> name;


	Shape* s = new myShapes::Rectangle(Point(x, y), len, wid, "Rectangle", name);
	_shapes.push_back(s);

	// s->draw(_canvas);

}

void Menu::addTriangle()
{
	double x1, y1, x2, y2, x3, y3;
	std::string name;
	std::cout << "Enter the X of point number: 1\n";
	std::cin >> x1;
	std::cout << "Enter the Y of point number: 1\n";
	std::cin >> y1;
	std::cout << "Enter the X of point number: 2\n";
	std::cin >> x2;
	std::cout << "Enter the Y of point number: 2\n";
	std::cin >> y2;
	std::cout << "Enter the X of point number: 3\n";
	std::cin >> x3;
	std::cout << "Enter the Y of point number: 3\n";
	std::cin >> y3;
	std::cout << "Please enter the name of the shape:\n";
	std::cin >> name;

	Shape* s = new Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3), "Triangle", name);
	_shapes.push_back(s);

	// s->draw(_canvas);

}

void Menu::addArrow()
{
	double x1, y1, x2, y2;
	std::string name;
	std::cout << "Enter the X of point number: 1\n";
	std::cin >> x1;
	std::cout << "Enter the Y of point number: 1\n";
	std::cin >> y1;
	std::cout << "Enter the X of point number: 2\n";
	std::cin >> x2;
	std::cout << "Enter the Y of point number: 2\n";
	std::cin >> y2;
	std::cout << "Please enter the name of the shape:\n";
	std::cin >> name;

	Shape* s = new Arrow(Point(x1, y1), Point(x2, y2), "Arrow", name);
	_shapes.push_back(s);

	// s->draw(_canvas);

}


void Menu::interactWithShape()
{
	listShapes();
	int index;
	std::cin >> index;

	while (index < 0 || index >= _shapes.size()) {
		std::cin >> index;
	}

	Shape* selectedShape = _shapes[index];
	printShapeSubMenu();

	int act;
	std::cin >> act;

	switch (act)
	{
	case 0:
		moveShape(selectedShape);
		break;
	case 1:
		selectedShape->printDetails();
		break;
	case 2:
		removeShape(index);
		break;
	default:
		break;
	}
}

void Menu::moveShape(Shape* shape)
{
	double dx, dy;
	std::cout << "Please enter the X moving scale:\n";
	std::cin >> dx;
	std::cout << "Please enter the Y moving scale:";
	std::cin >> dy;
	Point moveVec(dx, dy);

	// shape->clearDraw(_canvas); 

	shape->move(moveVec);

	// shape->draw(_canvas);
}

void Menu::removeShape(int index)
{
	Shape* s = _shapes[index];

	// s->clearDraw(_canvas); 

	std::string name = s->getName();
	delete s;
	_shapes.erase(_shapes.begin() + index);

	// for (Shape* remaining : _shapes) {
	//     remaining->draw(_canvas);
	// }

	std::cout << "Shape '" << name << "' removed.\n";
}

void Menu::deleteAllShapes()
{
	for (int i = 0; i < _shapes.size(); i ++)
	{
		// s->clearDraw(_canvas);
		Shape* s = _shapes[i];
		delete s;
	}
	_shapes.clear();
}


void Menu::run()
{
	int choice = 0;
	while (true)
	{
		printMainMenu();
		std::cin >> choice;

		switch (choice)
		{
		case 0: addNewShape(); break;
		case 1: interactWithShape(); break;
		case 2: deleteAllShapes(); break;
		case 3:
			return;
		}
	}
}
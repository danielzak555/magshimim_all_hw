#include "Pentagon.h"
#include "Hexagon.h"
#include "Circle.h"
#include "Quadrilateral.h"
#include "Rectangle.h"
#include "Parallelogram.h"
#include "ShapeException.h"
#include "InputException.h"
#include <iostream>
#include <string>

int main()
{
    std::string nam, col; double rad = 0, ang = 0, ang2 = 180; int height = 0, width = 0;
    Circle circ(col, nam, rad);
    Quadrilateral quad(nam, col, width, height);
    rectangle rec(nam, col, width, height);
    Parallelogram para(nam, col, width, height, ang, ang2);

    Shape* ptrcirc = &circ;
    Shape* ptrquad = &quad;
    Shape* ptrrec = &rec;
    Shape* ptrpara = &para;

    std::cout << "Enter information for your objects" << std::endl;
    const char circle = 'c', quadrilateral = 'q', rectangle = 'r', parallelogram = 'p';
    const char pentagon = 'n', hexagon = 'h';
    char shapetype;
    char x = 'y';

    while (x != 'x') {
        std::cout << "which shape would you like to work with?.. \n"
            << "c=circle, q=quadrilateral, r=rectangle, p=parallelogram, n=pentagon, h=hexagon" << std::endl;
        std::cin >> shapetype;
        std::cin.ignore(10000, '\n');

        if (shapetype != 'c' && shapetype != 'q' && shapetype != 'r' && shapetype != 'p'
            && shapetype != 'n' && shapetype != 'h') {
            std::cout << "Warning – Don’t try to build more than one shape at once" << std::endl;
            continue;
        }

        try {
            switch (shapetype) {
            case 'c':
                std::cout << "enter color, name,  rad for circle" << std::endl;
                std::cin >> col >> nam >> rad;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw InputException();
                }
                circ.setColor(col);
                circ.setName(nam);
                circ.setRad(rad);
                ptrcirc->draw();
                break;
            case 'q':
                std::cout << "enter name, color, height, width" << std::endl;
                std::cin >> nam >> col >> height >> width;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw InputException();
                }
                quad.setName(nam);
                quad.setColor(col);
                quad.setHeight(height);
                quad.setWidth(width);
                ptrquad->draw();
                break;
            case 'r':
                std::cout << "enter name, color, height, width" << std::endl;
                std::cin >> nam >> col >> height >> width;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw InputException();
                }
                rec.setName(nam);
                rec.setColor(col);
                rec.setHeight(height);
                rec.setWidth(width);
                ptrrec->draw();
                break;
            case 'p':
                std::cout << "enter name, color, height, width, 2 angles" << std::endl;
                std::cin >> nam >> col >> height >> width >> ang >> ang2;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw InputException();
                }
                para.setName(nam);
                para.setColor(col);
                para.setHeight(height);
                para.setWidth(width);
                para.setAngle(ang, ang2);
                ptrpara->draw();
                break;
            case 'n': {
                std::cout << "enter color, name, side for pentagon" << std::endl;
                double side;
                std::cin >> col >> nam >> side;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw InputException();
                }
                Pentagon pent(col, nam, side);
                pent.draw();
                break;
            }
            case 'h': {
                std::cout << "enter color, name, side for hexagon" << std::endl;
                double side;
                std::cin >> col >> nam >> side;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw InputException();
                }
                Hexagon hex(col, nam, side);
                hex.draw();
                break;
            }
            default:
                std::cout << "you have entered an invalid letter, please re-enter" << std::endl;
                break;
            }

            std::cout << "would you like to add more object press any key if not press x" << std::endl;
            std::cin.get() >> x;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw InputException();
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "caught a bad exception. continuing as usual" << std::endl;
        }
    }

    system("pause");
    return 0;
}

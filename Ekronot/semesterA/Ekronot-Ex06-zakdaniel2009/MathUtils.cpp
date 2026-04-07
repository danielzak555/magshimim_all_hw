#include "MathUtils.h"
#include <cmath>
#include "ShapeException.h"

static double PI = 3.14159265358979323846;

double MathUtils::CalPentagonArea(double side) {
    if (side <= 0)
        throw ShapeException();
	return (5.0 / 4.0) * side * side / std::tan(PI / 5.0);
}

double MathUtils::CalHexagonArea(double side) {
    if (side <= 0)
		throw ShapeException();
    return (3.0 * std::sqrt(3.0) / 2.0) * side * side;
}

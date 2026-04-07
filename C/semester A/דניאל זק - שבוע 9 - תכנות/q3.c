#include <stdio.h>
#include <math.h>

#define PI 3.14159265

enum calcOption{distance = 1, hypotenuse, circle, rectangle, square, end};

float circlePeriCalc(int radius);
float areaCalc(int num, int radius);
double hypotenuseCalc(void);
double distanceCalc(void);

int main()
{
	enum calcOption num = end;
	int radius = 0;
	float fOutput = 0;
	double dOutput = 0;
	do
	{
		printf("Welcome to my calculator!\nChoose option:\n%d - Calc distance between 2 points\n%d - Calc hypotenuse of triangle\n%d - Calc area and perimeter of circle\n%d - Calc area of rectangle\n%d - Calc area of square\n%d - Exit\n", distance, hypotenuse, circle, rectangle, square, end);
		scanf("%d", &num);
		if (num == distance)
		{
			dOutput = distanceCalc();
			printf("Distance is %.2f\n", dOutput);
		}
		else if (num == hypotenuse)
		{	
			dOutput = hypotenuseCalc();
			printf("Hypotenuse is %.2f\n", dOutput);
		}
		else if(num == circle)
		{
			printf("Enter circle radius: ");
			scanf("%d", &radius);
			fOutput = circlePeriCalc(radius);
			printf("Perimeter: %.2f\n", fOutput);
			fOutput = areaCalc(num, radius);
			printf("Area: %.2f\n", fOutput);
		}
		else if(num == rectangle || num == square)
		{	
			fOutput = areaCalc(num, radius);
			if(num == rectangle)
				printf("The area of the rectangle is %.0f\n", fOutput);
			else
				printf("The area of the square is %.0f\n", fOutput);
		}
	}
	while(num != end);
	printf("Goodbye\n");
	
	return 0;		
}
/*
the function will calculate the distance between to points
input: none.
output: the distance between two points.
*/
double distanceCalc(void) 
{
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	double distance = 0, sumPowXAndPowY = 0;
	printf("Enter point1 coordinates: ");
	scanf("%lf %lf", &x1, &y1);
	printf("Enter point2 coordinates: ");
	scanf("%lf %lf", &x2, &y2);
// calculating the distance	by the formula: sqrt((x2-x1)^2+(y2-y1)^2)
	sumPowXAndPowY = pow((x2 - x1), 2) + pow((y2 - y1), 2);
	distance = sqrt(sumPowXAndPowY);
	return distance;
}
/*
the function will calculate the hypotenuse of 90 degree triangle
input: none.
output: the hypotenuse ot the triangle.
*/
double hypotenuseCalc(void) 
{
    double a = 0, b = 0;
	double hypotenuse = 0, sumPowAAndPowB = 0;
	printf("Enter 2 sides of the triangle: ");
	scanf("%lf %lf", &a, &b);
	sumPowAAndPowB = pow(a, 2) + pow(b, 2);
	hypotenuse = sqrt(sumPowAAndPowB);
	return hypotenuse;
}
/*
the function will calculate the area of rectangle or square or circle
input: num - the action that the client asked for (3 || 4 || 5).
       radius - the radius of the circle.
output: the area of the circle or the rectangle or square.
*/
float areaCalc(int num, int radius) 
{
    int side1 = 0, side2 = 0;
	float area = 0;
	if(num == circle)
	{
		area = PI * (radius * radius);
	}
	else if(num == rectangle)
	{
		printf("Enter rectangle length: ");
		scanf("%d", &side1);
		printf("Enter rectangle width: ");
		scanf("%d", &side2);
		area = side1 * side2;
	}
	else
	{
		printf("Enter length of square: ");
		scanf("%d", &side1);
		area = side1 * side1;
	}
	return area;
}
/*
the function will calculate the perimeter of cyrcle
input: the radius of the circle.
output: the perimeter of the circle.
*/
float circlePeriCalc(int radius) 
{
	float perimeter = 0;
	perimeter = PI * (radius * 2);
	return perimeter;
}

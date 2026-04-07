#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void circlePeriCalc(int radius);
void areaCalc(int num, int radius);
void hypotenuseCalc(void);
void distanceCalc(void);

int main()
{
	int num = 0;
	int radius = 0;
	do
	{
		printf("Welcome to my calculator!\nChoose option:\n1 - Calc distance between 2 points\n2 - Calc hypotenuse of triangle\n3 - Calc area and perimeter of circle\n4 - Calc area of rectangle\n5 - Calc area of square\n6 - Exit\n");
		scanf("%d", &num);
		if (num == 1)
			distanceCalc();
		else if (num == 2)
			hypotenuseCalc();
		else if(num == 3)
		{
			printf("Enter circle radius: ");
			scanf("%d", &radius);
			circlePeriCalc(radius);
			areaCalc(num, radius);
		}
		else if(num == 4 || num == 5)
			areaCalc(num, radius);
	}
	while(num != 6);
	printf("Goodbye\n");
	
	return 0;		
}
/*
the function will calculate the distance between to points
input: none.
output: none.
*/
void distanceCalc(void) 
{
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	float distance = 0, sumPowXAndPowY = 0;
	printf("Enter point1 coordinates: ");
	scanf("%f %f", &x1, &y1);
	printf("Enter point2 coordinates: ");
	scanf("%f %f", &x2, &y2);
// calculating the distance	by the formula: sqrt((x2-x1)^2+(y2-y1)^2)
	sumPowXAndPowY = pow((x2 - x1), 2) + pow((y2 - y1), 2);
	distance = sqrt(sumPowXAndPowY);
	printf("Distance is %.2f\n", distance);
}
/*
the function will calculate the hypotenuse of 90 degree triangle
input: none.
output: none.
*/
void hypotenuseCalc(void) 
{
    float a = 0, b = 0;
	float hypotenuse = 0, sumPowAAndPowB = 0;
	printf("Enter 2 sides of the triangle: ");
	scanf("%f %f", &a, &b);
	sumPowAAndPowB = pow(a, 2) + pow(b, 2);
	hypotenuse = sqrt(sumPowAAndPowB);
	printf("Hypotenuse is %.2f\n", hypotenuse);
}
/*
the function will calculate the area of rectangle or square or circle
input: num - the action that the client asked for (3 || 4 || 5).
       radius - the radius of the circle.
output: none.
*/
void areaCalc(int num, int radius) 
{
    int side1 = 0, side2 = 0;
	float area = 0;
	if(num == 3)
	{
		area = PI * (radius * radius);
		printf("Area: %.2f\n", area);
	}
	else if(num == 4)
	{
		printf("Enter rectangle length: ");
		scanf("%d", &side1);
		printf("Enter rectangle width: ");
		scanf("%d", &side2);
		area = side1 * side2;
		printf("The area of the rectangle is %.0f\n", area);
	}
	else
	{
		printf("Enter length of square: ");
		scanf("%d", &side1);
		area = side1 * side1;
		printf("The area of the square is %.0f\n", area);
	}
}
/*
the function will calculate the perimeter of cyrcle
input: none.
output: none.
*/
void circlePeriCalc(int radius) 
{
	float perimeter = 0;
	perimeter = PI * (radius * 2);
	printf("Perimeter: %.2f\n", perimeter);
}

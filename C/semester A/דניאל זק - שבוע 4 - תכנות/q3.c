#include <stdio.h>

#define PI 3.14

int main()
{
	const float X = 4.0/3;
	float radius = 0;
	float volume = 0;
	//קולט משתנים מהמשתמש
	printf("Enter the radius:\n");
	scanf("%f", &radius);

	volume = X*PI*radius*radius*radius;
	
	//printing
	printf("the volume of the ball is:%f\n", volume);

	return 0;
}

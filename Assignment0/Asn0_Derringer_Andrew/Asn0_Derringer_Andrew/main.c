/********************************************************************
* Program: Heron's Formula in C
* Author: Andrew Derringer
* Last Modified: 4/3/2019
* Description: The program takes 3 side lengths of a triangle labeled
* a, b, and c. The semi-perimeter is calculated, labeled s, and used
* along with all 3 side lengths to calculate the area of the triangle,
* labeled area, using Heron's Formula.
********************************************************************/

#include <stdio.h>     // for printf()
#include <math.h>      // for sqrt()



int main(void)
{
	double area;
	double a = 4;
	double b = 6;
	double c = 5;

	double s = (a + b + c) / 2;     // semi-perimeter formula

	area = sqrt(s * (s - a) * (s - b) * (s - c));     // heron's formula

	printf("The trangle side lengths are:\na = %f\nb = %f\nc = %f\n\n", a, b, c);
	printf("The area of the triangle is %f\n", area);

	return 0;
}
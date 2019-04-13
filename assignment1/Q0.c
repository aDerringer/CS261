/* CS261- Assignment 1 - Q. 0*/
/* Name: Andrew Derringer
 * Date: 4/8/2019
 * Solution description:
 *
 *		Summary:	A randomized integer within main is passed by pointer to
 *					2 functions to experiment with operations. The first manipulates
 *					the value pointed to by the local pointer variable, and the second
 *					manipulates the address pointed to. Outputs are printed, before
 *					calling, inside, and after the functions are called.
 *
 *		Inputs:		An integer x is pseudo-randomly generated within main.
 *
 *		Outputs:	Within the function fooA the value for x is incrmented by 5. The
 *					Address and value pointed to by the local pointer and the address
 *					of the local pointer are printed. In main the incremented variable
 *					x is printed again. Within the function fooB the value and address
 *					pointed to by the local pointer are again printed, and the address
 *					pointed to is then decremented by 1. In main the final value and
 *					address of x is then printed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr) {

	printf("We are now inside fooA:\n\n");

	/*Print the value and address of the integer pointed to by iptr*/
	printf("The value of the integer pointed to by iptr is %d\n", *iptr);
	printf("The address of the integer pointed to by iptr is %p\n\n", iptr);

	/*Increment the value of the integer pointed to by iptr by 5*/
	*iptr += 5;

	/*Print the address of iptr itself*/
	printf("The address of iptr is %p\n\n", &iptr);

	/*Dummy variable, ignore the warning*/
	int c = 5;
}

void fooB(int* jptr) {

	printf("We are now inside fooB:\n\n");

	/*Print the value and address of the integer pointed to by jptr*/
	printf("The value of the integer pointed to by jptr is %d\n", *jptr);
	printf("The address of the integer pointed to by jptr is %p\n\n", jptr);

	/*Decrement the address by 1 pointed to by jptr using jptr */
	jptr -= 1;

	/*Observing change in value after address change for additional testing*/
	//printf("After changing the address the integer pointed to by jptr is %d\n\n", *jptr);

	/*Print the address of jptr itself*/
	printf("The address of jptr is %p\n\n", &jptr);
}

int main() {

	/*Declare an integer x and initialize it randomly to a value in [0,10]
	Citation: rand() and srand() information from geeksforgeeks.org*/
	srand(time(0));
	int x = rand() % 10;

	/*Print the value and address of x*/
	printf("The random value of x is %d\n", x);
	printf("The address of x is %p\n\n", &x);

	/*Call fooA() with the address of x*/
	fooA(&x);

	/*Print the value of x*/
	printf("After calling fooA the value of x is %d\n\n", x);

	/*Call fooB() with the address of x*/
	fooB(&x);

	/*Print the value and address of x*/
	printf("After calling FooB the value of x is %d\n", x);
	printf("Now the address of x is %p\n\n", &x);

	/* Question:
     *		#1:	No the value and address did not change in main. Why the
	 *			value pointed at can be changed by a called function, the
	 *			address that is the pointer is passed by value. Because fooB
	 *			Only manipulates the pointer value, it reads differently in
	 *			fooB but cannot be changed through fooB in main.
	*/
	return 0;
}



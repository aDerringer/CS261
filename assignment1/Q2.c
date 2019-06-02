/* CS261- Assignment 1 - Q.2*/
/* Name: Andrew Derringer
 * Date: 4/10/2019
 * Solution description:
 *
 *		Summary:	This program experiments with passing both pointers and values to
 *					a function and observing how those arguements can be manipulated.
 *					We see that while values that a pointer points to can be changed as
 *					though by referece, the address of a pointer cannot. This can only
 *					occur if a pointer to a pointer is passed.
 *
 *		Inputs:		3 integers are randomly generated between 0 and 10. 2 of them are
 *					passed by pointer and one by value to the only additonal function.
 *
 *		Outputs:	After swapping the values of the pointer arguments in foo, we see
 *					that these changes are only local because the addresses themselves
 *					are passed by value and only what is pointed at can by changed as
 *					though by reference.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){

	int* temp;
    /*Swap the addresses stored in the pointer variables a and b*/
	temp = a;
	a = b;
	b = temp;

    /*Decrement the value of integer variable c*/
	c -= 1;
    
    /*Return c*/
	return c;
}

int main(void){

	int returnVal;

	srand(time(0));

    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	int x = rand() % 10;
	int y = rand() % 10;
	int z = rand() % 10;

    /*Print the values of x, y and z*/
	printf("The value of x is %d\nThe value of y is %d\nThe value of z is %d\n\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
	returnVal = foo(&x, &y, z);
    
    /*Print the values of x, y and z*/
	printf("After calling foo:\nThe value of x is %d\nThe value of y is %d\nThe value of z is %d\n\n", x, y, z);

    /*Print the value returned by foo*/
	printf("The value returned by foo is %d", returnVal);

	/* Question:
	 *		#1:	Yes the return value is different than the final value of z in main. Z is passed to
	 *			foo by value and cannot change it's value in main no matter what it does within foo,
	 *			however foo can return an int value that is initialy assigned to the value of z and
	 *			then manipulated before being returned to main. Z could be changed by reassigning it
	 *			to a call to foo, or a new int value could be initialized to foo and then hold the
	 *			value that foo returns.
	 *		#2:	No the values of x and y are not different. The addresses of x and y are passed by value.
	 *			Whle the values they point to in main can be changed, the address cannot be swapped unless
	 *			a pointer to a pointer was passed to foo for the swap. While the addresses are swapped here
	 *			within foo, those changes are lost when the function terminates.
	*/
    
    return 0;
}
    
    



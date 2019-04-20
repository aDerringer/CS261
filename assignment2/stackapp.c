/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	s is not null
	post:	returns 1 if balanced and 0 if not
*/
int isBalanced(char* s) {
	assert(s != 0);

	/* Initiate dynArr stack to hold brackets and set idx to first char in input string. */
	struct DynArr* bracketHolder = newDynArr(10);
	char idx = nextChar(s);
	int balanced = 1;

	/* Continue until the end of the string or inbalance in brackets found. */
	while (idx != '\0' && balanced == 1) {

		/* Pop any openning brackets onto the bracketHolder stack. */
		if (idx == '(' || idx == '{' || idx == '[') {
			pushDynArr(bracketHolder, idx);
		}

		/* If closing bracket matches openning bracket on top of stack then they are
		balanced. Pop the stack and continue. If closing bracket does not match last
		opening bracket then NOT balanced. balanced set to false to end loop. */
		if (idx == ')') {
			if (sizeDynArr(bracketHolder) > 0 && topDynArr(bracketHolder) == '(') {
				popDynArr(bracketHolder);
			}
			else {
				balanced = 0;
			}
		}
		else if (idx == '}') {
			if (sizeDynArr(bracketHolder) > 0 && topDynArr(bracketHolder) == '{') {
				popDynArr(bracketHolder);
			}
			else {
				balanced = 0;
			}
		}
		else if (idx == ']') {
			if (sizeDynArr(bracketHolder) > 0 && topDynArr(bracketHolder) == '[') {
				popDynArr(bracketHolder);
			}
			else {
				balanced = 0;
			}
		}

		idx = nextChar(s);
	}

	/* The while loop catches instances of non-matching brackets or a string that contains
	more closing brackets than openning, but it does not catch a string that contains only
	or too many openning brackets. If openning brackets remain then the struct is not empty
	and the subsequent function call will return false, in which case we set balanced to false. */
	if (isEmptyDynArr(bracketHolder) == 0) {
		balanced = 0;
	}

	free(bracketHolder);
	bracketHolder = 0;

	return balanced;
}

int main(int argc, char* argv[]) {
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}


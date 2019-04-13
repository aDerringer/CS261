/* CS261- Assignment 1 - Q.3*/
/* Name: Andrew Derringer
 * Date: 4/13/2019
 * Solution description:
 *
 *		Summary:	This program reads user input into a string, validating that
 *					it countains at least one letter. The string is then formatted
 *					into all lower case with words seperated by underscores. Finally
 *					the string is converted into camel case with no spaces and any
 *					words after the first beginning with a capital letter.
 *
 *		Input:		String of any length that can fit on the heap.
 *
 *		Outputs:	As designated by the assignment, the program first prints the
 *					string once it has been converted to lower case and it's only
 *					non-alphabetic characters are underscores between words. After
 *					calling camelCase the string is printed again in the desired
 *					final camel case format.
 */

#include <stdio.h>
#include <stdlib.h>

/*Function:	isLetter
* Summary:	Bool statement to determine if a particular array index contains a letter.
* Inputs:	Single character from a string array.
* Outputs:	Bool statement. 1 if letter and 0 if not. */
int isLetter(char ch) {

	int letter = 1;		//default to true

	//If not in the range of upper or lower case letters
	if (ch < 65 || (ch > 90 && ch < 97) || ch > 122) {
		letter = 0;		// false
	}

	return letter;
}

/*Function:	toUpperCase
* Summary:	Algebraically convert only lower case letters to upper case
* Inputs:	Single character from a string array.
* Outputs:	If lower case letter then = lower case - 32 */
char toUpperCase(char ch){

	/*Convert ch to upper case, assuming it is in lower case currently*/
	char upper = ch;

	//Only convert if char is currently lower case
	if (ch > 96 && ch < 123) {
		upper -= 32;
	}

	return upper;

}

/*Function: toLowerCase
* Summary:	Algebraically convert only upper case letters to lower case
* Inputs:	Single character from a string array.
* Outputs:	If upper case letter then = upper case + 32 */
char toLowerCase(char ch){

	/*Convert ch to lower case, assuming it is in upper case currently*/                          
	char lower = ch;

	//Only convert if char is currently upper case
	if (ch > 64 && ch < 91) {
		lower += 32;
	}

	return lower;
}

/*Function: stringLength
* Summary:	Determines the length of a string by counting until reaching NUL
*			This function does not count the NUL character
*			that ends the string into the length so that the typical loop going
*			through the string won't evaluate or alter it because it's not alpha.
* Inputs:	String array
* Outputs:	int length of array passed*/
int stringLength(char s[]) {

	/*Return the length of the string*/
	int index = 0;
	int length = 0;

	//Accepts anything until the NUL character
	while (s[index] != '\0') {
		index++;
		length++;
	}

	return length;
}

/*Function: camelCase
* Summary:	Receives strings of words in a specific format, removes underscores that
*			seperate words, and converts the first letter of words excluding the first
*			word to upper case letters.
* Inputs:	String array
* Outputs:	Changes the string pointer passed to it as specified in summary*/
void camelCase(char* word){

	/*Convert to camelCase*/
	int length = stringLength(word);

	//Loop through the string by character excluding the terminating NUL
	for (int index = 0; index < length; index++) {

		//Ignores the first letter and converts any following letters preceeded by an
		//underscore to upper case
		if (index > 0) {
			if (word[index - 1] == '_') {
				word[index] = toUpperCase(word[index]);
			}
		}
	}

	//Loop through the string by character excluding the terminating NUL
	for (int index = 0; index < length; index++) {

		//If the char is an underscore then delete it by shifting the rest left by one.
		if (word[index] == '_') {
			for (int i = index; i < length + 1; i++) {
				word[i] = word[i + 1];
			}

			length -= 1;
		}
	}
}

/*Function: clearFrontBack
* Summary:	Removes any characters that are not alphabetic from the beginning 
*			and end of a string
* Inputs:	String array
* Outputs:	Changes the string pointer passed to it as specified in summary*/
void clearFrontBack(char* word) {

	int length = stringLength(word);	//does not include terminating \0

	//While first char != alpha, remove it, adjust length, and check again.
	while (isLetter(word[0]) == 0) {

		//Intentionally uses length + 1 to move terminating NUL over one.
		for (int index = 0; index < length + 1; index++) {
			word[index] = word[index + 1];
		}

		length -= 1;
	}

	//If the final character not including the terminating NUL isn't alpha
	//then remove it by shifting NUL left one over it. Check again.
	while (isLetter(word[length - 1]) == 0) {
		word[length - 1] = word[length];
		length -= 1;
	}

}

/*Function: underscores
* Summary:	Convert the first non-alpha character between words in a string array
*			to an underscore and delete any additional non-alpha characters between
*			words/letters
* Inputs:	String array
* Outputs:	Changes the string pointer passed to it as specified in summary*/
void underscores(char* word) {

	int flag = 0;		//Bool becomes true at beginning of any string of non-alpha char
	int length = stringLength(word);


	for (int index = 0; index < length; index++) {

		//If the char is not a letter and flag = 0 then it's the first non-alpha between words.
		//Converts it to underscore and sets flag to true.
		if (isLetter(word[index]) == 0 && flag == 0) {
			word[index] = '_';
			flag = 1;
		}

		//If the char is not a letter and flag = 1 then underscore between words already placed.
		//Deletes the character by shifting the rest of the string left one.
		else if (isLetter(word[index]) == 0 && flag == 1) {
			for (int i = index; i < length; i++) {
				word[i] = word[i + 1];
			}

			word[length - 1] = '\0';
			length -= 1;
		}

		//If the char is a letter reset the flag to 0 in preperation for any additional spaces between words.
		else {
			flag = 0;
		}
	}
}

/*Function: allLower
* Summary:	Convert all alpha characters in a string to lower case using a loop and
*			call to the toLowerCase function.
* Inputs:	String array
* Outputs:	Changes the string pointer passed to it as specified in summary*/
void allLower(char* word) {

	int length = stringLength(word);

	//Called function checks if the character is an upper case letter and converts to lower
	for (int index = 0; index < length; index++) {
		word[index] = toLowerCase(word[index]);
	}
}

int main(){

	int length = 0;
	int containsAlpha = 0;
	char c;
	char* word;
	char* temp;

	printf("Please enter a string:\n");

	//Throws error if no letters were in string and loops for new input
	do {
		length = 0;		//Incremented for realloc call each getchar()
		containsAlpha = 0;		//Bool flag stays false if no letters in string
		word = (char*)malloc(sizeof(char));		//Reallocate each loop

		//Loops continues to read and insert input characters until newline.
		//Citation: Inspired by cnicutar at https://stackoverflow.com/questions/8164000/
		while ((c = getchar()) != '\n') {

			//Size of dynamic string reallocated with each new char
			temp = realloc(word, (sizeof(char) * (length + 1)));
			word = temp;
			word[length] = c;
			length++;

			//If just one char is letter chance bool flag to true. Don't touch again.
			if (isLetter(c) == 1 && containsAlpha == 0) {
				containsAlpha = 1;
			}
		}

		//Append NUL to end of string
		temp = realloc(word, (sizeof(char) * (length + 1)));
		word = temp;
		word[length] = '\0';

		//If no letters were present throw error message. Input process will loop again.
		if (containsAlpha == 0) {
			printf("\nError: You must enter a string that contains at least one letter.\n");
			printf("Please try again:\n");

			//Old input is freed and pointer set to NULL for safety
			free(word);
			word = NULL;
		}

	} while (containsAlpha == 0);


	printf("\nYou entered: %s\n\n", word);

	//Remove any non-alpha characters from front and back of string
	clearFrontBack(word);

	printf("After editing the front and back: %s\n\n", word);

	//Reduce any non-alpha characters between words to single underscore
	underscores(word);

	//Convert all letters in string to lowercase
	allLower(word);

	printf("After reformatting: %s\n\n", word);

	/*Call camelCase*/
	camelCase(word);

	/*Print the new string*/
	printf("After calling camelCase: %s\n\n", word);

	free(word);
	word = NULL;

	return 0;
}


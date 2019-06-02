/* CS261- Assignment 1 - Q.1*/
/* Name: Andrew Derringer
 * Date: 4/10/2019
 * Solution description:
 *
 *		Summary:	This program allocated an array of 10 student structures and then
 *					randomly generates a unique student id and non-unique score for
 *					each of them. They are then printed and analyzed.
 *
 *		Inputs:		10 student structs in a dynamic array with randomly generated IDs
 *					and scores.
 *
 *		Outputs:	Printed table of students by ID and score as well as logic that
 *					determines the min and max scores and average.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

struct student{
	int id;
	int score;
};

/*Function:	allocate
* Summary:	A declared array of struct student type is initialized with call to allocate()
* Inputs:	None
* Outputs:	dynamic array with enough space for 10 student structs */
struct student* allocate(){

    /*Allocate memory for ten students*/
	struct student* roster;
	roster = (struct student*) malloc(10 * sizeof(struct student));
	assert(roster != 0);

    /*Return the pointer*/
	return roster;
}

/*Function:	generate
* Summary:	Generates unique IDs 1-10 using Fisher-Yates method and non-unique scores for each student
* Inputs:	Dynamic array of struct students
* Outputs:	Array populated with students including assigned IDs and scores */
void generate(struct student* students){
    /*Generate random and unique IDs and random scores for ten students, 
	IDs being between 1 and 10, scores between 0 and 100*/

	//Random ID generation using Fisher-Yates Shuffle
	int indexHolder;
	int exchangeIndex;
	int idNumbers[10] = { 1,2,3,4,5,6,7,8,9,10 };

	for (int id = 0; id < 10; id++) {
		exchangeIndex = rand() % 10;
		indexHolder = idNumbers[id];
		idNumbers[id] = idNumbers[exchangeIndex];
		idNumbers[exchangeIndex] = indexHolder;
	}

	//Generate student variables
	for (int stud = 0; stud < 10; stud++) {
		students[stud].id = idNumbers[stud];
		students[stud].score = rand() % 100;
	}  
}

/*Function:	output
* Summary:	Prints a table of each student ID and score per line
* Inputs:	Dynamic array of struct students
* Outputs:	Table of each student ID and score per line */
void output(struct student* students){
    /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	for (int stud = 0; stud < 10; stud++) {
		if (students[stud].id == 10) {
			printf("ID%d score%d\n", students[stud].id, students[stud].score);
		}
		else {
			printf("ID%d  score%d\n", students[stud].id, students[stud].score);
		}

	}

	printf("\n");
}

/*Function:	summary
* Summary:	Determines and prints min and max score and average score
* Inputs:	Dynamic array of struct students
* Outputs:	Prints min and max score and average score */
void summary(struct student* students){

    /*Compute and print the minimum, maximum and average scores of the 
	ten students*/
	int min = students[0].score;
	int max = min;
	int sum = 0;
	double average;

	for (int stud = 0; stud < 10; stud++) {

		if (students[stud].score > max) {
			max = students[stud].score;
		}
		else if(students[stud].score < min){
			min = students[stud].score;
		}

		//Add score to sum of scores each loop
		sum += students[stud].score;
	}

	//Compute the average
	average = sum / 10;

	//Print statements
	printf("The minimum score is %d\n", min);
	printf("The maximum score is %d\n", max);
	printf("The average score is %f\n\n", average);
}

/*Function:	deallocate
* Summary:	deallocates any dynamic array of struct students passed to it
* Inputs:	Dynamic array of struct students
* Outputs:	None */
void deallocate(struct student* stud){


    /*Deallocate memory from stud*/
	free(stud);
	stud = NULL;
}

int main(){
    struct student* stud = NULL;
    
	srand(time(0));

    /*Call allocate*/
	stud = allocate();

    /*Call generate*/
	generate(stud);
    
    /*Call output*/
	output(stud);

    /*Call summary*/
	summary(stud);
    
    /*Call deallocate*/
	deallocate(stud);

    return 0;
}


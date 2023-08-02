#include<stdio.h>
#include"calculate.h"  /*Double Quotes used for local files*/

/* #define DEBUG 1 /1* debugging mode ON/OFF (comment out) *1/ */

int main()
{
	int number = 5;

	#ifdef DEBUG
		printf("Reached line 11 OK\n"); /* debugging check */
	#endif

	printf("square of %d is %d\n", number, square(number));
	printf("cube of %d is %d\n", number, cube(number));

	#ifdef DEBUG
		printf("Reached line 18 OK\n"); /* debugging check */
	#endif

	return 0;
}

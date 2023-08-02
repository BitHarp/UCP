#include <stdio.h>
#include <stdlib.h>

int main()
{
	int intOne, intTwo;

	printf("\t### INTEGER DIVISIBILITY CHECKER ###\nEnter two integers, separated by a space, then press enter: ");
	scanf("%d %d",&intOne,&intTwo);
	/*printf("Enter another integer, then press enter: ");
	scanf("%d",&intTwo);*/

	if(intOne % intTwo == 0)
	{
		printf("divisible\n");
	}
	else
	{
		printf("not divisible\n");
	}
	return 0;
}


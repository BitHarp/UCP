#include <stdio.h>
#include <stdlib.h>

/*forward declarations*/
int factorial(int n);

int main(void)
{
	int number = 0;

	while(number >= 0)
	{
		printf("Enter a number to calculate the factorial: ");
		scanf("%d",&number);
		printf("The factorial of %d is %d\n",number,factorial(number));
	}
	printf("Enter a positive or zero integer. Ending.\n");
	
	return 0;
}

int factorial(int n)
{
	int i;
	int fact = 1;
	for(i = 2; i < n+1; i++)
	{
		fact = fact * i;
	}
	return fact;

}

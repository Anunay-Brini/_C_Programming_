#include <stdio.h>

int main()
{
	int secret = 26;
	int guess;
	int count = 0;
	
	do
	{
		printf("\nGuess the secret number between 20 and 30 : ");
		scanf("%d",&guess);
		if (guess != secret)
		{
			printf("Wrong! Try again...\n");
		}
		count++;
		
	}
    while(guess != secret);
    {
	    printf("\nCongratulations! You got it right");
	    printf("\nNumber of attempts : %d",count); 
    }
	return 0;

}


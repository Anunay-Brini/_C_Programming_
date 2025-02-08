#include <stdio.h>
int main()
{
	int a,b,sum,sub,mul,div,ch;
	printf("Enter the value of a : ");
	scanf("%d",&a);
	printf("Enter the value of b : ");
	scanf("%d",&b);
	do 
	{
        printf("\nMenu:\n");
        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Divide\n");
        printf("5. Exit\n");
		printf("Enter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				sum=a+b;
				printf("\n");
				printf("%d+%d=%d",a,b,sum);
				printf("\n");
				break;
			case 2:
				sub=a-b;
				printf("\n");
				printf("%d-%d=%d",a,b,sub);
				printf("\n");
				break;
			case 3:
				mul=a*b;
				printf("\n");
				printf("%d*%d=%d",a,b,mul);
				printf("\n");
				break;
			case 4:
				div=a/b;
				printf("\n");
				printf("%d/%d=%d",a,b,div);
				printf("\n");
				break;
			case 5:
				break;
			default:
				printf("\n");
				printf("Invalid Choice!!!!");
				printf("\n");
		}
 	}
 	while (ch != 5);
 	printf("\n");
 	return 0;
}

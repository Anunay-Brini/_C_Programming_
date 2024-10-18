#include<stdio.h>
int main()
{
    float radius, perimeter, area, pi=3.14;
    printf("enter the radius\n");
    scanf("%f",&radius);
    perimeter=2*pi*radius;
    area=pi*radius*radius;
    printf("perimeter=%f",perimeter);
    printf("area=%f", area);
    return 0;
}

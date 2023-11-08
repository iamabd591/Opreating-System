#include<stdio.h>
int main()
{
int lenght;
int width;
int Area;

printf(" Enter the lenght of Triangle:");
scanf("%d", &lenght);

printf(" Enter the width of Triangle:");
scanf("%d", &width);

Area =lenght*width;

printf("Lenght is : %d\n",lenght);
printf("Width is : %d\n",width);
printf("Area  is : %d\n",Area);

return 0;
}

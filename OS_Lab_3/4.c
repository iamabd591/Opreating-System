#include <stdio.h>
int main()
{
    int num1;
    int  num2;
    int total ;

    printf("Enter a number: ");
    scanf("%d", &num1);
    printf("Enter another number: ");
    scanf("%d", &num2);
if(num1<0 || num2<0)
{
printf("Numbers shoud be positive ");
}
else{
    total =num1+num2;
printf("total = %d", total);

}
    return 0;
}

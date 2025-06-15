#include <stdio.h>

int main(void)
{
    char name[100];

    //takes user input and says hello to them.
    printf("What's your name? ");
    scanf("%99s", name); //avoids buffer overflow
    printf("hello, %s\n", name);


}
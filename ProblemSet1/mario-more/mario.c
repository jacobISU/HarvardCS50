#include <stdio.h>

int main(void)
{

    int height;
    int increment = 1;
    const int gap = 2;

    // take user input
    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height < 1 || height > 8);

    for (int i = 1; i < height + 1; i++)
    {

        int spaceCounter = height - i;

        // number of spaces before gap
        for (int j = 0; j < spaceCounter; j++)
        {
            printf(" ");
        }

        // blocks before gap
        for (int k = 0; k < increment; k++)
        {
            printf("#");
        }

        // gap
        for (int l = 0; l < gap; l++)
        {
            printf(" ");
        }

        // blocks after gap
        for (int m = 0; m < increment; m++)
        {
            printf("#");
        }

        printf("\n");
        increment++;
    }
}

#include <stdio.h>
#include "mymath.h"

int main()
{
    int run = 1;
    int a;
    int b;
    int choice;
    while (run)
    {
        printf(" 1) Add\n 2) Sub\n 3) Mul\n 4) Div\n 5) Quit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case (5):
            run = 0;
            break;

        case (1):
            printf("Enter A: ");
            scanf("%d", &a);
            printf("Enter B: ");
            scanf("%d", &b);
            printf("Result: %d\n", add(a, b));
            break;

        case (2):
            printf("Enter A: ");
            scanf("%d", &a);
            printf("Enter B: ");
            scanf("%d", &b);
            printf("Result: %d\n", sub(a, b));
            break;

        case (3):
            printf("Enter A: ");
            scanf("%d", &a);
            printf("Enter B: ");
            scanf("%d", &b);
            printf("Result: %d\n", mul(a, b));
            break;

        case (4):
            printf("Enter A: ");
            scanf("%d", &a);
            printf("Enter B: ");
            scanf("%d", &b);
            printf("Result: %d\n", div(a, b));
            break;

        default:
            break;
        }
    }
    return 0;
}
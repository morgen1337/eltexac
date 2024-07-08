#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct abonent
{
    char *name;
    char *second_name;
    char *tel;
    struct abonent *next;
};

struct abonent *create_abonent(char *name, char *second_name, char *tel)
{
    struct abonent *newabonent = malloc(sizeof(struct abonent));
    if (!newabonent)
    {
        printf("Not Enough Space\n");
        return NULL;
    }
    newabonent->name = name;
    newabonent->second_name = second_name;
    newabonent->tel = tel;
    newabonent->next = NULL;
    return newabonent;
}

int main()
{

    struct abonent phonebook[100];
    struct abonent *baseabonent = NULL;
    struct abonent *lastabonent = NULL;
    int run = 1;
    int i;
    int choice;
    int maxind = 0;
    char *name;
    char *second_name;
    char *tel;
    struct abonent *printabonent;
    struct abonent *delabonent;
    struct abonent *prevabonent;
    while (run)
    {
        printf(" 1) Add\n 2) Delete\n 3) Name search\n 4) Print all\n 5) Quit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            name = malloc(sizeof(char) * 10);
            second_name = malloc(sizeof(char) * 10);
            tel = malloc(sizeof(char) * 10);
            printf("Enter a name: ");
            scanf("%s", name);
            printf("Enter a second name: ");
            scanf("%s", second_name);
            printf("Enter a telephone number: ");
            scanf("%s", tel);
            if (!baseabonent)
            {
                baseabonent = create_abonent(name, second_name, tel);
                lastabonent = baseabonent;
            }
            else
            {
                lastabonent->next = create_abonent(name, second_name, tel);
                lastabonent = lastabonent->next;
            }
            maxind++;
            break;
        case 2:
            if (!baseabonent)
                break;
            printf("Enter an index of abonent to delete: ");
            scanf("%d", &i);
            if (i < 0 || i > maxind){
                printf("No Such Index!\n");
                break;
            }
            if (i == 0)
            {
                delabonent = baseabonent;
                baseabonent = baseabonent->next;
                free(delabonent);
                break;
            }
            prevabonent = baseabonent;
            for (int j = 0; j < i - 1; j++)
            {
                prevabonent = prevabonent->next;
            }
            delabonent = prevabonent->next;
            prevabonent->next = delabonent->next;
            free(delabonent);
            break;
        case 3:
            if (!baseabonent)
                break;
            char search[10];
            printabonent = baseabonent;
            printf("Enter a name to search: ");
            scanf("%s", search);
            while (printabonent)
            {
                if (!strcmp(search, printabonent->name))
                {
                    printf("FOUND: \nName: %s\nSecond name: %s\nTelephone number: %s\n", printabonent->name, printabonent->second_name, printabonent->tel);
                }
                printabonent = printabonent->next;
            }
            break;
        case 4:
            if (!baseabonent)
                break;
            int index = 0;
            printabonent = baseabonent;
            while (printabonent)
            {
                printf("\nIndex: %d\nName: %s\nSecond name: %s\nTelephone number: %s\n", index, printabonent->name, printabonent->second_name, printabonent->tel);
                printabonent = printabonent->next;
                index++;
            }
            break;
        case 5:
            run = 0;
            break;
        default:
            break;
        }
    }

    struct abonent *next;
    while (baseabonent)
    {
        next = baseabonent->next;
        free(baseabonent);
        baseabonent = next;
    }
    return 0;
}
#include <stdio.h>
#include <string.h>

struct abonent {
char name[10];
char second_name[10];
char tel[10];
};

int main(){
    
    struct abonent phonebook[100];
    int filled = 0;
    int run = 1;
    int choice;
    while (run){
        printf(" 1) Add\n 2) Delete\n 3) Name search\n 4) Print all\n 5) Quit\n");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter a name: ");
                scanf("%s", phonebook[filled].name);
                printf("Enter a second name: ");
                scanf("%s", phonebook[filled].second_name);
                printf("Enter a telephone number: ");
                scanf("%s", phonebook[filled].tel);
                filled++;
                break;
            case 2:
                if (filled == 0)
                    break;
                filled--;
                phonebook[filled].name[0] = '\0';
                phonebook[filled].second_name[0] = '\0';
                phonebook[filled].tel[0] = '\0';
                break;
            case 3:
                char search[10];
                printf("Enter a name to search: ");
                scanf("%s", search);
                for (int i = 0; i < filled; i++){
                    if (!strcmp(search, phonebook[i].name)){
                        printf("Name: %s\nSecond name: %s\nTelephone number: %s\n", phonebook[i].name, phonebook[i].second_name, phonebook[i].tel);
                    }
                }
                break;
            case 4:
                for (int i = 0; i < filled; i++){
                    printf("Name: %s\nSecond name: %s\nTelephone number: %s\n", phonebook[i].name, phonebook[i].second_name, phonebook[i].tel);
                }
                break;
            case 5:
                run = 0;
                break;
            default:
                break;
        }
    }
    return 0;
}
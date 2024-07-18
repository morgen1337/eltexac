#include <ncurses.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define TABNUM 2

int alphasort(const struct dirent **a, const struct dirent **b)
{
    return strcmp((*a)->d_name, (*b)->d_name);
}

int main()
{
    int key;
    int n[TABNUM];
    char dirpath[TABNUM][200];
    struct dirent **namelist[TABNUM];
    int chosendir[TABNUM];
    for (int tabs = 0; tabs < TABNUM; tabs++)
    {
        strcpy(dirpath[tabs], ".");
        n[tabs] = scandir(dirpath[tabs], &namelist[tabs], 0, alphasort);
        chosendir[tabs] = 1;
    }

    int chosentab = 0;

    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    do
    {
        clear();
        for (int tabs = 0; tabs < TABNUM; tabs++)
        {

            for (int i = 1; i < n[tabs]; i++)
            {
                move(i, tabs * 100);
                printw("%s", namelist[tabs][i]->d_name);
                if (i == chosendir[tabs] && chosentab == tabs)
                    printw(" <-");
            }
            refresh();
        }
        key = getch();
        if (key == KEY_DOWN && chosendir[chosentab] < n[chosentab] - 1)
            chosendir[chosentab]++;
        if (key == KEY_UP && chosendir[chosentab] > 1)
            chosendir[chosentab]--;
        if (key == '\t')
        {
            if (chosentab == TABNUM - 1)
                chosentab = 0;
            else
                chosentab++;
        }
        if (key == '\n' && namelist[chosentab][chosendir[chosentab]]->d_type == DT_DIR)
        {
            strcat(dirpath[chosentab], "/");
            strcat(dirpath[chosentab], namelist[chosentab][chosendir[chosentab]]->d_name);
            n[chosentab] = scandir(dirpath[chosentab], &namelist[chosentab], 0, alphasort);
            chosendir[chosentab] = 1;
        }

    } while (key != 'q');
    for (int tabs = 0; tabs < TABNUM; tabs++)
    {
        for (int i = 0; i < n[tabs]; i++)
        {
            free(namelist[tabs][i]);
        }
        free(namelist[tabs]);
    }
    endwin();
    return 0;
}
#include "menu.h"
#include <string.h>

void printoption(WINDOW *win, char* text, int* id, int ymax, int xmax);
WINDOW* initwin(int *xmax, int *ymax);

WINDOW* initandsetcurses(int *xmax, int *ymax)
{
    WINDOW *win;
    initscr();
    noecho();
    curs_set(0);
    win = initwin(xmax, ymax);
    return(win);
}

WINDOW* initwin(int *xmax, int *ymax)
{
    WINDOW *win;
    getmaxyx(stdscr, (*ymax), (*xmax));
    win = newwin((*ymax)/2, (*xmax)/2, (*ymax)/4, (*xmax)/4);
    return(win);
}

void printoption(WINDOW *win, char* text, int* id, int ymax, int xmax)
{
    mvwprintw(win, ((ymax/4) + (*id) - 3), ((xmax/4) - (int)(strlen(text)/2)), "%s", text);
    if(ymax){}
    (*id)++;
}

void printmenu(WINDOW *win, int ymax, int xmax, int pos)
{
    int id = 1;
    box(win, 0, 0);
    switch (pos)
    {
        case(1):
            wattron(win, A_STANDOUT);
            printoption(win, "General Benchmarking", &id, ymax, xmax);
            wattroff(win, A_STANDOUT);
            printoption(win, "Specific Loading in DBMS", &id, ymax, xmax);
            printoption(win, "Viewing DBMS File Structure", &id, ymax, xmax);
            break;

        case(2):
            printoption(win, "General Benchmarking", &id, ymax, xmax);
            wattron(win, A_STANDOUT);
            printoption(win, "Specific Loading in DBMS", &id, ymax, xmax);
            wattroff(win, A_STANDOUT);
            printoption(win, "Viewing DBMS File Structure", &id, ymax, xmax);
            break;

        case(3):
            printoption(win, "General Benchmarking", &id, ymax, xmax);
            printoption(win, "Specific Loading in DBMS", &id, ymax, xmax);
            wattron(win, A_STANDOUT);
            printoption(win, "Viewing DBMS File Structure", &id, ymax, xmax);
            wattroff(win, A_STANDOUT);
            break;

        default:
            break;
    }
}

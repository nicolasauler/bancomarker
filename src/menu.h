#ifndef __MENU_H__
#define __MENU_H__

#include <ncurses.h>
#include <string.h>

WINDOW* initandsetcurses(int *xmax, int *ymax);

void printmenu(WINDOW *win, int xmax, int ymax, int pos);

#endif

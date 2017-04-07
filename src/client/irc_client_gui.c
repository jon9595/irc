#include </usr/include/ncurses.h>
#include <string.h>

#include "irc_client.h"

int main(int argc, char* argv[]) {

    char msg[] = "Enter a string: ";
    char str[80];
    int row, col;

    if(argc != 1 || argv == NULL) {
        return 1;
    }

    /*Initialize Curses Window*/
    initscr();
    getmaxyx(stdscr, row, col);
    mvprintw(row/2,(col-strlen(msg))/2, "%s", msg);

    getstr(str);
    mvprintw(LINES - 2, 0, "You Entered: %s", str);
    getch();
    endwin();

    return 0;
}

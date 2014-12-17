#ifndef HEADER_H
#define HEADER_H

#include <curses.h>

#define HEADER_ROWS 1

// Header window
WINDOW *header_win;

void print_header(WINDOW *);

#endif /* HEADER_H */

#ifndef FOOTER_H
#define FOOTER_H

#include <curses.h>

#define FOOTER_ROWS 1

// Footer window
WINDOW *footer_win;

void print_footer(WINDOW *);

#endif /* FOOTER_H */

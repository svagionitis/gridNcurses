#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>
#include <stdint.h>
#include "utils.h"
#include "window.h"
#include "header.h"
#include "footer.h"
#include "control.h"
#include "grid.h"


int main(int argc, char *argv[])
{
    pthread_t thread_control;

    memset(&g, 0, sizeof g);
    memset(&win_set, 0, sizeof win_set);
    win_set.speed = 1000000;

    if (argc != 2)
    {
        printf("Usage: %s <XxY grid>\n", argv[0]);
        printf("Example: %s 8x8\n", argv[0]);
        return -1;
    }


    sscanf(argv[1],"%ux%u", &g.x_grid, &g.y_grid);

    initscr();

    // Get the maximum size of the screen
    getmaxyx(stdscr, win_set.maxHeight, win_set.maxWidth);

    // Create window for the header rows
    header_win = newwin(HEADER_ROWS, win_set.maxWidth, 0, 0);

    getmaxyx(header_win, win_set.maxHeaderHeight, win_set.maxHeaderWidth);

    // Create window for the footer rows
    footer_win = newwin(FOOTER_ROWS, win_set.maxWidth, win_set.maxHeight - FOOTER_ROWS, 0);

    getmaxyx(footer_win, win_set.maxFooterHeight, win_set.maxFooterWidth);

    // Create main window, it's between the header and the footer
    grid_win = newwin(win_set.maxHeight - HEADER_ROWS - FOOTER_ROWS, win_set.maxWidth, HEADER_ROWS, 0);

    getmaxyx(grid_win, win_set.maxGridHeight, win_set.maxGridWidth);

    // Check if colors are supported
    if (!has_colors())
    {
        delwin(stdscr);
        endwin();
        fprintf(stderr,"Your terminal does not support color\n");
        return -1;
    }
    else
    {
        // Initialize colors
        start_color();

        // Assign terminal default foreground/background colors to color number -1
        use_default_colors();

        // Initialize color pairs.
        uint16_t pair_count = 0;
        for(uint16_t i = 0;i<COLORS;i++)
            for(uint16_t j = 0;j<COLORS;j++)
                init_pair(pair_count++, i, j);
    }


    clear();

    // The timeout and wtimeout routines set blocking or non-blocking 
    // read for a given window. If delay is negative, blocking read is used 
    // (i.e., waits indefinitely for input). If delay is zero, then non-blocking 
    // read is used (i.e., read returns ERR if no input is waiting). If delay is 
    // positive, then read blocks for delay milliseconds, and returns ERR 
    // if there is still no input.
    timeout(0);
    // Turn off key echoing
    noecho();
    // Line buffering disabled
    cbreak();
    // This determines the visibility of the cursor.
    curs_set(FALSE);
    // Tell curses not to do NL->CR/NL on output
    nonl();
    // Enable the keypad for non-char keys
    keypad(stdscr, TRUE);


    // Put control in a separate thread
    pthread_create(&thread_control, NULL, control, NULL);

    while(win_set.c != 'q')
    {
        print_header(header_win);

        print_grid(grid_win);

        print_footer(footer_win);

        doupdate();
        usleep(win_set.speed);
    }

    pthread_join(thread_control, NULL);

    delwin(header_win);
    delwin(footer_win);
    endwin();

    return 0;
}

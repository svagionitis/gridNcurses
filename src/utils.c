#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "utils.h"

/**
 * \brief   Print a string, with selected foreground and background color, 
 *          in (x,y) coordinates on a specific window.
 *
 * \param   win         Window that the string will be printed.
 * \param   y           Y coordinate of string for the window.
 * \param   x           X coordinate of string for the window.
 * \param   fg_color    Foreground color of string for the window.
 * \param   bg_color    Background color of string for the window.
 * \param   str         String to be printed on window.
 */
void color_str(WINDOW *win, uint32_t y, uint32_t x, int16_t fg_color, int16_t bg_color, const char *str)
{
    int16_t i;
    // Search all the pair of colors
    // to match with the given one.
    // Then apply the specific pair.
    // Naive way
    for (i = 0;i < COLOR_PAIRS;i++)
    {
        int16_t f, b;
        pair_content(i, &f, &b);
        if (f == fg_color && b == bg_color)
            break;
    }

    wattron(win, COLOR_PAIR(i));

    mvwaddstr(win, y, x, str);

    wattroff(win, COLOR_PAIR(i));
}

/**
 * \brief   Initialize srand using the time in seconds and useconds.
 *          Sleep for 10usecs in order not to have the same useconds.
 */
void init_seed_srand(void)
{
    struct timeval t;

    // Sleep 10 usec in order 
    // not to have the same seed
    usleep(10);

    gettimeofday(&t, NULL);

    srand(t.tv_usec * t.tv_sec);
}


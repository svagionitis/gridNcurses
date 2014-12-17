#include <string.h>
#include "window.h"
#include "grid.h"
#include "utils.h"

extern window_settings_t win_set;

void print_grid(WINDOW *win)
{
    getmaxyx(win, win_set.maxGridHeight, win_set.maxGridWidth);

    for(int32_t y=0;y<win_set.maxGridHeight;y++)
        for(int32_t x=0;x<win_set.maxGridWidth;x++)
        {
            if (y == x)
                color_str(win, y, x, 0, 0, "O");

        }

    wnoutrefresh(win);
}


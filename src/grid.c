#include <string.h>
#include "window.h"
#include "grid.h"
#include "utils.h"

extern window_settings_t win_set;

void print_grid(WINDOW *win)
{
    getmaxyx(win, win_set.maxGridHeight, win_set.maxGridWidth);

    int32_t y_grid_step = win_set.maxGridHeight / g.y_grid;
    int32_t x_grid_step = win_set.maxGridWidth / g.x_grid;

    for(int32_t y=0;y<win_set.maxGridHeight;y+=y_grid_step)
        for(int32_t x=0;x<win_set.maxGridWidth;x+=x_grid_step)
            color_str(win, y, x, 0, 0, "O");


    wnoutrefresh(win);
}


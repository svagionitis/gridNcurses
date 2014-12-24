#include <string.h>
#include "window.h"
#include "grid.h"
#include "utils.h"

extern window_settings_t win_set;

void print_grid(WINDOW *win)
{
    getmaxyx(win, win_set.maxGridHeight, win_set.maxGridWidth);

    // If the grid is larger than the maximum height
    // or width, then set it to max height or width
    if (g.y_grid > win_set.maxGridHeight)
        g.y_grid = win_set.maxGridHeight;

    if (g.x_grid > win_set.maxGridWidth)
        g.x_grid = win_set.maxGridWidth;

    int32_t y_grid_step = win_set.maxGridHeight / g.y_grid;
    int32_t x_grid_step = win_set.maxGridWidth / g.x_grid;

    int32_t y_remaining = win_set.maxGridHeight % g.y_grid;
    int32_t x_remaining = win_set.maxGridWidth % g.x_grid;

    int32_t y_max_height = win_set.maxGridHeight - y_remaining;
    int32_t x_max_width = win_set.maxGridWidth - x_remaining;

    for(int32_t y=0;y<=y_max_height;y++)
        for(int32_t x=0;x<=x_max_width;x++)
            if (!(y % y_grid_step) && !(x % x_grid_step))
                color_str(win, y+(y_remaining/2), x+(x_remaining/2), 0, 0, "+");
            else if (!(y % y_grid_step))
                color_str(win, y+(y_remaining/2), x+(x_remaining/2), 0, 0, "-");
            else if (!(x % x_grid_step))
                color_str(win, y+(y_remaining/2), x+(x_remaining/2), 0, 0, "|");
            else if ((y % y_grid_step) || (x % x_grid_step))
                color_str(win, y+(y_remaining/2), x+(x_remaining/2), 0, 0, "X");


    wnoutrefresh(win);
}


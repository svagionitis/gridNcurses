#include <string.h>
#include "window.h"
#include "grid.h"
#include "utils.h"

extern window_settings_t win_set;

void print_grid(WINDOW *win)
{
    getmaxyx(win, win_set.maxGridHeight, win_set.maxGridWidth);

    wclear(win);

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

    int32_t new_max_height = win_set.maxGridHeight - y_remaining;
    int32_t new_max_width = win_set.maxGridWidth - x_remaining;

    for(int32_t y = 0;y <= new_max_height;y++)
    {
        // Adding the half of the remaining in order
        // to put the grid more center on screen.
        int32_t new_y = y + (y_remaining / 2);

        for(int32_t x = 0;x <= new_max_width;x++)
        {
            int32_t new_x = x + (x_remaining / 2);

            if (!(y % y_grid_step) && !(x % x_grid_step))
                color_str(win, new_y, new_x, 0, 0, "+");
            else if (!(y % y_grid_step))
                color_str(win, new_y, new_x, 0, 0, "-");
            else if (!(x % x_grid_step))
                color_str(win, new_y, new_x, 0, 0, "|");
            else if ((y % y_grid_step) || (x % x_grid_step))
                color_str(win, new_y, new_x, 0, 0, "X");
        }
    }

    wnoutrefresh(win);
}


#include <string.h>
#include "window.h"
#include "grid.h"
#include "utils.h"

extern window_settings_t win_set;

void print_grid(WINDOW *win)
{
    getmaxyx(win, win_set.maxGridHeight, win_set.maxGridWidth);

    wclear(win);

    generate_grid(win, win_set.maxGridHeight, win_set.maxGridWidth);

    wnoutrefresh(win);
}

void generate_grid(WINDOW *win, int32_t grid_win_height, int32_t grid_win_width)
{
    // If the grid is larger than the maximum height
    // or width, then set it to max height or width
    if (g.y_grid > grid_win_height)
        g.y_grid = grid_win_height;

    if (g.x_grid > grid_win_width)
        g.x_grid = grid_win_width;

    int32_t y_grid_step = grid_win_height / g.y_grid;
    int32_t x_grid_step = grid_win_width / g.x_grid;

    int32_t y_remaining = grid_win_height % g.y_grid;
    int32_t x_remaining = grid_win_width % g.x_grid;

    int32_t new_max_height = grid_win_height - y_remaining;
    int32_t new_max_width = grid_win_width - x_remaining;

    for(int32_t y = 0;y <= new_max_height;y++)
    {
        // Adding the half of the remaining in order
        // to put the grid more center on screen.
        int32_t new_y = y + (y_remaining / 2);

        for(int32_t x = 0;x <= new_max_width;x++)
        {
            int32_t new_x = x + (x_remaining / 2);
            char print_char[10];
            memset(print_char, 0, sizeof(print_char));

            if (!(y % y_grid_step) && !(x % x_grid_step))
                print_char[0] = '+';
            else if (!(y % y_grid_step))
                print_char[0] = '-';
            else if (!(x % x_grid_step))
                print_char[0] = '|';
            else if ((y % y_grid_step) && (x % x_grid_step))
            {
                // Print in each grid the number of the grid "linearly"
                // It doesn't work well with two digits and more numbers.
                // It prints only the first digit.
                int32_t num = ((y / y_grid_step) * g.y_grid) + (x / x_grid_step);
                snprintf(print_char, sizeof(print_char), "%d", num);
            }

            color_str(win, new_y, new_x, 0, 0, print_char);
        }
    }
}


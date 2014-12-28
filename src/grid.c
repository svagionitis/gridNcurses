#include <string.h>
#include "window.h"
#include "grid.h"
#include "utils.h"

extern window_settings_t win_set;

/**
 * \brief   Print the grid on screen, in the specified window.
 *
 * \param   win Window that the grid will be printed.
 */
void print_grid(WINDOW *win)
{
    getmaxyx(win, win_set.maxGridHeight, win_set.maxGridWidth);

    wclear(win);

    generate_grid(win, win_set.maxGridHeight, win_set.maxGridWidth, color_str);

    wnoutrefresh(win);
}

/**
 * \brief   Generate the grid which will be printed on the specified window.
 *
 * \param   win             Window that the grid will be printed.
 * \param   grid_win_height The height of the grid window.
 * \param   grid_win_width  The width of the grid window.
 * \param   print_scr       The function that will print the grid on screen.
 */
void generate_grid(WINDOW *win, int32_t grid_win_height, int32_t grid_win_width, void (*print_scr)(WINDOW *, uint32_t, uint32_t, int16_t, int16_t, const char *))
{
    // If the grid is larger than the grid window height
    // or width, then set it to this height or width
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
                print_num_in_all_grid(((y / y_grid_step) * g.y_grid) + (x / x_grid_step), print_char);
            }

            (*print_scr)(win, new_y, new_x, 0, 0, print_char);
        }
    }
}

void print_num_in_all_grid(int32_t num, char *str_out)
{
    sprintf(str_out, "%d", num);
}


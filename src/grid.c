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

    // For 1x1, 1x? and ?x1
    if (y_grid_step == grid_win_height)
        y_grid_step -= 1;
    if (x_grid_step == grid_win_width)
        x_grid_step -= 1;

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

            if ((y % y_grid_step) == 0 && (x % x_grid_step) == 0)
                print_char[0] = '+';
            else if ((y % y_grid_step) == 0)
                print_char[0] = '-';
            else if ((x % x_grid_step) == 0)
                print_char[0] = '|';
            else if ((y % y_grid_step) && (x % x_grid_step))
            {
                // Print in each grid the number of the grid "linearly"
                // It doesn't work well with two digits and more numbers.
                // It prints only the first digit.
                print_num_in_all_grid(((y / y_grid_step) * g.y_grid) + (x / x_grid_step), print_char);
                //print_num_in_grid(2, 3, x, y, x_grid_step, y_grid_step, 7, print_char);
                //print_x_in_grid(1, 1, x, y, x_grid_step, y_grid_step, print_char);
                //print_o_in_grid(1, 2, x, y, x_grid_step, y_grid_step, print_char);
            }

            (*print_scr)(win, new_y, new_x, 0, 0, print_char);
        }
    }
}

void print_num_in_all_grid(int32_t num, char *str_out)
{
    sprintf(str_out, "%d", num);
}

void print_num_in_grid(int32_t grid_x, int32_t grid_y, int32_t x, int32_t y, int32_t x_step, int32_t y_step, int32_t num, char *str_out)
{
    if (grid_x == (x / x_step) &&
        grid_y == (y / y_step))
        sprintf(str_out, "%d", num);
    else
        sprintf(str_out, " ");

}

void print_x_in_grid(int32_t grid_x, int32_t grid_y, int32_t x, int32_t y, int32_t x_step, int32_t y_step, char *str_out)
{
    if (grid_x == (x / x_step) &&
        grid_y == (y / y_step))
    {
        int32_t cell_x = x - (grid_x * x_step);
        int32_t cell_y = y - (grid_y * y_step);

        int32_t slope_left_diag = cell_x / cell_y;
        int32_t slope_right_diag = cell_x / (y_step - cell_y);
        int32_t slope_step = x_step / y_step;


        // \ diagonal
        if (slope_left_diag == slope_step && (cell_x % cell_y) == cell_y - 1)
            sprintf(str_out, "\\");
        // / diagonal
        else if (slope_right_diag == slope_step && (cell_x % (y_step - cell_y)) == y_step - cell_y - 1)
            sprintf(str_out, "/");
        else
            sprintf(str_out, " ");
    }
    else
        sprintf(str_out, " ");

}

void print_o_in_grid(int32_t grid_x, int32_t grid_y, int32_t x, int32_t y, int32_t x_step, int32_t y_step, char *str_out)
{
    if (grid_x == (x / x_step) &&
        grid_y == (y / y_step))
    {
        int32_t cell_x = x - (grid_x * x_step);
        int32_t cell_y = y - (grid_y * y_step);

        int32_t radius = MIN(x_step, y_step) / 2;

        if ((cell_x - radius)*(cell_x - radius) + (cell_y - radius)*(cell_y - radius) < radius * radius)
            sprintf(str_out, "O");
        else
            sprintf(str_out, " ");

    }
    else
        sprintf(str_out, " ");

}


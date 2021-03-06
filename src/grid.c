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

    // 1. If x_remaining or y_remaining is 0 then
    //    new_max_height = grid_win_height or new_max_width = grid_win_width
    //    which we don't want.
    // 2. If 1x1 or ?x1 or 1x?, the x_remaining or y_remaining is again 0.
    if (y_remaining == 0)
    {
        y_grid_step -= 1;

        // To find the new height with the changed step we use 
        // the formula new_height = new_step * y_grid.
        y_remaining = grid_win_height - (y_grid_step * g.y_grid);
    }
    if (x_remaining == 0)
    {
        x_grid_step -= 1;

        x_remaining = grid_win_width - (x_grid_step * g.x_grid);
    }

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
                //print_num_in_all_grid(win, new_x, new_y, ((y / y_grid_step) * g.y_grid) + (x / x_grid_step), color_str);
                print_num_in_grid(win, 2, 3, x, y, x_grid_step, y_grid_step, new_x, new_y, 7, color_str);
                print_x_in_grid(win, 0, 0, x, y, x_grid_step, y_grid_step, new_x, new_y, color_str);
                print_o_in_grid(win, 1, 2, x, y, x_grid_step, y_grid_step, new_x, new_y, color_str);
            }

            (*print_scr)(win, new_y, new_x, 0, 0, print_char);
        }
    }
}

void print_num_in_all_grid(WINDOW *win, int32_t print_x, int32_t print_y, int32_t num, void (*print_scr)(WINDOW *, uint32_t, uint32_t, int16_t, int16_t, const char *))
{
    char str_out[10];
    memset(str_out, 0, sizeof(str_out));

    sprintf(str_out, "%d", num);

    (*print_scr)(win, print_y, print_x, 0, 0, str_out);
}

void print_num_in_grid(WINDOW *win, int32_t grid_x, int32_t grid_y, int32_t x, int32_t y, int32_t x_step, int32_t y_step, int32_t print_x, int32_t print_y, int32_t num, void (*print_scr)(WINDOW *, uint32_t, uint32_t, int16_t, int16_t, const char *))
{
    char str_out[10];
    memset(str_out, 0, sizeof(str_out));

    if (grid_x == (x / x_step) &&
        grid_y == (y / y_step))
    {
        sprintf(str_out, "%d", num);

        (*print_scr)(win, print_y, print_x, 0, 0, str_out);
    }
}

void print_x_in_grid(WINDOW *win, int32_t grid_x, int32_t grid_y, int32_t x, int32_t y, int32_t x_step, int32_t y_step, int32_t print_x, int32_t print_y, void (*print_scr)(WINDOW *, uint32_t, uint32_t, int16_t, int16_t, const char *))
{
    char str_out[10];
    memset(str_out, 0, sizeof(str_out));

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

        (*print_scr)(win, print_y, print_x, 0, 0, str_out);
    }
}

void print_o_in_grid(WINDOW *win, int32_t grid_x, int32_t grid_y, int32_t x, int32_t y, int32_t x_step, int32_t y_step, int32_t print_x, int32_t print_y, void (*print_scr)(WINDOW *, uint32_t, uint32_t, int16_t, int16_t, const char *))
{
    char str_out[10];
    memset(str_out, 0, sizeof(str_out));

    if (grid_x == (x / x_step) &&
        grid_y == (y / y_step))
    {
        int32_t cell_x = x - (grid_x * x_step);
        int32_t cell_y = y - (grid_y * y_step);

        int32_t center_x = x_step / 2;
        int32_t center_y = y_step / 2;

        int32_t radius = MIN(x_step, y_step) / 2;

        if ((cell_x - center_x)*(cell_x - center_x) + (cell_y - center_y)*(cell_y - center_y) < radius * radius)
            sprintf(str_out, "O");
        else
            sprintf(str_out, " ");

        (*print_scr)(win, print_y, print_x, 0, 0, str_out);
    }
}


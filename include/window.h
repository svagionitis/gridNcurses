#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <stdint.h>

typedef struct window_settings
{
    int32_t maxWidth;
    int32_t maxHeight;
    int32_t maxHeaderWidth;
    int32_t maxHeaderHeight;
    int32_t maxGridWidth;
    int32_t maxGridHeight;
    int32_t maxFooterWidth;
    int32_t maxFooterHeight;
    int8_t c;
    int8_t last_char;
    uint32_t speed;
    uint64_t days;
}window_settings_t;

window_settings_t win_set;
WINDOW *main_win;

#endif /* WINDOW_H */

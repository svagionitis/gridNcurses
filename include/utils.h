#ifndef UTILS_H
#define UTILS_H

#include <curses.h>
#include <stdint.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void color_str(WINDOW *, uint32_t, uint32_t, int16_t, int16_t, const char *);
void init_seed_srand(void);

#endif /* UTILS_H */

#include <stdlib.h>

#include "background.h"

extern uint16_t *frame_buffer;
extern int display_width;
extern int display_height;

void paint_background(uint16_t col)
{
    // For every pixel change the the colour given
    for (int j = 0; j < display_height; j++)
    {
        uint16_t *p = frame_buffer + j * display_width;
        for (int i = 0; i < display_width; i++)
        {
            *p++ = col;
        }
    }
}
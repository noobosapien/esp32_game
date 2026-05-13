#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "graphics2.h"

// Variables from the game file
extern uint16_t *frame_buffer;
extern int display_width;
extern int display_height;

// Struct for Position for easier calculation
typedef struct pos
{
    int x;
    int y;
} pos;

// Get the length of a position to another position
float len(pos current, pos center)
{
    pos vector = {
        current.x - center.x,
        current.y - center.y};

    return (float)sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

void draw_circle(int x, int y, int radius, uint16_t col)
{
    if (x >= display_width || y >= display_height)
        return;

    // Get the bounding box of 1 diameter width and 1 diameter height
    pos tl = {
        x - radius, y + radius};

    pos tr = {
        x + radius, y + radius};

    pos bl = {
        x - radius, y - radius};

    pos current = tl;

    pos center = {x,
                  y};

    // From each pixel from top left to bottom right...
    while (current.y > bl.y)
    {

        while (current.x < tr.x)
        {
            // From the center if the length of each point inside the the box is less than the radius from the center color it
            // and only if the pixels are inside the display
            if (len(current, center) < (float)radius && current.y > 0 && current.y < display_height && current.x > 0 && current.x < display_width)
            {
                uint16_t *p = frame_buffer + current.y * display_width + current.x;
                *p = col;
            }
            current.x++;
        }

        current.x = tl.x;
        current.y--;
    }
}
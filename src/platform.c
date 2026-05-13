#include <graphics.h>
#include <soc/gpio_struct.h>

#include "platform.h"

PLATFORM_CONFIG *create_platform(int x, int y, int w, int h, int speed)
{
    PLATFORM_CONFIG *platform = malloc(sizeof(PLATFORM_CONFIG));
    platform->x = x;
    platform->y = y;
    platform->w = w;
    platform->h = h;
    platform->speed = speed;

    return platform;
}

void process_platform(PLATFORM_CONFIG *platform, GAME_CONFIG game)
{

    if (!(GPIO.in & 1))
    {
        // Left button pressed
        // Constraint the movement inside the display
        if (platform->x > 0)
            platform->x -= platform->speed * game.delta * 10;
    }

    if (!(GPIO.in1.data & 8))
    {
        
        // Right button pressed
        // Constraint the movement inside the display
        if (platform->x + platform->w < display_width)
            platform->x += platform->speed * game.delta * 10;
    }
}

void render_platform(PLATFORM_CONFIG *platform, GAME_CONFIG game)
{
    if (platform)
    {
        // Draw a rectangle with the values of the platform
        draw_rectangle(platform->x, platform->y, platform->w, platform->h, 0xe20e);
    }
}
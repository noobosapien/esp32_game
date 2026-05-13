#include "game.h"

#ifndef PLATFORM_H
#define PLATFORM_H

typedef struct PLATFORM_CONFIG
{
    int x;
    int y;
    int w;
    int h;
    int speed;
} PLATFORM_CONFIG;

PLATFORM_CONFIG *create_platform(int x, int y, int w, int h, int speed);

void process_platform(PLATFORM_CONFIG *platform, GAME_CONFIG game);
void render_platform(PLATFORM_CONFIG *platform, GAME_CONFIG game);

#endif

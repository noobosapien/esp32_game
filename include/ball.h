#include <stdbool.h>
#include "game.h"
#include "platform.h"

#ifndef BALL_H
#define BALL_H

typedef struct BALL_CONFIG
{
    int x;
    int y;
    int radius;
    int speed;

    struct BALL_CONFIG *next_ball;
} BALL_CONFIG;

BALL_CONFIG *create_ball(int x, int y, int radius, int speed);

void process_ball(BALL_CONFIG *ball, GAME_CONFIG *game);
void render_ball(BALL_CONFIG *ball, GAME_CONFIG game);

bool collide_platform(BALL_CONFIG *ball, PLATFORM_CONFIG *platform);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#include <esp_timer.h>

#include <graphics.h>

#include "game.h"
#include "ball.h"
#include "graphics2.h"
#include "platform.h"

extern PLATFORM_CONFIG *game_platform;
extern GAME_STATE game_state;

BALL_CONFIG *create_ball(int x, int y, int radius, int speed)
{

    // Create a new ball and initialize it's variables and return it
    BALL_CONFIG *ball = malloc(sizeof(BALL_CONFIG));
    ball->x = x;
    ball->y = y;
    ball->radius = radius;
    ball->speed = speed;
    ball->next_ball = NULL;

    return ball;
}

void process_ball(BALL_CONFIG *ball, GAME_CONFIG *game)
{

    if (ball)
    {
        // If the ball is out of the display replace it at the top with random coordiantes
        if (ball->y > display_height)
        {
            int x = rand() % display_width;
            int y = (rand() % display_height) + 10;

            ball->x = x;
            ball->y = -y;

            game->score += 100; // Add 100 to the score when the ball passes the screen
        }

        ball->y += ball->speed * (game->delta * 10); // Add to the y coodinate of the ball it's speed

        bool colliding = collide_platform(ball, game_platform); // Get the bool whether the ball is colliding with the platform

        if (colliding)
        {
            game->to_begin = (int)(esp_timer_get_time() / 1000000) + 10000; // Current time + 10 seconds
            game_state = STOPPED;                                           // Change the state of the game to STOPPED
        }
    }
}

void render_ball(BALL_CONFIG *ball, GAME_CONFIG game)
{
    // Draw a circle at the x, y position of the ball with it's radius
    if (ball)
        draw_circle(ball->x, ball->y, ball->radius, 0xff0f);
}

bool collide_platform(BALL_CONFIG *ball, PLATFORM_CONFIG *platform)
{
    int temp_x = ball->x;
    int temp_y = ball->y;

    // If the ball is above the platform check with the top face
    // If the ball is below the platform check with the down face (optional)
    if (ball->y < platform->y)
    {
        temp_y = platform->y;
    }
    else if (ball->y > platform->y + platform->h)
    {
        temp_y = platform->y + platform->h;
    }

    // If the ball is left the platform check with the left face
    // If the ball is right the platform check with the right face
    if (ball->x < platform->x)
    {
        temp_x = platform->x;
    }
    else if (ball->x > platform->x + platform->w)
    {
        temp_x = platform->x + platform->w;
    }

    int dist_x = ball->x - temp_x;
    int dist_y = ball->y - temp_y;

    float dist = sqrt((dist_x * dist_x) + (dist_y * dist_y));

    if (dist < ball->radius)
        return true;

    return false;
}
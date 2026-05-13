#include "ball.h"

#ifndef BALL_LIST_H
#define BALL_LIST_H

typedef struct BALL_LIST
{
    BALL_CONFIG *first_ball;
    int amount;
} BALL_LIST;

BALL_CONFIG *get_ball(int index);

void add_ball(BALL_CONFIG *ball);

int get_ball_amount();

void remove_all_balls();

#endif
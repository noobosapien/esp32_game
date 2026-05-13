#include <stdio.h>

#include "ball_list.h"
#include "ball.h"

BALL_LIST ball_list =
    {
        NULL, 0}; // Initialize the list

BALL_CONFIG *get_ball(int index)
{
    // If the index is more than the amount of balls or the first ball is NULL
    // return NULL
    if (index > ball_list.amount || ball_list.first_ball == NULL)
        return NULL;

    BALL_CONFIG *ball = ball_list.first_ball;

    // Iterate to the ball of the index and return that
    for (int i = 0; i < index; i++)
    {
        ball = ball->next_ball;
    }

    return ball;
}

void add_ball(BALL_CONFIG *ball)
{

    // If there are no balls in the list add it as the first
    if (ball_list.first_ball == NULL)
    {
        ball_list.first_ball = ball;
    }
    else
    {
        // Go to the end of the list and the add the ball as the next ball

        BALL_CONFIG *last_ball = ball_list.first_ball;

        while (last_ball->next_ball != NULL)
        {
            last_ball = last_ball->next_ball;
        }

        last_ball->next_ball = ball;
    }

    ball_list.amount += 1; // Increment the amount
}

int get_ball_amount()
{
    return ball_list.amount;
}

void remove_all_balls()
{
    // If the list is empty return
    if (ball_list.first_ball == NULL)
    {
        return;
    }
    else
    {
        // Create two pointers to hold the last ball and the ball to free
        BALL_CONFIG *last_ball = ball_list.first_ball;
        BALL_CONFIG *temp = last_ball;

        // While the list continues
        while (last_ball->next_ball != NULL)
        {
            // Point last_ball to the next ball
            last_ball = last_ball->next_ball;

            // Free the previous ball
            if (temp)
                free(temp);

            // Next ball to free will be the last_ball
            temp = last_ball;
        }

        // Remove the last ball
        if (last_ball)
            free(last_ball);

        ball_list.first_ball = NULL; // Point first_ball to NULL
        ball_list.amount = 0;        // The amount in the list is 0 at this point
    }
}

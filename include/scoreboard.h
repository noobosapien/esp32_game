#include "game.h"

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

typedef struct SCORE
{
    int score;
    struct SCORE *next_score;
    struct SCORE *prev_score;
} SCORE;

typedef struct SCOREBOARD
{
    SCORE *first_score;
    int amount;
} SCOREBOARD;

void update_scoreboard(GAME_CONFIG *game);
void show_scoreboard(GAME_CONFIG *game);
int get_num_scores();
void prune_scoreboard(int n);
void remove_score(SCORE *score);

#endif
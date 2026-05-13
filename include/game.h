#include <stdlib.h>
#include <stdbool.h>

#ifndef GAME_H
#define GAME_H

typedef enum GAME_STATE
{
    INIT,
    RUNNING,
    STOPPED
} GAME_STATE;

typedef struct GAME_CONFIG
{
    float delta;
    uint64_t time_before_loop;
    uint64_t last_time;
    float next_level;
    int score;
    float to_begin;
    bool updated_scoreboard;
} GAME_CONFIG;

void initialize_game();

void process_game();

void render_game();

void quit_game();

#endif
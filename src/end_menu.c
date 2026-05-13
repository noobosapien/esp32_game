#include <esp_timer.h>

#include <fonts.h>
#include <graphics.h>

#include "end_menu.h"

extern GAME_STATE game_state; // Get the game state declared in the game file

void show_end_screen(GAME_CONFIG *game)
{
    setFont(FONT_UBUNTU16);
    setFontColour(188, 165, 207);
    print_xy("Score:", CENTER, LASTY + 20); // Show the score
    gprintf("  %d", game->score);
}

void show_countdown(GAME_CONFIG *game)
{
    setFont(FONT_SMALL);
    setFontColour(188, 165, 207);
    print_xy("Back to menu in:", CENTER, LASTY + 20);
    print_xy("", CENTER, LASTY + 20);

    gprintf("%d s", (int)game->to_begin / 1000); // Show the countdown to the init menu

    game->to_begin = (game->to_begin - (game->delta * 1000));

    if (game->to_begin <= 0)
    {
        game_state = INIT;
    }
}

#include <stdint.h>

#include <fonts.h>
#include <graphics.h>

#include "score.h"

void show_running_score(GAME_CONFIG game)
{
    // Show the score at the top of the screen
    setFont(FONT_SMALL);
    setFontColour(188, 165, 207);
    print_xy("Score:", CENTER, LASTY + 10);
    gprintf("  %d", game.score);
}
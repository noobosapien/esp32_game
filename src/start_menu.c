#include <soc/gpio_struct.h>
#include <fonts.h>
#include <graphics.h>

#include "start_menu.h"
#include "ball_list.h"
#include "ball.h"

extern int display_width;
extern int display_height;

extern const int init_no_of_balls;

extern PLATFORM_CONFIG *game_platform;

void process_init_input(GAME_STATE *game_state, GAME_CONFIG *game)
{

    if (!(GPIO.in & 1))
    {
        // Initialize the values to start
        game->score = 0;
        game->next_level = 10;
        game->to_begin = 10;
        game->updated_scoreboard = false;

        if (game_platform)
            free(game_platform);

        // Create the platform to the center of the x-axis
        game_platform = create_platform((display_width / 2) - display_width / 8, display_height - 40, display_width / 4, display_height / 40, 10);

        // Remove if there are any existing balls
        remove_all_balls();

        // Create new balls with the initial number of balls
        for (int i = 0; i < init_no_of_balls; i++)
        {
            int x = rand() % display_width;
            int y = (rand() % (display_height * 2)) + 10;
            int size = (rand() % 3) + 4;
            int speed = (rand() % 4) + 8;

            BALL_CONFIG *ball = create_ball(x, -y, size, speed);
            add_ball(ball);
        }

        // Left button pressed: start the game
        *game_state = RUNNING;
    }
}

void show_menu(GAME_CONFIG game)
{

    // Show the menu starting from the top and x-centered
    setFont(FONT_UBUNTU16);
    setFontColour(128, 114, 140);
    print_xy("Press the left", CENTER, LASTY + 20);
    print_xy("key to start", CENTER, LASTY + 15);
    print_xy("the game", CENTER, LASTY + 15);

    setFont(FONT_SMALL);
    setFontColour(188, 165, 207);
    print_xy("Instructions:", CENTER, LASTY + 40);
    print_xy("Avoid the falling", CENTER, LASTY + 10);
    print_xy("balls", CENTER, LASTY + 10);
    print_xy("using the left", CENTER, LASTY + 10);
    print_xy("and right buttons", CENTER, LASTY + 10);
}
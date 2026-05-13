#include <driver/gpio.h>

#include <esp_system.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <esp_timer.h>

#include <math.h>
#include <esp_log.h>
#include <esp_sntp.h>
#include <nvs_flash.h>

#include <graphics.h>

#include "game.h"
#include "platform.h"
#include "ball.h"
#include "ball_list.h"
#include "background.h"
#include "start_menu.h"
#include "score.h"
#include "end_menu.h"
#include "scoreboard.h"

GAME_STATE game_state;
GAME_CONFIG game_config;
const int init_no_of_balls = 3;

PLATFORM_CONFIG *game_platform = NULL; // The platform that should avoid the balls

void initialize_game()
{
    game_state = INIT; // Set the initial state

    // Initialize the ESP
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    setenv("TZ", "NZST-12:00:00NZDT-13:00:00,M9.5.0,M4.1.0", 0);
    tzset();
    graphics_init();
    set_orientation(1 - get_orientation()); // Set the orientation to potrait mode
    cls(0);                                 // Clear the screen

    // Initialize the game variables
    game_config.delta = 0.f;
    game_config.last_time = game_config.time_before_loop = esp_timer_get_time();
    game_config.next_level = 10;
    game_config.score = 0;
    game_config.to_begin = 10;
    game_config.updated_scoreboard = false;

    srand(time(NULL)); // For random numbers
}

void process_game()
{
    // Infinite loop for the task
    for(;;){

        game_config.time_before_loop = esp_timer_get_time(); // Time before the loop

        // Calculate the delta which is last time loop finished with the current time
        game_config.delta = (float)(game_config.time_before_loop - game_config.last_time) / 1000000;

        // Cap the delta if it goes over the limit
        if (game_config.delta > 0.05)
            game_config.delta = 0.05;

        switch (game_state)
        {
        case INIT:
            // Process the input for the menu
            process_init_input(&game_state, &game_config);
            break;

        case RUNNING:
            // Subtract delta from next_level counter
            game_config.next_level = game_config.next_level - game_config.delta;

            // When the next_level counter hits 0
            if (game_config.next_level <= 0.f)
            {
                    game_config.next_level = 10; // Reset the counter

                    // Create random values for the new ball
                    int x = rand() % display_width;
                    int y = (rand() % (display_height * 2)) + 10;
                    int size = (rand() % 3) + 4;
                    int speed = (rand() % 4) + 8; // Variable speed at the start but will increase with time for each ball

                    // Create a new ball from the random variables and add it to the list
                    BALL_CONFIG *new_ball = create_ball(x, -y, size, speed);
                    add_ball(new_ball);

                    // For every ball increase the speed with every level
                    for (int i = 0; i < get_ball_amount(); i++)
                    {
                        BALL_CONFIG *ball = get_ball(i);
                        ball->speed += 1; // Increase the speed of every ball each level by 1
                    }

                    
            }

            // Process the platform
            process_platform(game_platform, game_config);

            // Process the falling balls
            for (int i = 0; i < get_ball_amount(); i++)
            {
                BALL_CONFIG *ball = get_ball(i);
                process_ball(ball, &game_config);
            }

            break;

        case STOPPED:
            // Process the scoreboard
            update_scoreboard(&game_config);
            break;

        default:
            break;
        }

        game_config.last_time = esp_timer_get_time(); // For the delta calculation

        vTaskDelay(2);
    }
    

}

void render_game()
{
    // Infinite loop for the task
    for(;;){
        cls(0); // Clear the screen

        switch (game_state)
        {
        case INIT:
            paint_background(0x2006); // Paint the background
            show_menu(game_config);   // Render the instructions
            break;

        case RUNNING:

            // Paint a better background
            paint_background(0x2006);
            show_running_score(game_config);

            // Render the platform
            render_platform(game_platform, game_config);

            // Render the falling balls
            for (int i = 0; i < get_ball_amount(); i++)
            {
                BALL_CONFIG *ball = get_ball(i);
                render_ball(ball, game_config);
            }

            break;

        case STOPPED:
            paint_background(0x2006);      // Paint the background
            show_end_screen(&game_config); // Show the score
            show_countdown(&game_config);  // Show the countdown for the menu
            show_scoreboard(&game_config); // Show the scoreboard
            break;

        default:
            break;
        }

        flip_frame(); // Flip the frame to show it on the screen
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    
}

// In the end remove all resources
void quit_game()
{
    if (game_platform)
        free(game_platform); // If there is a platform present free it

    remove_all_balls(); // Remove all the balls

    prune_scoreboard(0); // Remove all scores
}
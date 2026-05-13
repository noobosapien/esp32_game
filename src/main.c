#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "game.h"
#include "interrupts.h"

void app_main()
{
    set_interrupts();
    initialize_game(); // Initialize the game

        xTaskCreate(
            process_game, "Process Task", 1024*32, NULL, 1, NULL
        );

        xTaskCreate(
            render_game, "Render Task", 1024*32, NULL, 1, NULL
        );

    // quit_game(); // At the end release all resources
}
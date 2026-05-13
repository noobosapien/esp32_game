#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_timer.h>

static void IRAM_ATTR gpio_isr_handler(void* arg);
void set_interrupts();

#endif
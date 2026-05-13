# ESP32 FreeRTOS Arcade Game

A real-time embedded arcade game developed on the ESP32 using the ESP-IDF framework and FreeRTOS.
The project demonstrates multitasking, interrupt-driven input handling, frame-buffer graphics rendering, collision detection, dynamic memory management, and custom game-state architecture in an embedded environment.

---

## Project Overview

This game is about the player controlling the platform to avoid falling balls. It progressively increases difficulty by spawning additional balls and increasing movement speed over time.

The system design:

* Real-time task scheduling with FreeRTOS
* Hardware interrupt handling
* Embedded graphics rendering
* Dynamic object management
* Collision detection algorithms
* State-machine architecture
* Low-level GPIO interaction
* Timing and delta-time game loops
* Memory management in constrained systems

---

## Gameplay

### Objective

Avoid colliding with falling balls for as long as possible.

### Controls

* Left button → Move platform left
* Right button → Move platform right

### Features

* Dynamic difficulty scaling
* Increasing ball speed over time
* Real-time score tracking
* Persistent top-5 scoreboard during runtime
* Start menu and end-game screen
* Smooth rendering using frame-buffer flipping

---

## System Architecture

### Core Tasks

The application is divided into two concurrent FreeRTOS tasks:

| Task             | Purpose                                                  |
| ---------------- | -------------------------------------------------------- |
| `process_game()` | Handles game logic, physics, input, collisions, spawning |
| `render_game()`  | Handles graphics rendering and frame updates             |

---

## Technical Highlights

### FreeRTOS Multitasking

The game logic and rendering engine execute independently using FreeRTOS tasks:

```c
xTaskCreate(process_game, "Process Task", 1024*32, NULL, 1, NULL);
xTaskCreate(render_game, "Render Task", 1024*32, NULL, 1, NULL);
```

### Interrupt-Driven GPIO Input

Hardware interrupts are configured for responsive button handling:

```c
gpio_set_intr_type(0, GPIO_INTR_POSEDGE);
gpio_set_intr_type(35, GPIO_INTR_ANYEDGE);
```

### Delta-Time Based Physics

Movement and timing are frame-rate independent using delta timing:

```c
game_config.delta =
(float)(game_config.time_before_loop - game_config.last_time) / 1000000;
```

### Collision Detection

Custom circle-vs-rectangle collision detection was implemented for gameplay physics.

### Dynamic Object Management

Balls are dynamically allocated and stored in a linked list structure:

```c
BALL_CONFIG *new_ball = create_ball(x, -y, size, speed);
add_ball(new_ball);
```

### Real-Time Rendering Pipeline

Graphics are rendered using a double-buffer/frame-buffer style architecture:

---

## Software Design

### State Machine

The game operates using a finite state machine:

```text
INIT → RUNNING → STOPPED → INIT
```

| State     | Description              |
| --------- | ------------------------ |
| `INIT`    | Menu and initialization  |
| `RUNNING` | Active gameplay          |
| `STOPPED` | Game over and scoreboard |

---

## Data Structures

### Linked List Ball System

Dynamic linked lists are used to manage active game objects efficiently.

### Scoreboard

A sorted doubly linked list stores the top scores during runtime.

---

## Hardware

### Target Platform

* ESP32 Tdisplay (TTGO) Development Board

### Peripherals Used

* GPIO buttons
* LCD/TFT Display
* Hardware timer
* Interrupt controller

---

## Technologies Used

* Embedded C
* ESP-IDF
* FreeRTOS
* GPIO Drivers
* ESP Timer APIs
* Frame-buffer Graphics
* Dynamic Memory Allocation

---

## Key Concepts

### Real-Time Systems

* Deterministic task execution
* Cooperative multitasking
* Time-sensitive rendering

### Memory Management

* Heap allocation
* Runtime object creation/destruction
* Linked list traversal

### Hardware Interaction

* GPIO register access
* Interrupt service routines
* Hardware timing

### Software Engineering

* Modular architecture
* Separation of concerns
* Scalable game-state design

---

## Example Game Loop

```c
for(;;)
{
    process_platform(game_platform, game_config);

    for (int i = 0; i < get_ball_amount(); i++)
    {
        BALL_CONFIG *ball = get_ball(i);
        process_ball(ball, &game_config);
    }

    vTaskDelay(2);
}
```

---

## Future Improvements

Potential future enhancements include:

* Better time loop delta calculation
* Add more tasks for physics and other processing
* Use FreeRTOS queues with interrupt handlers to add which button was pressed
* Deallocate resources after the game exit

---

### Skills Included

* Embedded software architecture
* FreeRTOS task management
* Interrupt-driven systems
* Real-time graphics programming
* Low-level hardware interaction
* Algorithm implementation
* Memory-safe dynamic allocation
* Debugging embedded applications
* Modular firmware design

### Engineering Aspect

* Concurrent execution
* Hardware abstraction
* Event-driven systems
* Efficient rendering pipelines
* Scalable code organization

---

## Build Environment

### Recommended Toolchain

* ESP-IDF
* GCC for Xtensa
* PlatformIO
* FreeRTOS
* Ubuntu/Linux development environment

---

## Debugging log

* Creating different tasks for rendering and processing made the balls halt in one place. Tried adding semaphores, but it didn't fix the issue. It turned out that there needed to be a task delay for each task.
* Slowed game loop after the semaphore. The semaphore was barring the two tasks, but it wasn't needed.
* The right button didn't register until the interrupt handlers were introduced.
* The platform was slowed heavily due to increased task delay. It was fixed by tuning the correct number of ticks to delay.

---

## Demo

### Many allocations of falling balls and the platform is functioning normally.

https://github.com/user-attachments/assets/45b277a0-8e61-42bb-9e31-eeb74966c604

### Gameplay

https://github.com/user-attachments/assets/61a54d85-472c-4b02-aaf4-00f9d07f2e14


  

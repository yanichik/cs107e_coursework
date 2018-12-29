#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>


typedef enum {
    MOUSE_BUTTON_PRESS = 0,
    MOUSE_BUTTON_RELEASE = 1,
    MOUSE_MOVED = 2,
    MOUSE_DRAGGED = 3,
} mouse_action_t;


typedef struct {
    mouse_action_t action;
    int dx, dy;
    bool x_overflow, y_overflow;
    bool left, middle, right;
} mouse_event_t;

/*
 * `mouse_init`: Required initialization for mouse
 *
 * The mouse must first be initialized before any mouse events can be read.
 * The mouse clock line should be connected to GPIO_PIN25 and data line to GPIO_PIN26.
 * Returns true if able to initialize mouse, false otherwise.
 */
bool mouse_init(void);

/*
 * `mouse_read_event`
 *
 * The function reads (blocking) the next event from the mouse.
 * Returns a `mouse_event_t` struct that represents the mouse event.  The
 * struct includes the relative change in x and y (dx, dy fields). A delta
 * value will be in range +/- 255, the x_overflow/y_overflow fields are true 
 * if actual valueof dx/dy exceeded +/- 255.  The left/middle/right fields 
 * give the state of the mouse buttons. Each field is true if the corresponding 
 * mouse button is down, false otherwise.
 */
mouse_event_t mouse_read_event(void);

#endif

#include "pacman.h"
#include <stdlib.h>

/**
 * Move pacman to the chosen position.
 */
static void set_position(Pacman *pacman, Position *pos) {
    pacman->pos = *pos;
}

/**
 * Set the x-y coordinate position of pacman.
 */
static void set_coordinates(Pacman *pacman, int x, int y) {
    pacman->pos.x = x;
    pacman->pos.y = y;
}

/**
 * Get the position of pacman.
 */
static void get_position(Pacman *pacman, Position *pos) {
    *pos = pacman->pos;
}

/**
 * Get the x-y coordinate position of pacman.
 */
static void get_coordinates(Pacman *pacman, int *x, int *y) {
    *x = pacman->pos.x;
    *y = pacman->pos.y;
}

/**
 * Set Pacman's direction and change his sprite accordingly.
 */
static void set_direction(Pacman *pacman, Direction dir) {
    pacman->dir = dir;
    switch (dir) {
    case LEFT:
        pacman->sprite = '<';
        break;
    case RIGHT:
        pacman->sprite = '>';
        break;
    case UP:
        pacman->sprite = '^';
        break;
    case DOWN:
        pacman->sprite = 'v';
        break;
    }
}

/**
 * Increase pacmans food consumption total.
 */
static void eat(Pacman *pacman) {
    pacman->food_count++;
    pacman->score += 10;
}

/**
 * Remove one of pacmans lives.
 * Returns the total lives remaining.
 */
static int lose_life(Pacman *pacman) {
    pacman->lives--;
    return pacman->lives;
}

/**
 * Reset Pacman.
 */
static void reset(Pacman *pacman) {
    pacman->pos = new_position(13, 23);
    pacman->dir = RIGHT;
    pacman->food_count = 0;
    pacman->score = 0;
}


/**
 * Release memory held by pacman.
 */
static void release(Pacman *pacman) {
    // Release resources.
}

/**
 * Create a new instance of pacman.
 */
Pacman * new_pacman(Pacman *self) {
    if (self) {
        self->lives = 3;
        self->colour = YELLOW;
        self->sprite = '>';
        reset(self);

        self->eat = &eat;
        self->lose_life = &lose_life;
        self->set_direction = &set_direction;
        self->move = &set_position;
        self->set_coords = &set_coordinates;
        self->get_pos = &get_position;
        self->get_coords = &get_coordinates;
        self->reset = &reset;
        self->release = &release;
    }
    return self;
}

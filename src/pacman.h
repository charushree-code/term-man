#ifndef TERMMAN_PACMAN_H
#define TERMMAN_PACMAN_H

#include "std_objects.h"

/**
 * Pacman himself
 */
typedef struct Pacman {
    Direction dir;
    Position pos;
    unsigned char sprite;
    Colour colour;
    int food_count;
    int lives;
    int score;

    void (*eat)(struct Pacman *self);
    void (*set_direction)(struct Pacman *self, Direction dir);
    int (*lose_life)(struct Pacman *self);

    void (*move)(struct Pacman *self, Position *pos);
    void (*set_coords)(struct Pacman *self, int x, int y);

    void (*get_pos)(struct Pacman *self, Position *pos);
    void (*get_coords)(struct Pacman *self, int *x, int *y);

    void (*reset)(struct Pacman *self);
    void (*release)(struct Pacman *self);
} Pacman;

/**
 * Create a new instance of ghost
 */
Pacman * new_pacman(Pacman *self);

#endif

#ifndef TERMMAN_PACMAN_H
#define TERMMAN_PACMAN_H

#include "std_objects.h"

struct private_t;

/*
 * Pacman himself.
 */
typedef struct Pacman {
    unsigned char (*sprite)(struct Pacman *self);
    void (*eat)(struct Pacman *self);
    int (*score)(struct Pacman *self);

    int (*lose_life)(struct Pacman *self);
    int (*lives)(struct Pacman *self);

    void (*set_direction)(struct Pacman *self, Direction dir);
    Direction (*direction)(struct Pacman *self);

    void (*set_position)(struct Pacman *self, Position pos);
    Position (*position)(struct Pacman *self);

    void (*reset)(struct Pacman *self);
    void (*release)(struct Pacman *self);

    struct private_t *private;
} Pacman;

/*
 * Create a new instance of pacman.
 */
Pacman * new_pacman(Pacman *self);

#endif

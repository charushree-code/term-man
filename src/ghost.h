#ifndef TERMMAN_GHOST_H
#define TERMMAN_GHOST_H

#include "std_objects.h"

typedef enum {CHASE, SCATTER, FRIGHTENED} GhostMode;
typedef enum {BLINKY, PINKY, INKY, CLYDE} GhostName;

/**
 * The ghost character in pacman.
 */
typedef struct Ghost {
    Position pos;
    Position target_tile;
    Direction dir;
    Direction future_dir;

    GhostName name;
    GhostMode mode;
    Colour colour;
    unsigned char sprite;
    

    void (*move_tile)(struct Ghost *self, Dimension *dims);
    void (*target)(struct Ghost *self, int x, int y);
    int (*at_target)(struct Ghost *self, Dimension *dims);
    Position (*next_position)(struct Ghost *self, Dimension *dims);

    void (*set_pos)(struct Ghost *self, Position *pos);
    void (*set_coords)(struct Ghost *self, int x, int y);

    void (*get_pos)(struct Ghost *self, Position *pos);
    void (*get_coords)(struct Ghost *self, int *x, int *y);

    void (*reset)(struct Ghost *self);
    void (*reverse)(struct Ghost *self);
    void (*release)(struct Ghost *self);
} Ghost;

Ghost * new_ghost_blinky(Ghost *self);
Ghost * new_ghost_pinky(Ghost *self);
Ghost * new_ghost_inky(Ghost *self);
Ghost * new_ghost_clyde(Ghost *self);

#endif

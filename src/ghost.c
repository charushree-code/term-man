#include <stdlib.h>
#include "ghost.h"

/**
 * Change position based on the direction.
 */
static void change_position(Position *pos, Dimension *dims, Direction dir) {
    switch (dir) {
    case UP:
        pos->y = (pos->y > 0) ? pos->y - 1 : dims->height - 1;
        break;
    case DOWN:
        pos->y = (pos->y < dims->height - 1) ? pos->y + 1 : 0;
        break;
    case LEFT:
        pos->x = (pos->x > 0) ? pos->x - 1 : dims->width - 1;
        break;
    case RIGHT:
        pos->x = (pos->x < dims->width - 1) ? pos->x + 1 : 0;
        break;
    }
}

/**
 * Move the ghost based on its current direction.
 * Ghost plans one move ahead so change to the next direction after moving.
 */
static void move(Ghost *ghost, Dimension *dims) {
    change_position(&ghost->pos, dims, ghost->dir);
    ghost->dir = ghost->future_dir;
}

/**
 * Move ghost to the chosen position.
 */
static void set_position(Ghost *ghost, Position *pos) {
    ghost->pos = *pos;
}

/**
 * Set the x-y coordinate position of the ghost.
 */
static void set_coordinates(Ghost *ghost, int x, int y) {
    ghost->pos.x = x;
    ghost->pos.y = y;
}

/**
 * Get the position of the ghost.
 */
static void get_position(Ghost *ghost, Position *pos) {
    *pos = ghost->pos;
}

/**
 * Get the x-y coordinate position of the ghost.
 */
static void get_coordinates(Ghost *ghost, int *x, int *y) {
    *x = ghost->pos.x;
    *y = ghost->pos.y;
}

/**
 * Get the next position of the ghost.
 */
static Position get_next_position(Ghost *ghost, Dimension *dims) {
    Position pos = ghost->pos;
    change_position(&pos, dims, ghost->dir);
    return pos;
}

/**
 * Set target tile.
 */
static void set_target(Ghost *ghost, int x, int y) {
    ghost->target_tile = new_position(x, y);
}

/**
 * Check if the ghost is at the target tile.
 * Returns:
 *  0:  not at target
 *  1:  at target tile
 */
static int at_target(Ghost *ghost, Dimension *dims) {
    return compare_positions(ghost->next_position(ghost, dims), ghost->target_tile);
}

/**
 * Reset the ghost.
 */
static void reset(Ghost *ghost) {
    ghost->pos = new_position(13, 11);
    ghost->dir = SAME;
    ghost->future_dir = LEFT;
}

/**
 * Release memory held by ghost.
 */
static void release(Ghost *ghost) {
    // Release resources
}

/**
 * Reverse the direction of the ghost.
 */
static void reverse(Ghost *ghost) {
    switch (ghost->dir) {
    case LEFT:
        ghost->dir = RIGHT;
        break;
    case RIGHT:
        ghost->dir = LEFT;
        break;
    case UP:
        ghost->dir = DOWN;
        break;
    case DOWN:
        ghost->dir = UP;
        break;
    }
}

/**
 * Create a new instance of a generic ghost.
 */
static Ghost * new_ghost(Ghost *ghost) {
    if (ghost) {
        ghost->mode = SCATTER;
        reset(ghost);

        ghost->move_tile = &move;
        ghost->set_pos = &set_position;
        ghost->set_coords = &set_coordinates;
        ghost->get_pos = &get_position;
        ghost->get_coords = &get_coordinates;
        ghost->reverse = &reverse;
        ghost->target = &set_target;
        ghost->at_target = &at_target;
        ghost->next_position = &get_next_position;
        ghost->reset = &reset;
        ghost->release = &release;
    }
    return ghost;
}

/**
 * Create a new instance of Blinky.
 */
Ghost * new_ghost_blinky(Ghost *ghost) {
    if (ghost) {
        ghost = new_ghost(ghost);
        ghost->name = BLINKY;
        ghost->sprite = 'B';
        ghost->colour = RED;
    }
    return ghost;
}

/**
 * Create a new instance of Pinky.
 */
Ghost * new_ghost_pinky(Ghost *ghost) {
    if (ghost) {
        ghost = new_ghost(ghost);
        ghost->name = PINKY;
        ghost->sprite = 'P';
        ghost->colour = PINK;
    }
    return ghost;
}

/**
 * Create a new instance of Inky.
 */
Ghost * new_ghost_inky(Ghost *ghost) {
    if (ghost) {
        ghost = new_ghost(ghost);
        ghost->name = INKY;
        ghost->sprite = 'I';
        ghost->colour = CYAN;
    }
    return ghost;
}

/**
 * Create a new instance of Clyde.
 */
Ghost * new_ghost_clyde(Ghost *ghost) {
    if (ghost) {
        ghost = new_ghost(ghost);
        ghost->name = CLYDE;
        ghost->sprite = 'C';
        ghost->colour = ORANGE;
    }
    return ghost;
}

#include "std_objects.h"

/**
 * Return a position based on given coordinates.
 */
Position new_position(int x, int y) {
    Position pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

/**
 * Return a position based on given coordinates.
 */
Position new_position_with_wrap(int x, int y, Dimension *dims) {
    Position pos;
    pos.x = x % dims->width;
    pos.y = y % dims->height;

    if (pos.x < 0) {
        pos.x += dims->width - 1;
    }
    if (pos.y < 0) {
        pos.y += dims->height - 1;
    }

    return pos;
}

/**
 * Get the distance between two x coordinates.
 */
int get_distance(int p1, int p2) {
    return (p2 - p1 > 0) ? (p2 - p1) : (p1 - p2);
}

/**
 * Get the distance between two tiles using coordinates.
 * Dirty way to do it to avoid including math library (for FPGA purposes).
 */
int get_distance_coords(int x1, int y1, int x2, int y2) {
    int a = get_distance(x1, x2);
    int b = get_distance(y1, y2);
    return (a * a + b * b);
}

/**
 * Get the distance between two tiles.
 * Dirty way to do it to avoid including math library (for FPGA purposes).
 */
int get_distance_pos(Position *pos, Position *target_pos) {
    int a = get_distance(target_pos->x, pos->x);
    int b = get_distance(target_pos->y, pos->y);
    return (a * a + b * b);
}

/**
 * Compare two positions.
 * Return values:
 *  0:  positions are different
 *  1:  positions are equal
 */
int compare_positions(Position pos1, Position pos2) {
    return ((pos1.x == pos2.x) && (pos1.y == pos2.y)) ? 1 : 0;
}

/**
 * Get the new coordinates based on the input direction.
 */
Position get_position_from_direction(Position pos, Dimension dims, Direction dir) {
    switch (dir) {
    case UP:
        pos.y = (pos.y > 0) ? pos.y - 1 : dims.height - 1;
        break;
    case DOWN:
        pos.y = (pos.y < dims.height - 1) ? pos.y + 1 : 0;
        break;
    case LEFT:
        pos.x = (pos.x > 0) ? pos.x - 1 : dims.width - 1;
        break;
    case RIGHT:
        pos.x = (pos.x < dims.width - 1) ? pos.x + 1 : 0;
        break;
    }
    return pos;
}

/**
 * Get the direction from keyboard input.
 */
Direction get_direction_from_input(unsigned char input) {
    switch (input) {
    case 'W':
    case 'w': return UP;
    case 'S':
    case 's': return DOWN;
    case 'A':
    case 'a': return LEFT;
    case 'D':
    case 'd': return RIGHT;
    }
    return SAME;
}

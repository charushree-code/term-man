#ifndef TERMMAN_MAP_H
#define TERMMAN_MAP_H

#include "std_objects.h"
#include "ghost.h"
#include "pacman.h"

/**
 * Stores the layout of the map.
 * Holds the position and size of a coordinate system.
 * layout:  stores the layout terrain of the map
 * pos:     x-y coordinate position inside the map
 * dims:    width and height dimensions of the map
 */
typedef struct Map {
    Terrain (*layout)[MAX_Y][MAX_X];
    Position origin;
    Dimension dims;

    void (*detect_pacman_collision)(struct Map *self, Pacman *pacman, Position *new_pos);
    int (*detect_collision)(struct Map *self, Position *new_pos);
    int (*detect_collision_coords)(struct Map *self, int x, int y);
    int (*intersection)(struct Map *self, Position *pos);

    void (*set_object)(struct Map *self, Position *pos, Terrain terrain);
    Terrain (*get_object)(struct Map *self, Position *pos);
    unsigned char (*draw_terrain)(Terrain terrain);

    void (*get_map_level)(struct Map *self);
    void (*release)(struct Map *self);
} Map;

/**
 * Create a new instance of map.
 */
Map * new_map(Map *self);

#endif

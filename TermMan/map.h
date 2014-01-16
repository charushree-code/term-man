#ifndef TERMMAN_MAP_H
#define TERMMAN_MAP_H

#include "std_objects.h"
#include "ghost.h"
#include "pacman.h"

/**
 * Stores the layout of the map.
 * Holds the position and size of a coordinate system.
 * layout:	stores the layout terrain of the map
 * pos:		x-y coordinate position inside the map
 * dims:	width and height dimensions of the map
 */
typedef struct map_t {
	terrain_t (*layout)[MAX_Y][MAX_X];
	position_t origin;
	dimension_t dims;

	void (*detect_pacman_collision)(struct map_t *self, pacman_t *pacman, position_t *new_pos);
	int (*detect_collision)(struct map_t *self, position_t *new_pos);
	int (*detect_collision_coords)(struct map_t *self, int x, int y);
	int (*intersection)(struct map_t *self, position_t *pos);

	void (*set_object)(struct map_t *self, position_t *pos, terrain_t terrain);
	terrain_t (*get_object)(struct map_t *self, position_t *pos);
	unsigned char (*draw_terrain)(terrain_t terrain);

	void (*get_map_level)(struct map_t *self);
	void (*release)(struct map_t *self);
} map_t;

/**
 * Create a new instance of map.
 */
map_t * new_map();

#endif

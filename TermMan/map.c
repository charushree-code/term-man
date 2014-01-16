#include <stdlib.h>
#include "map.h"
#include "level_defs.h"

/**
 * Detect a collision between pacman and map terrain.
 */
static void detect_pacman_collision(map_t *map, pacman_t *pacman, position_t *new_pos) {

	if (map->get_object(map, new_pos) != WALL && map->get_object(map, new_pos) != GATE) {
		pacman->move(pacman, new_pos);

		if (map->get_object(map, new_pos) == FOOD) {
			pacman->eat(pacman);
			map->set_object(map, new_pos, PATH);
		}
	}
}

/**
 * Detect the type of collision at a chosen position with an object on the map.
 * Return types:
 * 0:	non-blocking collision
 * 1:	blocking collision
 * -1:	out of bounds
 */
static int collision(terrain_t terrain) {
	switch (terrain) {
		case PATH: return 0;
		case FREE: return 0;
		case FOOD: return 0;
		case GATE: return 1;
		case WALL: return 1;
	}

	return 1;
}

/**
 * Detect the type of collision at a chosen position with an object on the map.
 * Return types:
 * 0:	non-blocking collision
 * 1:	blocking collision
 * -1:	out of bounds
 */
static int detect_collision(map_t *map, position_t *pos) {

	if (pos->x < 0 || pos->x > map->dims.width - 1) {
		return 0;
	}

	return collision(map->get_object(map, pos));
}

/**
 * Detect the type of collision at a chosen x-y coordinate position with an object on the map.
 */
static int detect_collision_coords(map_t *map, int x, int y) {
	position_t pos = new_position(x, y);

	return (detect_collision(map, &pos));
}

/**
 * Set the terrain of the map at the defined position.
 */
static void set_object(map_t *map, position_t *pos, terrain_t terrain) {
	(*map->layout)[pos->y][pos->x] = terrain;
}

/**
 * Get the terrain of the map at the defined position.
 */
static terrain_t get_object(map_t *map, position_t *pos) {
	return (*map->layout)[pos->y][pos->x];
}

/**
 * Choose the ASCII character to represent the given terrain on the map.
 */
static unsigned char draw_terrain(terrain_t terrain) {
	unsigned char out;

	switch(terrain) {
		case WALL:
			out = 'X';
			break;
		case PATH:
		case FREE:
			out = ' ';
			break;
		case GATE:
			out = '_';
			break;
		case FOOD:
			out = '*';
			break;
	}

	return out;
}

/**
 * Loads the map with the given level.
 */
static void get_map_level(map_t *map) {
	unsigned char i, j;

	map->dims.height = MAX_Y;
	map->dims.width = MAX_X;
	/*
	for (i = 0; i < map->dims.height; i++) {
		for (j = 0; j < map->dims.width; j++) {
			map->layout[i][j] = level[i][j];
		}
	}*/
	map->layout = &level;
}

/**
 * Release memory held by the map.
 */
static void release(map_t *map) {
	free(map);
}

/**
 * Check for an intersection point on the map.
 * Return values:
 * 0:	no intersection
 * 1:	intersection
 */
int intersection(map_t *map, position_t *pos) {
	bool_t x_check = NO, y_check = NO;	// Flag to determine path availablility

	x_check = (!collision((*map->layout)[pos->y][pos->x - 1])) ? YES : x_check;	// Left check
	x_check = (!collision((*map->layout)[pos->y][pos->x + 1])) ? YES : x_check;	// Right check
	y_check = (!collision((*map->layout)[pos->y - 1][pos->x])) ? YES : y_check;	// Up check
	y_check = (!collision((*map->layout)[pos->y + 1][pos->x])) ? YES : y_check;	// Down check

	return (y_check == YES && x_check == YES) ? 1 : 0;
}

/**
 * Return a new instance of map.
 */
map_t * new_map() {
	map_t *map = malloc(sizeof(map_t));

	map->set_object = &set_object;
	map->get_object = &get_object;
	map->detect_pacman_collision = &detect_pacman_collision;
	map->detect_collision = &detect_collision;
	map->detect_collision_coords = &detect_collision_coords;
	map->intersection = &intersection;
	map->draw_terrain = &draw_terrain;
	map->get_map_level = &get_map_level;
	map->release = &release;

	return map;
}

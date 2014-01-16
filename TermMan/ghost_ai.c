#include "ghost_ai.h"
#include "std_objects.h"

#define NO_DIST	100000

/**
 * Set the path of the ghost.
 * The ghost will not 
 * There are certain conditions which limit the path the ghost can take.
 * 	1. The ghost cannot reverse it's direction.
 * 	2. A path can only be set at an intersection.
 * 	3. The ghost will choose the shortest path to it's target tile.
 * 	4. If there are equal distance paths to the target tile, the order of path chosen is UP, DOWN, LEFT, RIGHT.
 */
void set_path(ghost_t *ghost, map_t *map) {
	int left = NO_DIST, right = NO_DIST, up = NO_DIST, down = NO_DIST;
	position_t new_pos = ghost->next_position(ghost, &map->dims);
	int x_wrap;
	
	x_wrap = ((new_pos.x - 1) >= 0) ? new_pos.x - 1 : map->dims.width - 1;
	if ((map->detect_collision_coords(map, x_wrap, new_pos.y) == 0) && (ghost->dir != RIGHT)) {	// Distance from left tile
		left = get_distance_coords(x_wrap, new_pos.y, ghost->target_tile.x, ghost->target_tile.y);
	}
	x_wrap = ((new_pos.x + 1) <= map->dims.width - 1) ? new_pos.x + 1 : 0;
	if ((map->detect_collision_coords(map, x_wrap, new_pos.y) == 0) && (ghost->dir != LEFT)) {	// Distance from right tile
		right = get_distance_coords(x_wrap, new_pos.y, ghost->target_tile.x, ghost->target_tile.y);
	}
	if ((map->detect_collision_coords(map, new_pos.x, new_pos.y - 1) == 0) && (ghost->dir != DOWN)) {	// Distance from tile above
		up = get_distance_coords(new_pos.x, new_pos.y - 1, ghost->target_tile.x, ghost->target_tile.y);
	}
	if ((map->detect_collision_coords(map, new_pos.x, new_pos.y + 1) == 0) && (ghost->dir != UP)) {		// Distance from tile below
		down = get_distance_coords(new_pos.x, new_pos.y + 1, ghost->target_tile.x, ghost->target_tile.y);
	}

	int dist = NO_DIST;
	direction_t new_dir = SAME;
	if (up < dist) {
		new_dir = UP;
		dist = up;
	}
	if (left < dist) {
		new_dir = LEFT;
		dist = left;
	}
	if (down < dist) {
		new_dir = DOWN;
		dist = down;
	}
	if (right < dist) {
		new_dir = RIGHT;
	}
	
	ghost->future_dir = new_dir;
}

/**
 * Targeting strategy for Blinky.
 * Blinky uses Pacman's current position as a target.
 * Steps:
 * 	1. Get Pacman's current position and set it as the target tile.
 */
static void set_target_blinky(ghost_t *ghost, pacman_t *pacman) {
	ghost->target_tile = pacman->pos;
}

/**
 * Targeting strategy for Pinky.
 * Pinky uses Pacman's position and current direction as a target.
 * Steps:
 * 	1. Get Pacman's current direction and move 4 tiles in that direction.
 *	2. Get this new position and set it as Pinky's target tile.
 */
static void set_target_pinky(ghost_t *ghost, pacman_t *pacman, dimension_t *dims) {
	position_t pos;
	switch (pacman->dir) {
		case LEFT:
			pos = new_position_with_wrap(pacman->pos.x - 4, pacman->pos.y, dims);
			break;
		case RIGHT:
			pos = new_position_with_wrap(pacman->pos.x + 4, pacman->pos.y, dims);
			break;
		case UP:
			pos = new_position_with_wrap(pacman->pos.x, pacman->pos.y - 4, dims);
			break;
		case DOWN:
			pos = new_position_with_wrap(pacman->pos.x, pacman->pos.y + 4, dims);
			break;
	}
	ghost->target_tile = pos;
} 

/**
 * Targeting strategy for Inky.
 * Inky uses Pacman's current direction and tile as well as Blinky's current position to determine his target.
 * Steps:
 * 	1. Get the position two tiles in front of Pacman's current position.
 * 	2. Get the x and y distance from Blinky to that current tile.
 * 	3. Double the x and y distances to form Inky's new target tile.
 */
static void set_target_inky(ghost_t *ghost, pacman_t *pacman, ghost_t *blinky, dimension_t *dims) {
	position_t int_tile, targ_tile;
	switch (pacman->dir) {
		case LEFT:
			int_tile = new_position_with_wrap(pacman->pos.x - 2, pacman->pos.y, dims);
			break;
		case RIGHT:
			int_tile = new_position_with_wrap(pacman->pos.x + 2, pacman->pos.y, dims);
			break;
		case UP:
			int_tile = new_position_with_wrap(pacman->pos.x, pacman->pos.y - 2, dims);
			break;
		case DOWN:
			int_tile = new_position_with_wrap(pacman->pos.x, pacman->pos.y + 2, dims);
			break;
	}

	targ_tile.x = int_tile.x + (int_tile.x - blinky->pos.x);
	targ_tile.y = int_tile.y + (int_tile.y - blinky->pos.y);
	ghost->target_tile = new_position_with_wrap(targ_tile.x, targ_tile.y, dims);
} 

/**
 * Targeting strategy for Clyde.
 * Clyde's targeting stratgey relies on Pacman and the bottom left corner.
 * Steps:
 * 	1. If Clyde is within an an 8 tile euclidian distance from Pacman, he will taget the bottom left corner.
 * 	2. If Clyde is over 8 tiles away from Pacman, he will target Pacman's current position.
 */
static void set_target_clyde(ghost_t *ghost, pacman_t *pacman, dimension_t *dims) {
	int distance = get_distance_coords(ghost->pos.x, ghost->pos.y, pacman->pos.x, pacman->pos.y);
	if (distance > 64 ) {
		ghost->target_tile = pacman->pos;
	} else {
		ghost->target_tile = new_position(0, 30);
	}
} 

/**
 * Set a new target tile.
 */
void set_new_target(ghost_t *ghost, pacman_t *pacman, ghost_t *blinky, dimension_t *dims) {
	switch (ghost->name) {
		case BLINKY:
			set_target_blinky(ghost, pacman);
			break;
		case PINKY:
			set_target_pinky(ghost, pacman, dims);
			break;
		case INKY:
			set_target_inky(ghost, pacman, blinky, dims);
			break;
		case CLYDE:
			set_target_clyde(ghost, pacman, dims);
			break;
	}
}

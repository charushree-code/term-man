#include <stdlib.h>
#include "ghost.h"

/**
 * Change position based on the direction.
 */ 
static void change_position(position_t *pos, dimension_t *dims, direction_t dir) {
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
static void move(ghost_t *ghost, dimension_t *dims) {
	change_position(&ghost->pos, dims, ghost->dir);
	ghost->dir = ghost->future_dir;
}

/**
 * Move ghost to the chosen position.
 */
static void set_position(ghost_t *ghost, position_t *pos) {
	ghost->pos = *pos;
}

/**
 * Set the x-y coordinate position of the ghost.
 */
static void set_coordinates(ghost_t *ghost, int x, int y) {
	ghost->pos.x = x;
	ghost->pos.y = y;
}

/**
 * Get the position of the ghost.
 */ 
static void get_position(ghost_t *ghost, position_t *pos) {
	*pos = ghost->pos;
}

/**
 * Get the x-y coordinate position of the ghost.
 */ 
static void get_coordinates(ghost_t *ghost, int *x, int *y) {
	*x = ghost->pos.x;
	*y = ghost->pos.y;
}

/**
 * Get the next position of the ghost.
 */
static position_t get_next_position(ghost_t *ghost, dimension_t *dims) {
	position_t pos = ghost->pos;
	change_position(&pos, dims, ghost->dir);
	return pos;
}

/**
 * Set target tile. 
 */ 
static void set_target(ghost_t *ghost, int x, int y) {
	ghost->target_tile = new_position(x, y);
}

/**
 * Check if the ghost is at the target tile.
 * Returns:
 * 	0:	not at target
 * 	1:	at target tile
 */
static int at_target(ghost_t *ghost, dimension_t *dims) {
	return compare_positions(ghost->next_position(ghost, dims), ghost->target_tile);
}

/**
 * Reset the ghost.
 */
static void reset(ghost_t *ghost) {
	ghost->pos = new_position(13, 11);
	ghost->dir = SAME;
	ghost->future_dir = LEFT;
}

/**
 * Release memory held by ghost.
 */ 
static void release(ghost_t *ghost) {
	free(ghost);
}

/**
 * Reverse the direction of the ghost.
 */
void reverse(ghost_t *ghost) {	
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
static ghost_t * new_ghost() {
	ghost_t *ghost = malloc(sizeof(ghost_t));	
	
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
	
	return ghost;
}

/**
 * Create a new instance of Blinky.
 */
ghost_t * new_ghost_blinky() {
	ghost_t *blinky = new_ghost();
	blinky->name = BLINKY;
	blinky->sprite = 'B';
	blinky->colour = RED;
	return blinky;
}

/**
 * Create a new instance of Pinky.
 */
ghost_t * new_ghost_pinky() {
	ghost_t *pinky = new_ghost();
	pinky->name = PINKY;
	pinky->sprite = 'P';
	pinky->colour = PINK;
	return pinky;
}

/**
 * Create a new instance of Inky.
 */
ghost_t * new_ghost_inky() {
	ghost_t *inky = new_ghost();
	inky->name = INKY;
	inky->sprite = 'I';
	inky->colour = CYAN;
	return inky;
}

/**
 * Create a new instance of Clyde.
 */
ghost_t * new_ghost_clyde() {
	ghost_t *clyde = new_ghost();
	clyde->name = CLYDE;
	clyde->sprite = 'C';
	clyde->colour = ORANGE;
	return clyde;
}

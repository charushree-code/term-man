#include "pacman.h"
#include <stdlib.h>

/**
 * Move pacman to the chosen position.
 */
static void set_position(pacman_t *pacman, position_t *pos) {
	pacman->pos = *pos;
}

/**
 * Set the x-y coordinate position of pacman.
 */ 
static void set_coordinates(pacman_t *pacman, int x, int y) {
	pacman->pos.x = x;
	pacman->pos.y = y;
}

/**
 * Get the position of pacman.
 */ 
static void get_position(pacman_t *pacman, position_t *pos) {
	*pos = pacman->pos;
}

/**
 * Get the x-y coordinate position of pacman.
 */ 
static void get_coordinates(pacman_t *pacman, int *x, int *y) {
	*x = pacman->pos.x;
	*y = pacman->pos.y;
}

/**
 * Set Pacman's direction and change his sprite accordingly.
 */
static void set_direction(pacman_t *pacman, direction_t dir) {
	pacman->dir = dir;
	switch (dir) {
		case LEFT:
			pacman->sprite = '<';
			break;
		case RIGHT:
			pacman->sprite = '>';
			break;
		case UP:
			pacman->sprite = '^';
			break;
		case DOWN:
			pacman->sprite = 'v';
			break;
	}
}

/**
 * Increase pacmans food consumption total.
 */ 
static void eat(pacman_t *pacman) {
	pacman->food_count++;
	pacman->score += 10;
}

/**
 * Remove one of pacmans lives.
 * Returns the total lives remaining.
 */
static int lose_life(pacman_t *pacman) {
	pacman->lives--;
	return pacman->lives;
}

/**
 * Reset Pacman.
 */ 
static void reset(pacman_t *pacman) {
	pacman->pos = new_position(13, 23);
	pacman->dir = RIGHT;
	pacman->food_count = 0;
	pacman->score = 0;
}


/**
 * Release memory held by pacman.
 */ 
static void release(pacman_t *pacman) {
	free(pacman);
}

/**
 * Create a new instance of pacman.
 */ 
pacman_t * new_pacman() {
	pacman_t *pacman = malloc(sizeof(pacman_t));	
	
	pacman->lives = 3;
	pacman->colour = YELLOW;
	pacman->sprite = '>';
	reset(pacman);
	
	pacman->eat = &eat;
	pacman->lose_life = &lose_life;
	pacman->set_direction = &set_direction;
	pacman->move = &set_position;
	pacman->set_coords = &set_coordinates;
	pacman->get_pos = &get_position;
	pacman->get_coords = &get_coordinates;
	pacman->reset = &reset;
	pacman->release = &release;
	
	return pacman;
}

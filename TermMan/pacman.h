#ifndef TERMMAN_PACMAN
#define TERMMAN_PACMAN

#include "std_objects.h"

/**
 * Pacman himself
 */
typedef struct pacman_t {
	direction_t dir;
	position_t pos;
	unsigned char sprite;
	colour_t colour;
	int food_count;
	int lives;
	int score;
	
	void (*eat)(struct pacman_t *self);
	void (*set_direction)(struct pacman_t *self, direction_t dir);
	int (*lose_life)(struct pacman_t *self);
	
	void (*move)(struct pacman_t *self, position_t *pos);
	void (*set_coords)(struct pacman_t *self, int x, int y);
	
	void (*get_pos)(struct pacman_t *self, position_t *pos);
	void (*get_coords)(struct pacman_t *self, int *x, int *y);
	
	void (*reset)(struct pacman_t *self);
	void (*release)(struct pacman_t *self);
} pacman_t;

/**
 * Create a new instance of ghost
 */
pacman_t * new_pacman();

#endif

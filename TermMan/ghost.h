#ifndef TERMMAN_GHOST
#define TERMMAN_GHOST

#include "std_objects.h"

typedef enum {CHASE, SCATTER, FRIGHTENED} ghost_mode_t;
typedef enum {BLINKY, PINKY, INKY, CLYDE} ghost_name_t;

/**
 * The ghost character in pacman.
 */
typedef struct ghost_t {
	position_t pos;
	position_t target_tile;
	direction_t dir;
	direction_t future_dir;
	
	ghost_name_t name;
	unsigned char sprite;
	colour_t colour;
	ghost_mode_t mode;

	void (*move_tile)(struct ghost_t *self, dimension_t *dims);
	void (*target)(struct ghost_t *self, int x, int y);
	int (*at_target)(struct ghost_t *self, dimension_t *dims);
	position_t (*next_position)(struct ghost_t *self, dimension_t *dims);

	void (*set_pos)(struct ghost_t *self, position_t *pos);
	void (*set_coords)(struct ghost_t *self, int x, int y);
	
	void (*get_pos)(struct ghost_t *self, position_t *pos);
	void (*get_coords)(struct ghost_t *self, int *x, int *y);
	
	void (*reset)(struct ghost_t *self);
	void (*reverse)(struct ghost_t *self);
	void (*release)(struct ghost_t *self);
} ghost_t;

ghost_t * new_ghost_blinky();
ghost_t * new_ghost_pinky();
ghost_t * new_ghost_inky();
ghost_t * new_ghost_clyde();

#endif

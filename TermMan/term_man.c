#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "std_objects.h"
#include "ghost.h"
#include "pacman.h"
#include "map.h"
#include "ghost_ai.h"

// Function Prototypes
void draw(unsigned char input);
void draw_pacman(unsigned char input);
void draw_ghost(ghost_t *_ghost);
void draw_map();
void check_collision();
void check_food_count();
void reset();

// Global Objects
map_t *map;
ghost_t *blinky;
ghost_t *pinky;
ghost_t *inky;
ghost_t *clyde;
pacman_t *pacman;

int main() {
	int width, height;
	unsigned char input;

	map = new_map();
	map->get_map_level(map);

	pacman = new_pacman();

	blinky = new_ghost_blinky();
	pinky = new_ghost_pinky();
	inky = new_ghost_inky();
	clyde = new_ghost_clyde();
	set_new_target(blinky, pacman, blinky, &map->dims);
	set_new_target(pinky, pacman, blinky, &map->dims);
	set_new_target(inky, pacman, blinky, &map->dims);
	set_new_target(clyde, pacman, blinky, &map->dims);

	WINDOW *window;

	window = initscr();			// Initialise the window
	cbreak();				// Don't wait for enter key
	noecho();				// Don't echo the input
	getmaxyx(window, height, width);	// Get window size
	clear();
	refresh();

	draw_map();	// Draw the map
	draw(' ');

	for (;;) {
		input = getch();
		if (input == 'q') {		// Quit
			break;
		} else if (input == 'r') {	// Restart
			reset();
		} else {
			draw(input);
		}
	}

	endwin();	// Restore original window

	pacman->release(pacman);
	blinky->release(blinky);
	pinky->release(pinky);
	inky->release(inky);
	clyde->release(clyde);
	map->release(map);

	return 0;
}

/**
 * Reset the map.
 */
void reset() {
	map->get_map_level(map);
	draw_map();

	blinky->reset(blinky);
	pinky->reset(pinky);
	inky->reset(inky);
	clyde->reset(clyde);
	pacman->reset(pacman);

	draw(' ');
}

/**
 * Hanlde the drawing of pacman and the ghosts.
 */
void draw(unsigned char input) {
	draw_ghost(blinky);
	draw_ghost(pinky);
	draw_ghost(inky);
	draw_ghost(clyde);
	check_collision();

	draw_pacman(input);
	check_collision();
	check_food_count();
}

/**
 * Draw the map to the screen
 */
void draw_map() {
	unsigned char i, j;

	clear();
	position_t pos;

	for (i = 0; i < map->dims.height; i++) {
		for (j = 0; j < map->dims.width; j++) {
			pos = new_position(j, i);
			move(i, j);
			delch();
			insch(map->draw_terrain(map->get_object(map, &pos)));
		}
	}

	refresh();
}

/**
 * Draw the graphics to the screen.
 */
void draw_pacman(unsigned char input) {
	move(pacman->pos.y, pacman->pos.x);	// Move currect position of pacman
	delch();							// Delete pacman
	insch(map->draw_terrain(map->get_object(map, &pacman->pos)));	// Redraw terrain at selected point

	pacman->set_direction(pacman, get_direction_from_input(input));	// Get direction from input
	position_t new_pos = get_position_from_direction(pacman->pos, map->dims, pacman->dir);	// Get new position
	map->detect_pacman_collision(map, pacman, &new_pos);			// Handle movement of pacman

	move(pacman->pos.y, pacman->pos.x);	// Move pacman to new position
	delch();
	insch(pacman->sprite);			// Draw pacman

	refresh();
}

/**
 * Draw the given ghost to the screen.
 */
void draw_ghost(ghost_t *_ghost) {
	move(_ghost->pos.y, _ghost->pos.x);	// Move currect position of ghost
	delch();							// Delete the ghost
	insch(map->draw_terrain(map->get_object(map, &_ghost->pos)));	// Redraw terrain at selected point

	_ghost->move_tile(_ghost, &map->dims);

	// Check if next ghost position is at the intersection and set new target if true.
	position_t new_pos = _ghost->next_position(_ghost, &map->dims);
	if (map->intersection(map, &new_pos)) {
		set_new_target(_ghost, pacman, blinky, &map->dims);
		set_path(_ghost, map);
	}

	move(_ghost->pos.y, _ghost->pos.x);	// Move ghost to new position
	delch();
	insch(_ghost->sprite);			// Draw ghost

	refresh();
}

/**
 * Check for a collision between Pacman and the ghosts
 */
void check_collision() {
	if (compare_positions(pacman->pos, blinky->pos) || compare_positions(pacman->pos, pinky->pos) ||
		compare_positions(pacman->pos, inky->pos) || compare_positions(pacman->pos, clyde->pos)) {
		if (pacman->lose_life(pacman)) {
			reset();
		} else {
			pacman->lives = 3;
		}
		reset();
	}
}

void check_food_count() {
	if (pacman->food_count > MAX_FOOD) {
		reset();
	}
}

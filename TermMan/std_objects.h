#ifndef TERMMAN_STD_OBJECTS_H
#define TERMMAN_STD_OBJECTS_H

#define MAX_X 		28
#define MAX_Y		31
#define MAX_FOOD	243

typedef enum { YES, NO } bool_t;
typedef enum { UP, DOWN, LEFT, RIGHT, SAME } direction_t;
typedef enum { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, CENTER } bearing_t;
typedef enum { WHITE, BLACK, RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE, GRAY, PINK, CYAN } colour_t;
typedef enum { WALL, PATH, FOOD, FREE, GATE } terrain_t;

/**
 * Holds the x and y values within a coordinate system.
 * x:	x coordinate
 * y:	y coordinate
 */
typedef struct {
	int x;
	int y;
} position_t;

/**
 * Holds the height and width dimension values.
 * width:	width
 * height:	height
 */
typedef struct {
	int width;
	int height;
} dimension_t;

int get_distance_pos(position_t *pos, position_t *target_pos);
int get_distance_coords(int x1, int y1, int x2, int y2);
int get_distance(int p1, int p2);

int compare_positions(position_t pos1, position_t pos2);

position_t new_position(int x, int y);
position_t new_position_with_wrap(int x, int y, dimension_t *dims);
position_t get_position_from_direction(position_t pos, dimension_t dims, direction_t dir);

direction_t get_direction_from_input(unsigned char input);

#endif

#ifndef TERMMAN_STD_OBJECTS_H
#define TERMMAN_STD_OBJECTS_H

#define MAX_X       28
#define MAX_Y       31
#define MAX_FOOD    243

/*
 * Used for creating and destroying objects.
 * There must be a 1:1 alloc and dealloc call on an object.
 */
#define alloc(object)       malloc(sizeof(object))
#define dealloc(object)     free(object)

typedef enum { YES, NO } bool_t;
typedef enum { UP, DOWN, LEFT, RIGHT, SAME } Direction;
typedef enum { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, CENTER } Bearing;
typedef enum { WHITE, BLACK, RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE, GRAY, PINK, CYAN } Colour;
typedef enum { WALL, PATH, FOOD, FREE, GATE } Terrain;

/*
 * Holds the x and y values within a coordinate system.
 * x:   x coordinate
 * y:   y coordinate
 */
typedef struct {
    int x;
    int y;
} Position;

/*
 * Holds the height and width dimension values.
 * width:   width
 * height:  height
 */
typedef struct {
    int width;
    int height;
} Dimension;

int get_distance_pos(Position *pos, Position *target_pos);
int get_distance_coords(int x1, int y1, int x2, int y2);
int get_distance(int p1, int p2);

int compare_positions(Position pos1, Position pos2);

Position new_position(int x, int y);
Position new_position_with_wrap(int x, int y, Dimension *dims);
Position get_position_from_direction(Position pos, Dimension dims, Direction dir);

Direction get_direction_from_input(unsigned char input);

#endif

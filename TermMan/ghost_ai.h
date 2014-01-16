#ifndef TERMMAN_GHOST_AI_H
#define TERMMAN_GHOST_AI_H

#include "std_objects.h"
#include "ghost.h"
#include "map.h"

void set_path(ghost_t *ghost, map_t *map);
void set_new_target(ghost_t *ghost, pacman_t *pacman, ghost_t *blinky, dimension_t *dims);

#endif

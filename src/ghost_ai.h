#ifndef TERMMAN_GHOST_AI_H
#define TERMMAN_GHOST_AI_H

#include "std_objects.h"
#include "ghost.h"
#include "map.h"

void set_path(Ghost *ghost, Map *map);
void set_new_target(Ghost *ghost, Pacman *pacman, Ghost *blinky, Dimension *dims);

#endif

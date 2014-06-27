#include "pacman.h"
#include <stdlib.h>

// Private variables
static struct private_t {
    Position pos;
    Direction dir;
    int lives;
    int score;
    unsigned char sprite;
} private_t;

/*
 * Update pacmans sprite based on his current direction.
 */
static void update_sprite(Pacman *pacman)
{
    if (pacman->private->dir == LEFT){
        pacman->private->sprite = '<';
    }
    else if (pacman->private->dir == RIGHT) {
        pacman->private->sprite = '>';
    }
    else if (pacman->private->dir == UP) {
        pacman->private->sprite = '^';
    }
    else if (pacman->private->dir == DOWN) {
        pacman->private->sprite = 'v';
    }
}

/*
 * Move pacman to the chosen position.
 */
static void set_position(Pacman *pacman, Position pos)
{
    pacman->private->pos = pos;
}

/*
 * Get the position of pacman.
 */
static Position position(Pacman *pacman)
{
    return pacman->private->pos;
}

/*
 * Set Pacman's direction and change his sprite accordingly.
 */
static void set_direction(Pacman *pacman, Direction dir)
{
    pacman->private->dir = dir;

    update_sprite(pacman);
}

/*
 * Get the direction of pacman.
 */
static Direction direction(Pacman *pacman)
{
    return pacman->private->dir;
}

/*
 * Get pacman's sprite.
 */
static unsigned char sprite(Pacman *pacman)
{
    return pacman->private->sprite;
}

/*
 * Increase pacmans food consumption total.
 */
static void eat(Pacman *pacman)
{
    pacman->private->score += 10;
}

/*
 * Get the current score.
 */
static int score(Pacman *pacman)
{
    return pacman->private->score;
}

/*
 * Remove one of pacmans lives.
 * Returns the total lives remaining.
 */
static int lose_life(Pacman *pacman)
{
    return (pacman->private->lives -= 1);
}

/*
 * Returns the total lives remaining.
 */
static int lives(Pacman *pacman)
{
    return pacman->private->lives;
}

/*
 * Reset Pacman to his default position.
 */
static void reset(Pacman *pacman)
{
    pacman->set_position(pacman, new_position(13, 23));
    pacman->set_direction(pacman, RIGHT);
    pacman->private->score = 0;
}

/*
 * Release memory held by pacman.
 */
static void release(Pacman *pacman)
{
    free(pacman->private);
}

/*
 * Create a new instance of pacman.
 */
Pacman * new_pacman(Pacman *self)
{
    if (self) {
        self->sprite = &sprite;
        self->eat = &eat;
        self->score = &score;

        self->lose_life = &lose_life;
        self->lives = &lives;

        self->set_direction = &set_direction;
        self->direction = &direction;

        self->set_position = &set_position;
        self->position = &position;

        self->reset = &reset;
        self->release = &release;

        self->private = malloc(sizeof(private_t));

        self->private->lives = 3;
        self->reset(self);
    }

    return self;
}

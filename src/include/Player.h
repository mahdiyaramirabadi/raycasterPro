#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef struct
{
    Vector2 pos;
    Vector2 map_pos;
    Vector2 dir;
    Vector2 plane;
}Player;

#endif
#include "knight.h"
#include "ije02_game.h"

#define MAX_LIFE 300
Knight::Knight(vector<string> sprite_paths, unsigned id, double x, double y)
    : Character(sprite_paths, id, x, y, MAX_LIFE)
{
}

void
Knight::heavy_attack()
{

}
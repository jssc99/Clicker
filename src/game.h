#pragma once

#define WIDTH 80
#define HEIGTH 40

typedef struct Check
{
    _Bool hasOneCandy;
    int hasOneCandyCounter;
    _Bool hasTenCandy;
    int hasTenCandyCounter;
} Check;

typedef struct Game
{
    Check check;

    int value;
    int candy;
    float frames;
} Game;

void game_init(Game* game);
void game_update(Game* game);
void game_shutdown(Game* game);

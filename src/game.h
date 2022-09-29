#pragma once

#define WIDTH 80
#define HEIGTH 70

typedef struct Check
{
    _Bool DARK_MODE;
    _Bool EXIT;
    _Bool hasOneCandy;
    _Bool hasTenCandy;
    _Bool hasThirtyCandy;
    _Bool firstFeature;
    _Bool secondFeature;
    _Bool thirdFeature;
} Check;

typedef enum Menu
{
    ON_CANDY_BOX,
    ON_DEBUG_MENU,
    ON_OTHER
} Menu;

typedef struct Game
{
    Check check;
    Menu menu;
    unsigned long int candy;
    float frames;
    int hasOneCandyCounter;
    int hasTenCandyCounter;
} Game;

void game_init(Game* game);
void game_update(Game* game);
void game_shutdown(Game* game);

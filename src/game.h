#pragma once

#include <stdbool.h>

#define WIDTH 80
#define HEIGTH 65

typedef struct Check
{
    bool DARK_MODE;
    bool EXIT_GAME;
    bool hasOneCandy;
    bool hasTenCandy;
    bool hasThirtyCandy;
    bool foundCandyBoxLolly;
    bool foundForgeLolly;
    bool foundMerchantLolly;
} Check;

typedef enum Menu
{
    ON_CANDY_BOX,
    ON_DEBUG_MENU,
    ON_SAVE_MENU,
    ON_FORGE,
    ON_MERCHANT,
    ON_OTHER
} Menu;

typedef struct Game
{
    Check check;
    Menu menu;
    float frames;
    unsigned long int candy;
    unsigned long int lollypop;
    int featuresUnlocked;
    int hasOneCandyCounter;
    int hasTenCandyCounter;
    int forgeDialog;
} Game;

void game_init(Game *game);
void game_update(Game *game);
void game_shutdown(Game *game);
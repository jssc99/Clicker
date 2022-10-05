#pragma once

#include <stdbool.h>

#define WIDTH 80
#define HEIGTH 65

#define CANDYBOX 1
#define DEBUGMENU 2
#define SAVEMENU 3
#define FORGE 4
#define MERCHANT 5

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
    ON_MERCHANT
} Menu;

typedef struct Counter
{
    float frames;
    float freq;
    float timer;
    unsigned long int amount;
} Counter;

typedef struct Game
{
    Check check;
    Menu menu;

    Counter candy;
    int candyEaten;
    int candyThrown;
    unsigned long int lollypop;

    int featuresUnlocked;
    int forgeDialog;
} Game;

void game_init(Game *game);
void game_update(Game *game);
void game_shutdown(Game *game);
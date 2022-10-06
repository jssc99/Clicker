#pragma once

#include "gui.h"

#define WIDTH 105
#define HEIGTH 65

#define NONE 0
#define CANDYBOX 1
#define DEBUGMENU 2
#define SAVEMENU 3
#define MAP 4
#define FORGE 5
#define MERCHANT 6

typedef struct Check
{
    bool hasOneCandy;
    bool hasTenCandy;
    bool hasThirtyCandy;

    bool foundCandyBoxLolly;
    bool foundSaveLolly;
    bool foundMapLolly;
    bool foundForgeLolly;
    bool foundMerchantLolly;
} Check;

typedef enum Menu
{
    ON_CANDY_BOX,
    ON_DEBUG_MENU,
    ON_SAVE_MENU,
    ON_MAP,
    ON_FORGE,
    ON_MERCHANT
} Menu;

typedef struct Counter
{
    float freq;
    float frames;
    float timer;
    unsigned long int amount;
} Counter;

typedef struct Game
{
    Check check;
    bool DARK_MODE;
    bool EXIT_GAME;

    Counter candy;
    int candyEaten;
    int candyThrown;
    
    Counter lollypop;
    
    Menu menu;
    int featuresUnlocked;
    int forgeDialog;
} Game;

void game_init(Game *game);
void game_update(Game *game);
void game_shutdown(Game *game);

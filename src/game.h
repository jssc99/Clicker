#pragma once

#define WIDTH 80
#define HEIGTH 70

typedef struct Check
{
    _Bool DARK_MODE;
    _Bool EXIT_GAME;
    _Bool hasOneCandy;
    _Bool hasTenCandy;
    _Bool hasThirtyCandy;
} Check;

typedef enum Menu
{
    ON_CANDY_BOX,
    ON_DEBUG_MENU,
    ON_SAVE_MENU,
    ON_MERCHANT,
    ON_OTHER
} Menu;

typedef struct Game
{
    Check check;
    Menu menu;
    unsigned long int candy;
    unsigned long int lollypop;
    float frames;
    int featuresUnlocked;
    int hasOneCandyCounter;
    int hasTenCandyCounter;
} Game;

void game_init(Game *game);
void game_update(Game *game);
void game_shutdown(Game *game);

void header_button_candybox(Game *game);
void header_button_merchant(Game *game);
void header_button_savemenu(Game *game);
void header_button_debugmenu(Game *game);
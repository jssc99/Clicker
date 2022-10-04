#pragma once

#define WIDTH 80
#define HEIGTH 65

typedef struct Check
{
    _Bool DARK_MODE;
    _Bool EXIT_GAME;
    _Bool hasOneCandy;
    _Bool hasTenCandy;
    _Bool hasThirtyCandy;
    _Bool foundCandyBoxLolly;
    _Bool foundForgeLolly;
    _Bool foundMerchantLolly;
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

void draw_header(Game *game);
void draw_candybox(Game *game);
void draw_savemenu(Game *game);
void draw_debugmenu(Game *game);
void draw_forge(Game *game);
void draw_merchant(Game *game);

void header_button_candybox(Game *game);
void header_button_forge(Game *game);
void header_button_savemenu(Game *game);
void header_button_debugmenu(Game *game);
void header_button_merchant(Game *game);

void game_save(Game *game, const char *filename);
void game_load(Game *game, const char *filename);

const char *getThrowAnim(int counter);
#include "game.h"
#include "gui.h"

void draw_savemenu(Game *game);

void game_save(Game *game, const char *filename);
void game_load(Game *game, const char *filename);
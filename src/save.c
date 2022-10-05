#include "save.h"

void game_save(Game *game, const char *filename)
{
    FILE *save = fopen(filename, "w");
    if (save == NULL)
    {
        printf("error saving game\n");
        return;
    }
    fwrite(game, sizeof(Game), 1, save);
    fclose(save);
}

void game_load(Game *game, const char *filename)
{
    FILE *save = fopen(filename, "r");
    if (save == NULL)
    {
        printf("error loading save\n");
        return;
    }
    fread(game, sizeof(Game), 1, save);
    fclose(save);
}

void draw_savemenu(Game *game)
{
    if (im_button(1, 6, "Save binary"))
        game_save(game, "save.bin");
    if (im_button(1, 8, "Load binary"))
        game_load(game, "save.bin");
    change_bg_fg(game->check.DARK_MODE);

    if (im_button(1, HEIGTH - 4, "EXIT GAME"))
        game->check.EXIT_GAME = true;
}
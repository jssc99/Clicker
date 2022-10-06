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
    if (im_button(get_center("Save game"), 6, "Save game"))
        game_save(game, "save.bin");
    if (im_button(get_center("Load gamesave"), 9, "Load gamesave"))
        game_load(game, "save.bin");
    change_bg_fg(game->DARK_MODE);

    // "Secret" Lollypop

    if (game->check.foundSaveLolly == false)
    {
        if (im_button_quiet(69, 56, "--O"))
        {
            game->lollypop.amount++;
            game->check.foundSaveLolly = true;
        }
    }
    else
        im_print_text(get_center("You found the not so secret lollypop!"), 16, "You found the not so secret lollypop!");

    if (im_button(get_center("EXIT GAME"), HEIGTH - 4, "EXIT GAME"))
        game->EXIT_GAME = true;
}
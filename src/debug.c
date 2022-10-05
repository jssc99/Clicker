#include "debug.h"

void draw_debugmenu(Game *game)
{
    if (im_button(32, 6, "O"))
    {
        game->check.DARK_MODE = !game->check.DARK_MODE;
        change_bg_fg(game->check.DARK_MODE);
    }
    im_print(34, 6, "DARK O%s", (game->check.DARK_MODE) ? "N" : "FF");

    if (im_button(32, 8, "O"))
        game->check.DEBUG_MODE = !game->check.DEBUG_MODE;
    im_print(34, 8, "DEBUG MODE O%s", (game->check.DEBUG_MODE) ? "N" : "FF");

    if (im_button(1, 6, "Reset candies"))
        game->candy.number = 0;
    if (im_button(1, 8, "Reset candies eaten"))
        game->hasOneCandyCounter = 0;
    if (im_button(1, 10, "Reset candies thrown"))
        game->hasTenCandyCounter = 0;

    if (im_button(1, 13, "Reset lollypops"))
        game->lollypop = 0;
        
    if (im_button(1, 15, "Reset forge dialog"))
        game->forgeDialog = 0;

    if (im_button(1, 17, "Reset secret lollypops"))
    {
        game->check.foundCandyBoxLolly = false;
        game->check.foundForgeLolly = false;
        game->check.foundMerchantLolly = false;
    }
}
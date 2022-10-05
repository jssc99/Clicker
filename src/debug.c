#include "debug.h"

void draw_debugmenu(Game *game)
{
    if (im_button(WIDTH / 2, 6, "O"))
    {
        game->check.DARK_MODE = !game->check.DARK_MODE;
        change_bg_fg(game->check.DARK_MODE);
    }
    im_print((WIDTH / 2) + 2, 6, "DARK O%s", (game->check.DARK_MODE) ? "N" : "FF");

    if (im_button(1, 6, "Reset candies"))
        game->candy.amount = 0;
    if (im_button(1, 8, "Reset candies eaten"))
        game->candyEaten = 0;
    if (im_button(1, 10, "Reset candies thrown"))
        game->candyThrown = 0;
    if (im_button(1, 12, "Increase candy freq (+1 / sec)"))
        game->candy.freq += 1;
    if (im_button(1, 14, "Increase candy freq (+10 / sec)"))
        game->candy.freq += 10;

    if (im_button(1, 19, "Reset lollypops"))
        game->lollypop = 0;

    if (im_button(1, 21, "Reset forge dialog"))
        game->forgeDialog = 0;

    if (im_button(1, 23, "Reset secret lollypops"))
    {
        game->check.foundCandyBoxLolly = false;
        game->check.foundForgeLolly = false;
        game->check.foundMerchantLolly = false;
    }
}
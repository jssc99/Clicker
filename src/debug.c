#include "debug.h"

void draw_debugmenu(Game *game)
{
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
    if (im_button(1, 16, "Decrease candy freq (-1 / sec)"))
        game->candy.freq -= 1;
    if (im_button(1, 18, "Decrease candy freq (-10 / sec)"))
        game->candy.freq -= 10;
    im_print(1, 20, "FREQ CANDY : %0.2f / SEC", game->candy.freq);

    if (im_button(WIDTH / 2, 6, "#"))
    {
        game->DARK_MODE = !game->DARK_MODE;
        change_bg_fg(game->DARK_MODE);
    }
    im_print((WIDTH / 2) + 2, 6, "DARK O%s", (game->DARK_MODE) ? "N" : "FF");

    if (im_button(WIDTH / 2, 8, "Reset lollypops"))
        game->lollypop.amount = 0;

    if (im_button(WIDTH / 2, 10, "Reset forge dialog"))
        game->forgeDialog = 0;

    if (im_button(WIDTH / 2, 12, "Reset secret lollypops (5 total)"))
    {
        game->check.foundCandyBoxLolly = false;
        game->check.foundSaveLolly = false;
        game->check.foundMapLolly = false;
        game->check.foundForgeLolly = false;
        game->check.foundMerchantLolly = false;
    }
}
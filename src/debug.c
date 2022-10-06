#include "debug.h"

void draw_debugmenu(Game *game)
{
    if (im_button(1, 6, "Get 1000 candies"))
        game->candy.amount += 1000;
    if (im_button(1, 8, "Reset candies"))
        game->candy.amount = 0;
    if (im_button(1, 10, "Reset candies eaten"))
        game->candyEaten = 0;
    if (im_button(1, 12, "Reset candies thrown"))
        game->candyThrown = 0;

    if (im_button(1, 14, "Increase candy freq (+1 / sec)"))
        game->candy.freq += 1;
    if (im_button(1, 16, "Increase candy freq (+10 / sec)"))
        game->candy.freq += 10;
    if (im_button(1, 18, "Set candy freq to 0"))
        game->candy.freq = 0;
    if (im_button(1, 20, "Decrease candy freq (-1 / sec)"))
        game->candy.freq -= 1;
    if (im_button(1, 22, "Decrease candy freq (-10 / sec)"))
        game->candy.freq -= 10;
    im_print(1, 24, "FREQ CANDY : %0.2f / SEC", game->candy.freq);

    // Other side

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
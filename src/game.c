#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>
#include "game.h"
#include "header.h"
#include "candybox.h"
#include "forge.h"
#include "merchant.h"
#include "save.h"
#include "debug.h"
#include "map.h"

void game_init(Game *game)
{
    //game->candy.amount = 1000; // GET RICH QUICK WITH THIS ONE EASY TRICK
    game->menu = ON_CANDY_BOX;
    game->candy.freq = 1.0;
}

void counter_update(Counter *counter)
{
    if (counter->freq > 0.0 && counter->amount != 4294967295) // positif freq
    {
        counter->timer = 1.0 / counter->freq;
        counter->frames += pg_io_get_frame_time();
        while (counter->frames >= counter->timer && counter->amount != 4294967295)
        {
            counter->amount++;
            counter->frames -= counter->timer;
        }
    }
    else if (counter->freq < 0.0 && counter->amount != 0) // negatif freq
    {
        counter->timer = 1.0 / (-1 * counter->freq);
        counter->frames += pg_io_get_frame_time();
        while (counter->frames >= counter->timer && counter->amount != 0)
        {
            counter->amount--;
            counter->frames -= counter->timer;
        }
    }
}

void game_update(Game *game)
{
    counter_update(&game->candy);
    // counter_update(&game->lollypop); // not used

    im_print(1, 1, "%s %lu cand%s", (game->candy.amount >= 10000000000) ? "->" : "You've got",
             game->candy.amount, (game->candy.amount <= 1) ? "y" : "ies");
    if (game->lollypop.amount)
        im_print(1, 2, "%s %lu lollypop%s", (game->lollypop.amount >= 10000000000) ? "->" : "You've got",
                 game->lollypop.amount, (game->lollypop.amount == 1) ? "" : "s");

    // GAME HEADER

    if (game->featuresUnlocked)
        draw_header(&game->menu, game->featuresUnlocked);

    // GAME BODY

    switch (game->menu)
    {
    case ON_CANDY_BOX:
        draw_candybox(game);
        break;

    case ON_DEBUG_MENU:
        draw_debugmenu(game);
        break;

    case ON_SAVE_MENU:
        draw_savemenu(game);
        break;

    case ON_MAP:
        draw_map(game);
        break;

    case ON_FORGE:
        draw_forge(game);
        break;

    case ON_MERCHANT:
        draw_merchant(game);
        break;

    default:
        printf("error menu\n");
        break;
    }
}

void game_shutdown(Game *game)
{
    // rm *
}

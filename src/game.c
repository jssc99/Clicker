#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>

#include "game.h"
#include "gui.h"
#include "header.h"
#include "candybox.h"
#include "forge.h"
#include "merchant.h"
#include "save.h"
#include "debug.h"

void game_init(Game *game)
{
    game->candy.amount = 35;
    game->menu = ON_CANDY_BOX;
    game->candy.freq = 2;
}

void candy_counter(Counter *counter)
{
    counter->timer = 1.0 / counter->freq;
    if ((counter->frames += pg_io_get_frame_time()) >= counter->timer)
    {
        counter->amount++;
        counter->frames -= counter->timer;
    }
}

void game_update(Game *game)
{
    candy_counter(&game->candy);

    // CANDY & LOLLYPOP DISPLAY

    im_print(1, 1, "%s %lu cand%s", (game->candy.amount >= 10000000000) ? "->" : "You've got",
             game->candy.amount, (game->candy.amount <= 1) ? "y" : "ies");

    if (game->lollypop)
        im_print(1, 2, "You've got %lu lollypop%s", game->lollypop, (game->lollypop == 1) ? "" : "s");

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

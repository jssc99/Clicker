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
    game->check.DEBUG_MODE = true;
    game->menu = ON_CANDY_BOX;
    game->candy.freq = 2;
}

void game_update(Game *game)
{
    // CANDY COUNTER

    game->candy.timer = 1.0 / game->candy.freq;
    if ((game->candy.frames += pg_io_get_frame_time()) >= game->candy.timer)
    {
        if (game->check.DEBUG_MODE)
            game->candy.number += 1000;
        else
            game->candy.number++;
        game->candy.frames -= game->candy.timer;
    }

    // GAME HEADER

    im_print(1, 1, "%s %lu cand%s", (game->candy.number >= 10000000000) ? "->" : "You've got",
             game->candy.number, (game->candy.number <= 1) ? "y" : "ies");

    if (game->lollypop)
        im_print(1, 2, "You've got %lu lollypop%s", game->lollypop, (game->lollypop == 1) ? "" : "s");

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

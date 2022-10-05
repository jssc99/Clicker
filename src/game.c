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
    game->menu = ON_CANDY_BOX;
}

void game_update(Game *game)
{
    if ((game->frames += pg_io_get_frame_time()) > 1)
    {
        game->candy++;
        // game->frames--; // fast candy if disabled
    }

    // GAME HEADER

    im_print(1, 1, "You've got %lu cand%s", game->candy, (game->candy <= 1) ? "y" : "ies");
    if (game->lollypop)
        im_print(1, 2, "You've got %lu lollypop%s", game->lollypop, (game->lollypop == 1) ? "" : "s");

    if (game->featuresUnlocked)
        draw_header(game);

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

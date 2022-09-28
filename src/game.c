#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>

#include "game.h"
#include "gui.h"

void game_init(Game *game)
{
    game->value = 0;
    game->candy = 0;
    game->frames = 0;
    game->check.hasOneCandy = false;
    game->check.hasOneCandyCounter = 0;
    game->check.hasTenCandy = false;
    game->check.hasTenCandyCounter = 0;
}

const char* getThrowAnim(int counter)
{
    if (counter > 1 && counter < 2) return "...";
    else if (counter == 3)          return "... :'(";
    else if (counter == 4)          return "...  :'(";
    else if (counter == 5)          return "...   :'(";
    else return "";
    //      (game->check.hasTenCandyCounter > 1 && game->check.hasTenCandyCounter < 6) ? "..." : "",
    //                 (game->check.hasTenCandyCounter > 2 && game->check.hasTenCandyCounter < 6) ? "?" : "",
    //                 (game->check.hasTenCandyCounter == 3) ? " :'(" : "",
    //                 (game->check.hasTenCandyCounter == 4) ? " :(" : "",
    //                 (game->check.hasTenCandyCounter == 5) ? " (;_;)" : "",
    //                 (game->check.hasTenCandyCounter == 6) ? ". Please stop." : "",
    //                 (game->check.hasTenCandyCounter == 7) ? ". :/" : "",
    //                 (game->check.hasTenCandyCounter == 8) ? ". >:/" : "",
    //                 (game->check.hasTenCandyCounter == 9) ? ". >:(" : "",
    //                 (game->check.hasTenCandyCounter >= 10) ? ". Fuck You." : "");
}

void game_update(Game *game)
{
    if ((game->frames += pg_io_get_frame_time()) > 1)
    {
        game->candy++;
        // game->frames--;
    }
    im_print_text(0, 0, "+------------------------------------------------------------------------------+");
    im_print_text(0, 1, "|");
    im_print(get_center("Candy count : %d"), 1, "Candy count : %d", game->candy);
    im_print_text(WIDTH - 1, 1, "|");
    im_print_text(0, 2, "+------------------------------------------------------------------------------+");

    if (game->candy > 0)
        game->check.hasOneCandy = true;

    if (game->check.hasOneCandy)
    {
        if (im_button(1, 4, "Eat all the candies"))
        {
            game->check.hasOneCandyCounter += game->candy;
            game->candy = 0;
        }
        if (game->check.hasOneCandyCounter)
            im_print(1, 5, "You have eaten %d %s", game->check.hasOneCandyCounter, (game->check.hasOneCandyCounter == 1) ? "candy" : "candies");
    }

    if (game->candy > 10)
        game->check.hasTenCandy = true;

    if (game->check.hasTenCandy)
    {
        if (im_button(1, 7, "Throw 10 candies to the ground") && game->candy >= 10)
        {
            game->check.hasTenCandyCounter += 1;
            game->candy -= 10;
        }
        if (game->check.hasTenCandyCounter)
            //im_print(1, 8, "You threw %d candies on the ground%s%s%s%s%s%s%s%s%s%s", game->check.hasTenCandyCounter * 10,
            //         (game->check.hasTenCandyCounter > 1 && game->check.hasTenCandyCounter < 6) ? "..." : "",
            //         (game->check.hasTenCandyCounter > 2 && game->check.hasTenCandyCounter < 6) ? "?" : "",
            //         (game->check.hasTenCandyCounter == 3) ? " :'(" : "",
            //         (game->check.hasTenCandyCounter == 4) ? " :(" : "",
            //         (game->check.hasTenCandyCounter == 5) ? " (;_;)" : "",
            //         (game->check.hasTenCandyCounter == 6) ? ". Please stop." : "",
            //         (game->check.hasTenCandyCounter == 7) ? ". :/" : "",
            //         (game->check.hasTenCandyCounter == 8) ? ". >:/" : "",
            //         (game->check.hasTenCandyCounter == 9) ? ". >:(" : "",
            //         (game->check.hasTenCandyCounter >= 10) ? ". Fuck You." : "");
            im_print(1, 8, "You threw %d candies on the ground%s", 
                game->check.hasTenCandyCounter * 10,
                getThrowAnim(game->check.hasTenCandyCounter));
    }
}

void game_shutdown(Game *game)
{
}

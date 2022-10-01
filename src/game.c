#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>

#include "game.h"
#include "gui.h"

void game_init(Game *game)
{
    game->menu = ON_CANDY_BOX;
}

const char *getThrowAnim(int counter)
{
    if (counter == 2)
        return "...";
    else if (counter == 3)
        return "...?";
    else if (counter == 4)
        return "...? :(";
    else if (counter == 5)
        return "...? :'(";
    else if (counter == 6)
        return "...? (;_;)";
    else if (counter == 7)
        return ". Please stop.";
    else if (counter == 8)
        return ". :/";
    else if (counter == 9)
        return ". >:/";
    else if (counter == 10)
        return ". >:(";
    else if (counter >= 11)
        return ". Fuck You.";
    else
        return "";
}

void game_update(Game *game)
{

    //////////////////////
    // GAME HEADER HERE //
    //////////////////////

    if ((game->frames += pg_io_get_frame_time()) > 1)
    {
        game->candy++;
        // game->frames--; // fast candy if disabled
    }
    im_print(1, 1, "You've got %lu cand%s", game->candy, (game->candy <= 1) ? "y" : "ies");
    if (game->check.hasUnlockedLollypop)
        im_print(1, 1, "You've got %lu lollypop%s", game->lollypop, (game->lollypop == 1) ? "" : "s");

    if (game->featuresUnlocked)
    {
        im_print_text(0, 0, "+------------------------------------------------------------------------------+");
        im_print_text(0, 4, "+------------------------------------------------------------------------------+");
        for (int i = 1; i < 4; i++)
        {
            im_print_text(0, i, "|");
            im_print_text(30, i, "|");
            im_print_text(36, i, "|");
            im_print_text(WIDTH - 1, i, "|");
            if (game->featuresUnlocked)
                im_print_text(WIDTH - 3, i, "|");
        }
        if (game->menu == ON_CANDY_BOX)
        {
            im_print_text_greyed(31, 1, " THE ");
            im_print_text_greyed(31, 2, "CANDY");
            im_print_text_greyed(31, 3, " BOX ");
            if (game->featuresUnlocked >= 2)
                if (im_button_quiet(WIDTH - 2, 1, "D") ||
                    im_button_quiet(WIDTH - 2, 2, "B") ||
                    im_button_quiet(WIDTH - 2, 3, "G"))
                    game->menu = ON_DEBUG_MENU;
        }
        if (game->menu == ON_DEBUG_MENU)
        {
            im_print_text_greyed(WIDTH - 2, 1, "D");
            im_print_text_greyed(WIDTH - 2, 2, "B");
            im_print_text_greyed(WIDTH - 2, 3, "G");
            if (im_button_quiet(31, 1, " THE ") ||
                im_button_quiet(31, 2, "CANDY") ||
                im_button_quiet(31, 3, " BOX "))
                game->menu = ON_CANDY_BOX;
        }
    }

    ////////////////////
    // GAME BODY HERE //
    ////////////////////

    if (game->menu == ON_CANDY_BOX)
    {
        if (game->candy > 0)
            game->check.hasOneCandy = true;

        if (game->check.hasOneCandy)
        {
            if (im_button(1, 6, "Eat all the candies"))
            {
                game->hasOneCandyCounter += game->candy;
                game->candy = 0;
            }
            if (game->hasOneCandyCounter)
                im_print(1, 7, "You have eaten %d cand%s",
                         game->hasOneCandyCounter,
                         (game->hasOneCandyCounter == 1) ? "y" : "ies");
        }

        if (game->candy > 10)
            game->check.hasTenCandy = true;

        if (game->check.hasTenCandy)
        {
            if (im_button(1, 9, "Throw 10 candies to the ground") && game->candy >= 10)
            {
                game->hasTenCandyCounter++;
                game->candy -= 10;
            }
            if (game->hasTenCandyCounter)
                im_print(1, 10, "You threw %d candies on the ground%s",
                         game->hasTenCandyCounter * 10,
                         getThrowAnim(game->hasTenCandyCounter));
        }

        if (game->candy > 30)
            game->check.hasThirtyCandy = true;

        if (game->check.hasThirtyCandy && game->featuresUnlocked == 0)
        {
            if (im_button(1, 12, "Request a new feature (30 candies)") && game->candy >= 30)
            {
                game->featuresUnlocked++;
                game->candy -= 30;
            }
        }

        if (game->featuresUnlocked == 1)
            im_print_text(1, 13, "You've unlocked a status bar!");

        if (game->check.hasThirtyCandy && game->featuresUnlocked == 1)
        {
            if (im_button(1, 12, "Request another feature (5 candies)") && game->candy >= 5)
            {
                game->featuresUnlocked++;
                game->candy -= 5;
            }
        }

        if (game->featuresUnlocked == 2)
            im_print_text(1, 13, "You've unlocked the debug menu!");

        if (game->check.hasThirtyCandy && game->featuresUnlocked == 2)
        {
            if (im_button(1, 12, "Request another feature (5 candies)") && game->candy >= 5)
            {
                game->featuresUnlocked++;
                game->candy -= 5;
            }
        }

        if (game->featuresUnlocked == 3)
            im_print_text(1, 13, "You've unlocked the merchant!");
    }

    // DEBUG MENU //

    else if (game->menu == ON_DEBUG_MENU)
    {
        if (im_button(30, 6, "O"))
        {
            game->check.DARK_MODE = !game->check.DARK_MODE;
            if (game->check.DARK_MODE)
            {
                pg_set_default_bg_color(0xFF000000);
                pg_set_default_fg_color(0xFFFFFFFF);
            }
            else
            {
                pg_set_default_bg_color(0xFFFFFFFF);
                pg_set_default_fg_color(0xFF000000);
            }
        }
        im_print(32, 6, "%s", (game->check.DARK_MODE) ? "NIGHT" : "DAY");

        if (im_button(1, 6, "Reset candies"))
            game->candy = 0;
        if (im_button(1, 8, "Reset candies eaten"))
            game->hasOneCandyCounter = 0;
        if (im_button(1, 10, "Reset candies thrown"))
            game->hasTenCandyCounter = 0;

        if (im_button(1, HEIGTH - 4, "EXIT GAME"))
            game->check.EXIT_GAME = true;
    }

    // MERCHANT MENU //

    else if (game->menu == ON_MERCHANT)
    {
    }
}

void game_shutdown(Game *game)
{
    // rm *
}

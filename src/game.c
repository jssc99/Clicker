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

void header_button_candybox(Game *game)
{
    if (im_button_quiet(31, 1, " THE ") ||
        im_button_quiet(31, 2, "CANDY") ||
        im_button_quiet(31, 3, " BOX "))
        game->menu = ON_CANDY_BOX;
}

void header_button_merchant(Game *game)
{
    if (im_button_quiet(37, 1, "MERC") ||
        im_button_quiet(37, 2, "HANT") ||
        im_button_quiet(37, 3, "SHOP"))
        game->menu = ON_MERCHANT;
}

void header_button_savemenu(Game *game)
{
    if (im_button_quiet(WIDTH - 4, 1, "S") ||
        im_button_quiet(WIDTH - 4, 2, "V") ||
        im_button_quiet(WIDTH - 4, 3, "E"))
        game->menu = ON_SAVE_MENU;
}

void header_button_debugmenu(Game *game)
{
    if (im_button_quiet(WIDTH - 2, 1, "D") ||
        im_button_quiet(WIDTH - 2, 2, "B") ||
        im_button_quiet(WIDTH - 2, 3, "G"))
        game->menu = ON_DEBUG_MENU;
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
    if (game->lollypop)
        im_print(1, 2, "You've got %lu lollypop%s", game->lollypop, (game->lollypop == 1) ? "" : "s");

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
            if (game->featuresUnlocked >= 3)
                im_print_text(WIDTH - 5, i, "|");
            if (game->featuresUnlocked >= 4)
                im_print_text(41, i, "|");
        }

        if (game->menu == ON_CANDY_BOX)
        {
            im_print_text_greyed(31, 1, " THE ");
            im_print_text_greyed(31, 2, "CANDY");
            im_print_text_greyed(31, 3, " BOX ");
            if (game->featuresUnlocked >= 2)
                header_button_debugmenu(game);
            if (game->featuresUnlocked >= 3)
                header_button_savemenu(game);
            if (game->featuresUnlocked >= 4)
                header_button_merchant(game);
        }

        if (game->menu == ON_DEBUG_MENU)
        {
            im_print_text_greyed(WIDTH - 2, 1, "D");
            im_print_text_greyed(WIDTH - 2, 2, "B");
            im_print_text_greyed(WIDTH - 2, 3, "G");
            header_button_candybox(game);
            if (game->featuresUnlocked >= 3)
                header_button_savemenu(game);
            if (game->featuresUnlocked >= 4)
                header_button_merchant(game);
        }

        if (game->menu == ON_SAVE_MENU)
        {
            im_print_text_greyed(WIDTH - 4, 1, "S");
            im_print_text_greyed(WIDTH - 4, 2, "V");
            im_print_text_greyed(WIDTH - 4, 3, "E");
            header_button_candybox(game);
            header_button_debugmenu(game);
            if (game->featuresUnlocked >= 4)
                header_button_merchant(game);
        }

        if (game->menu == ON_MERCHANT)
        {
            im_print_text_greyed(37, 1, "MERC");
            im_print_text_greyed(37, 2, "HANT");
            im_print_text_greyed(37, 3, "SHOP");
            header_button_candybox(game);
            header_button_savemenu(game);
            header_button_debugmenu(game);
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
            im_print_text(1, 13, "You've unlocked the status bar!");

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
            if (im_button(1, 12, "And another one (5 candies)") && game->candy >= 5)
            {
                game->featuresUnlocked++;
                game->candy -= 5;
            }
        }

        if (game->featuresUnlocked == 3)
            im_print_text(1, 13, "You've unlocked the save menu!");

        if (game->check.hasThirtyCandy && game->featuresUnlocked == 3)
        {
            if (im_button(1, 12, "A final one please! (5 candies)") && game->candy >= 5)
            {
                game->featuresUnlocked++;
                game->candy -= 5;
            }
        }

        if (game->featuresUnlocked == 4)
            im_print_text(1, 13, "You've unlocked the merchant!");
    }

    // DEBUG MENU //

    else if (game->menu == ON_DEBUG_MENU)
    {
        if (im_button(32, 6, "O"))
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
        im_print(34, 6, "%s", (game->check.DARK_MODE) ? "NIGHT" : "DAY");

        if (im_button(1, 6, "Reset candies"))
            game->candy = 0;
        if (im_button(1, 8, "Reset candies eaten"))
            game->hasOneCandyCounter = 0;
        if (im_button(1, 10, "Reset candies thrown"))
            game->hasTenCandyCounter = 0;

        if (im_button(1, 13, "Reset lollypops"))
            game->lollypop = 0;

        if (im_button(1, HEIGTH - 4, "EXIT GAME"))
            game->check.EXIT_GAME = true;
    }

    // SAVE MENU //

    else if (game->menu == ON_SAVE_MENU)
    {
    }

    // MERCHANT MENU //

    else if (game->menu == ON_MERCHANT)
    {
        im_print_text(1, 6, "Hello, I'm the candy merchant.");
        im_print_text(1, 7, "I would do anything for candies.");
        im_print_text(1, 8, "My lollipops are delicious!");

        if (im_button(1, 30, "One lollypop please! (60 candies)") && game->candy >= 60)
        {
            game->lollypop++;
            game->candy -= 60;
        }
    }
}

void game_shutdown(Game *game)
{
    // rm *
}

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>

#include "game.h"
#include "gui.h"

void game_init(Game *game)
{
    game->menu = ON_CANDY_BOX;
}

void game_save(Game *game, const char *filename)
{
    FILE *save = fopen(filename, "w");
    if (save == NULL)
    {
        printf("error saving game\n");
        return;
    }
    fwrite(game, sizeof(Game), 1, save);
    fclose(save);
}

void game_load(Game *game, const char *filename)
{
    FILE *save = fopen(filename, "r");
    if (save == NULL)
    {
        printf("error loading save\n");
        return;
    }
    fread(game, sizeof(Game), 1, save);
    fclose(save);
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
    if (im_big_button_quiet(31, 1, " THE ", "CANDY", " BOX "))
        game->menu = ON_CANDY_BOX;
}

void header_button_forge(Game *game)
{
    if (im_big_button_quiet(37, 1, "LOLLY", " POP ", "FORGE"))
        game->menu = ON_FORGE;
}

void header_button_merchant(Game *game)
{
    if (im_big_button_quiet(43, 1, "MERC", "HANT", "SHOP"))
        game->menu = ON_MERCHANT;
}

void header_button_savemenu(Game *game)
{
    if (im_big_button_quiet(WIDTH - 4, 1, "S", "V", "E"))
        game->menu = ON_SAVE_MENU;
}

void header_button_debugmenu(Game *game)
{
    if (im_big_button_quiet(WIDTH - 2, 1, "D", "B", "G"))
        game->menu = ON_DEBUG_MENU;
}

void draw_header(Game *game)
{

    im_print_text(0, 0, "+------------------------------------------------------------------------------+");
    im_print_text(0, 4, "+------------------------------------------------------------------------------+");
    im_triple_print_text(0, 1, "|"); // header box
    im_triple_print_text(WIDTH - 1, 1, "|");
    im_triple_print_text(30, 1, "|");
    im_triple_print_text(36, 1, "|"); // candy box delimiters
    if (game->featuresUnlocked >= 2)
        im_triple_print_text(WIDTH - 3, 1, "|"); // debug delims
    if (game->featuresUnlocked >= 3)
        im_triple_print_text(WIDTH - 5, 1, "|"); // save delims
    if (game->featuresUnlocked >= 4)
        im_triple_print_text(42, 1, "|"); // forge delims
    if (game->featuresUnlocked >= 5)
        im_triple_print_text(47, 1, "|"); // merchant delims

    // header buttons

    if (game->featuresUnlocked >= 1)
        if (game->menu != ON_CANDY_BOX)
            header_button_candybox(game);
        else
            im_big_print_text_greyed(31, 1, " THE ", "CANDY", " BOX ");

    if (game->featuresUnlocked >= 2)
        if (game->menu != ON_DEBUG_MENU)
            header_button_debugmenu(game);
        else
            im_big_print_text_greyed(WIDTH - 2, 1, "D", "B", "G");

    if (game->featuresUnlocked >= 3)
        if (game->menu != ON_SAVE_MENU)
            header_button_savemenu(game);
        else
            im_big_print_text_greyed(WIDTH - 4, 1, "S", "V", "E");

    if (game->featuresUnlocked >= 4)
        if (game->menu != ON_FORGE)
            header_button_forge(game);
        else
            im_big_print_text_greyed(37, 1, "LOLLY", " POP ", "FORGE");

    if (game->featuresUnlocked >= 5)
        if (game->menu != ON_MERCHANT)
            header_button_merchant(game);
        else
            im_big_print_text_greyed(43, 1, "MERC", "HANT", "SHOP");
}

void draw_candybox(Game *game)
{
    // Eat Candy

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
                     (game->hasOneCandyCounter == true) ? "y" : "ies");
    }

    // Throw Candy

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

    // Features

    if (game->candy > 30)
        game->check.hasThirtyCandy = true;

    if (game->featuresUnlocked == 1)
        im_print_text(1, 13, "You've unlocked the status bar!");
    else if (game->featuresUnlocked == 2)
        im_print_text(1, 13, "You've unlocked the debug menu!");
    else if (game->featuresUnlocked == 3)
        im_print_text(1, 13, "You've unlocked the save menu!");
    else if (game->featuresUnlocked == 4)
        im_print_text(1, 13, "You've unlocked the lollypop forge!");

    if (game->check.hasThirtyCandy)
    {
        if (game->featuresUnlocked == 3)
            if (im_button(1, 12, "One final one please! (5 candies)") && game->candy >= 5)
            {
                game->featuresUnlocked++;
                game->candy -= 5;
            }
        if (game->featuresUnlocked == 2)
            if (im_button(1, 12, "And another one (5 candies)") && game->candy >= 5)
            {
                game->featuresUnlocked++;
                game->candy -= 5;
            }
        if (game->featuresUnlocked == 1)
            if (im_button(1, 12, "Request another feature (5 candies)") && game->candy >= 5)
            {
                game->featuresUnlocked++;
                game->candy -= 5;
            }
        if (game->featuresUnlocked == false)
            if (im_button(1, 12, "Request a new feature (30 candies)") && game->candy >= 30)
            {
                game->featuresUnlocked++;
                game->candy -= 30;
            }
    }

    // Secret lollypop

    if (game->check.foundCandyBoxLolly == false && game->featuresUnlocked)
    {
        if (im_button_quiet(WIDTH - 4, 4, "---o"))
        {
            game->lollypop++;
            game->check.foundCandyBoxLolly = true;
        }
    }
    else if (game->check.foundCandyBoxLolly)
        im_print_text(1, 47, "You found the hidden lollypop!");
}

void draw_forge(Game *game)
{
    print_file(1, 9, "assets/forge.txt");

    if (game->forgeDialog == 0)
    {
        im_print_text(1, 6, "Hello, I'm the lollypop maker.");
        im_print_text(1, 7, "I would do anything for some candies.");
        im_print_text(1, 8, "My lollypops are delicious!");
    }
    else if (game->forgeDialog == 1)
        im_print_text(1, 7, "Here you go.");
    else if (game->forgeDialog == 2)
        im_print_text(1, 7, "My lollypops are delicious!");
    else if (game->forgeDialog == 3)
        im_print_text(1, 7, "Somebody likes lollypops ahaha.");
    else if (game->forgeDialog == 4 || game->forgeDialog == 5)
    {
        im_print_text(1, 6, "You seen to have a lot of candies on you.");
        im_print_text(1, 7, "I think you should also give a visit to a friend of mine.");
        im_print_text(1, 8, "He's a merchant next door, he'll have lots of stuff to sell to you!");
        if (game->featuresUnlocked == 4)
            game->featuresUnlocked++;
    }
    else if (game->forgeDialog >= 6)
        im_print_text(1, 7, "Make sure you give a visit to my good friend the merchant.");

    if (im_button(1, 45, "One lollypop please! (60 candies)") && game->candy >= 60)
    {
        game->candy -= 60;
        game->lollypop++;
        game->forgeDialog++;
    }

    if (game->check.foundForgeLolly == false)
    {
        if (im_button_quiet(12, 36, "---o"))
        {
            game->lollypop++;
            game->check.foundForgeLolly = true;
        }
    }
    else
        im_print_text(1, 47, "You found the hidden lollypop!");
}

void draw_merchant(Game *game)
{
    print_file(1, 9, "assets/merchant.txt");
    im_print_text(1, 7, "Go away, i'm currently under construction.");

    if (game->check.foundMerchantLolly == false)
    {
        if (im_big_button_quiet(59, 19, "o", "|", "|"))
        {
            game->lollypop++;
            game->check.foundMerchantLolly = true;
        }
    }
    else
        im_print_text(1, 8, "Hey! My lollypop monocle!");
}

void draw_savemenu(Game *game)
{
    if (im_button(1, 6, "Save binary"))
        game_save(game, "save.bin");
    if (im_button(1, 8, "Load binary"))
        game_load(game, "save.bin");
    change_bg_fg(game->check.DARK_MODE);

    if (im_button(1, HEIGTH - 4, "EXIT GAME"))
        game->check.EXIT_GAME = true;
}

void draw_debugmenu(Game *game)
{
    if (im_button(32, 6, "O"))
    {
        game->check.DARK_MODE = !game->check.DARK_MODE;
        change_bg_fg(game->check.DARK_MODE);
    }
    im_print(34, 6, "DARK O%s", (game->check.DARK_MODE) ? "N" : "FF");

    if (im_button(1, 6, "Reset candies"))
        game->candy = 0;
    if (im_button(1, 8, "Reset candies eaten"))
        game->hasOneCandyCounter = 0;
    if (im_button(1, 10, "Reset candies thrown"))
        game->hasTenCandyCounter = 0;

    if (im_button(1, 13, "Reset lollypops"))
        game->lollypop = 0;
    if (im_button(1, 15, "Reset forge dialog"))
        game->forgeDialog = 0;
    if (im_button(1, 17, "Reset secret lollypops"))
    {
        game->check.foundCandyBoxLolly = false;
        game->check.foundForgeLolly = false;
        game->check.foundMerchantLolly = false;
    }
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

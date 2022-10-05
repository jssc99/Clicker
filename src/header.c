#include "header.h"

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

void draw_box(int features) 
{
    im_print_text(0, 0, "+------------------------------------------------------------------------------+");
    im_print_text(0, 4, "+------------------------------------------------------------------------------+");
    im_triple_print_text(0, 1, "|"); // header box
    im_triple_print_text(WIDTH - 1, 1, "|");
    im_triple_print_text(30, 1, "|");
    im_triple_print_text(36, 1, "|"); // candy box delimiters
    if (features >= 2)
        im_triple_print_text(WIDTH - 3, 1, "|"); // debug delims
    if (features >= 3)
        im_triple_print_text(WIDTH - 5, 1, "|"); // save delims
    if (features >= 4)
        im_triple_print_text(42, 1, "|"); // forge delims
    if (features >= 5)
        im_triple_print_text(47, 1, "|"); // merchant delims}
}

void draw_header(Game *game)
{
    draw_box(game->featuresUnlocked);

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

#include "header.h"

void header_button(Menu* currentMenu, Menu menu, int x, int y, const char *text1, const char *text2, const char *text3)
{
    if (*currentMenu == menu)
        im_big_print_text_greyed(x, y, text1, text2, text3);
    else if (im_big_button_quiet(x, y, text1, text2, text3))
        *currentMenu = menu;
}

void draw_basic_box()
{
    im_print_text(0, 0, "+-------------------------------------------------------------------------------------------------------+");
    im_triple_print_text(0, 1, "|");
    im_triple_print_text(30, 1, "|");
    im_triple_print_text(WIDTH - 1, 1, "|");
    im_print_text(0, 4, "+-------------------------------------------------------------------------------------------------------+");
}

void draw_header(Menu* currentMenu, int featuresUnlocked)
{
    draw_basic_box();

    // header buttons

    if (featuresUnlocked >= CANDYBOX)
    {
        header_button(currentMenu, ON_CANDY_BOX, 31, 1, " THE ", "CANDY", " BOX ");
        im_triple_print_text(36, 1, "|"); // candy box delimiters
    }

    if (featuresUnlocked >= DEBUGMENU)
    {
        header_button(currentMenu, ON_DEBUG_MENU, WIDTH - 2, 1, "D", "B", "G");
        im_triple_print_text(WIDTH - 3, 1, "|"); // debug delimiters
    }

    if (featuresUnlocked >= SAVEMENU)
    {
        header_button(currentMenu, ON_SAVE_MENU, WIDTH - 4, 1, "S", "V", "E");
        im_triple_print_text(WIDTH - 5, 1, "|"); // save delimiters
    }

    if (featuresUnlocked >= MAP)
    {
        header_button(currentMenu, ON_MAP, 37, 1, "   ", "MAP", "   ");
        im_triple_print_text(40, 1, "|"); // merchant delimiters
    }

    if (featuresUnlocked >= FORGE)
    {
        header_button(currentMenu, ON_FORGE, 41, 1, "LOLLY", " POP ", "FORGE");
        im_triple_print_text(46, 1, "|"); // forge delimiters
    }

    if (featuresUnlocked >= MERCHANT)
    {
        header_button(currentMenu, ON_MERCHANT, 47, 1, "MERC", "HANT", "SHOP");
        im_triple_print_text(51, 1, "|"); // merchant delimiters
    }
}

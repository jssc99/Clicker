#include "map.h"

void draw_map(Game *game)
{
    print_file(1, 9, "assets/village.txt");

    if (game->featuresUnlocked < MERCHANT)
        im_print_text(1, 7, "The merchant is currently out, but the forge is open.");
    else if (im_custom_button(20, 30, 8, 10))
        game->menu = ON_MERCHANT;

    if (im_custom_button(62, 33, 10, 6))
    {
        game->menu = ON_FORGE;
        if (game->featuresUnlocked == MAP)
            game->featuresUnlocked++;
    }

    // Secret lollypop

    if (game->check.foundMapLolly == false)
    {
        if (im_big_button_quiet(80, 40, "O", "|", "|"))
        {
            game->lollypop.amount++;
            game->check.foundMapLolly = true;
        }
    }
    else
        im_print_text(1, HEIGTH - 2, "You found the hidden lollypop!");
}

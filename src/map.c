#include "map.h"

void draw_map(Game *game)
{
    print_file(1, 9, "assets/village.txt");
    
    if (game->featuresUnlocked < MERCHANT)
        im_print_text(1, 7, "The merchant is currently out, but the forge is open.");

    if (im_house_button(62, 33, 10, 6))
    {
        game->menu = ON_FORGE;
        if (game->featuresUnlocked == MAP)
            game->featuresUnlocked++;
    }

    if (im_house_button(20, 30, 8, 10))
    {
        if (game->featuresUnlocked >= MERCHANT)
        {
            game->menu = ON_MERCHANT;
            if (game->featuresUnlocked == FORGE)
                game->featuresUnlocked++;
        }
    }
}
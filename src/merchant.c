#include "merchant.h"

void draw_merchant(Game *game)
{
    print_file(2, 9, "assets/merchant.txt");
    im_print_text(1, 7, "Go away, i'm currently under construction.");

    if (game->check.foundMerchantLolly == false)
    {
        if (im_big_button_quiet(68, 23, "o", "|", "|"))
        {
            game->lollypop.amount++;
            game->check.foundMerchantLolly = true;
        }
    }
    else
        im_print_text(1, 8, "Hey! My lollypop monocle!");
}
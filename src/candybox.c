#include "candybox.h"

const char *getThrowAnim(int counter)
{
    if (counter == 1)
        return ".";
    else if (counter == 2)
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
    else
        return ". Fuck You.";
}

void draw_candybox(Game *game)
{
    // Eat Candy

    if (game->candy.number > 0)
        game->check.hasOneCandy = true;

    if (game->check.hasOneCandy)
    {
        if (im_button(1, 6, "Eat all the candies"))
        {
            game->candyEaten += game->candy.number;
            game->candy.number = 0;
        }
        if (game->candyEaten)
            im_print(1, 7, "You have eaten %d cand%s", game->candyEaten,
                     (game->candyEaten == true) ? "y" : "ies");
    }

    // Throw Candy

    if (game->candy.number > 9)
        game->check.hasTenCandy = true;

    if (game->check.hasTenCandy)
    {
        if (im_button(1, 9, "Throw 10 candies to the ground") && game->candy.number >= 10)
        {
            game->candyThrown++;
            game->candy.number -= 10;
        }
        if (game->candyThrown)
            im_print(1, 10, "You threw %d candies on the ground%s",
                     game->candyThrown * 10,
                     getThrowAnim(game->candyThrown));
    }

    // Features

    if (game->candy.number > 30)
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
            if (im_button(1, 12, "One final one please! (5 candies)") && game->candy.number >= 5)
            {
                game->featuresUnlocked++;
                game->candy.number -= 5;
            }
        if (game->featuresUnlocked == 2)
            if (im_button(1, 12, "And another one (5 candies)") && game->candy.number >= 5)
            {
                game->featuresUnlocked++;
                game->candy.number -= 5;
            }
        if (game->featuresUnlocked == 1)
            if (im_button(1, 12, "Request another feature (5 candies)") && game->candy.number >= 5)
            {
                game->featuresUnlocked++;
                game->candy.number -= 5;
            }
        if (game->featuresUnlocked == 0)
            if (im_button(1, 12, "Request a new feature (30 candies)") && game->candy.number >= 30)
            {
                game->featuresUnlocked++;
                game->candy.number -= 30;
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
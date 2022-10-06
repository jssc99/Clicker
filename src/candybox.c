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

void im_feature_button(Counter *counter, int *featuresUnlocked, int x, int y, const char *text, int cost)
{
    if (im_button(x, y, text) && counter->amount >= cost)
    {
        *featuresUnlocked += 1;
        counter->amount -= cost;
    }
}

void draw_candybox(Game *game)
{
    // Eat Candy

    if (game->candy.amount > 0)
        game->check.hasOneCandy = true;

    if (game->check.hasOneCandy)
    {
        if (im_button(1, 6, "Eat all the candies"))
        {
            game->candyEaten += game->candy.amount;
            game->candy.amount = 0;
        }
        if (game->candyEaten)
            im_print(1, 7, "You have eaten %d cand%s.", game->candyEaten,
                     (game->candyEaten == true) ? "y" : "ies");
    }

    // Throw Candy

    if (game->candy.amount > 9)
        game->check.hasTenCandy = true;

    if (game->check.hasTenCandy)
    {
        if (im_button(1, 9, "Throw 10 candies to the ground") && game->candy.amount >= 10)
        {
            game->candyThrown++;
            game->candy.amount -= 10;
        }
        if (game->candyThrown)
            im_print(1, 10, "You threw %d candies on the ground%s", game->candyThrown * 10,
                     getThrowAnim(game->candyThrown));
    }

    // Features

    if (game->candy.amount > 29)
        game->check.hasThirtyCandy = true;

    if (game->check.hasThirtyCandy)
    {
        switch (game->featuresUnlocked)
        {
        case MAP:
            im_print_text(1, 13, "You've unlocked the map!");
            break;

        case SAVEMENU:
            im_feature_button(&game->candy, &game->featuresUnlocked,
                              1, 12, "One final one please! (5 candies)", 5);
            im_print_text(1, 13, "You've unlocked the save menu!");
            break;

        case DEBUGMENU:
            im_feature_button(&game->candy, &game->featuresUnlocked,
                              1, 12, "And another one (5 candies)", 5);
            im_print_text(1, 13, "You've unlocked the debug menu!");
            break;

        case CANDYBOX:
            im_feature_button(&game->candy, &game->featuresUnlocked,
                              1, 12, "Request another feature (5 candies)", 5);
            im_print_text(1, 13, "You've unlocked the status bar!");
            break;

        case NONE:
            im_feature_button(&game->candy, &game->featuresUnlocked,
                              1, 12, "Request a new feature (30 candies)", 30);
            break;

        default:
            break;
        }
    }

    // Secret lollypop

    if (game->featuresUnlocked)
        if (game->check.foundCandyBoxLolly == false)
        {
            if (im_button_quiet(WIDTH - 3, 4, "--O"))
            {
                game->lollypop.amount++;
                game->check.foundCandyBoxLolly = true;
            }
        }
        else
            im_print_text(1, 47, "You found the hidden lollypop!");
}
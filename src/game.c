#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>

#include "game.h"
#include "gui.h"

void game_init(Game *game)
{
    game->menu = ON_FORGE;
}

void game_save(Game *game, const char *filename)
{
    FILE *save = fopen(filename, "w");
    if (save == NULL)
        printf("error saving game\n");
    fwrite(game, sizeof(Game), 1, save);
    fclose(save);
}

void game_load(Game *game, const char *filename)
{
    FILE *save = fopen(filename, "r");
    if (save == NULL)
        printf("error loading save\n");
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

void print_file(int x, int y, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        printf("error printing file\n");
    char buffer[254], c;
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i != size; i++)
    {
        for (int f = 0; i != size; c = scanf(file), f++)
            im_print(x + f, y + i, "%c", c);
    }
    fclose(file);
}

void change_bg_fg(Game *game)
{
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

void header_button_candybox(Game *game)
{
    if (im_button_quiet(31, 1, " THE ") ||
        im_button_quiet(31, 2, "CANDY") ||
        im_button_quiet(31, 3, " BOX "))
        game->menu = ON_CANDY_BOX;
}

void header_button_forge(Game *game)
{
    if (im_button_quiet(37, 1, "LOLLY") ||
        im_button_quiet(37, 2, " POP ") ||
        im_button_quiet(37, 3, "FORGE"))
        game->menu = ON_FORGE;
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

void draw_header(Game *game)
{
    im_print_text(0, 0, "+------------------------------------------------------------------------------+");
    im_print_text(0, 4, "+------------------------------------------------------------------------------+");
    for (int i = 1; i < 4; i++)
    {
        im_print_text(0, i, "|");
        im_print_text(30, i, "|");
        im_print_text(36, i, "|");
        im_print_text(WIDTH - 1, i, "|");
        if (game->featuresUnlocked >= 2)
            im_print_text(WIDTH - 3, i, "|");
        if (game->featuresUnlocked >= 3)
            im_print_text(WIDTH - 5, i, "|");
        if (game->featuresUnlocked >= 4)
            im_print_text(42, i, "|");
    }

    if (game->featuresUnlocked >= 1)
        if (game->menu != ON_CANDY_BOX)
            header_button_candybox(game);
        else
        {
            im_print_text_greyed(31, 1, " THE ");
            im_print_text_greyed(31, 2, "CANDY");
            im_print_text_greyed(31, 3, " BOX ");
        }
    if (game->featuresUnlocked >= 2)
        if (game->menu != ON_DEBUG_MENU)
            header_button_debugmenu(game);
        else
        {
            im_print_text_greyed(WIDTH - 2, 1, "D");
            im_print_text_greyed(WIDTH - 2, 2, "B");
            im_print_text_greyed(WIDTH - 2, 3, "G");
        }
    if (game->featuresUnlocked >= 3)
        if (game->menu != ON_SAVE_MENU)
            header_button_savemenu(game);
        else
        {
            im_print_text_greyed(WIDTH - 4, 1, "S");
            im_print_text_greyed(WIDTH - 4, 2, "V");
            im_print_text_greyed(WIDTH - 4, 3, "E");
        }
    if (game->featuresUnlocked >= 4)
        if (game->menu != ON_FORGE)
            header_button_forge(game);
        else
        {
            im_print_text_greyed(37, 1, "LOLLY");
            im_print_text_greyed(37, 2, " POP ");
            im_print_text_greyed(37, 3, "FORGE");
        }
}

void draw_candybox(Game *game)
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
                     (game->hasOneCandyCounter == true) ? "y" : "ies");
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

    // Features

    if (game->candy > 30)
        game->check.hasThirtyCandy = true;

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

    if (game->check.hasThirtyCandy && game->featuresUnlocked == false)
    {
        if (im_button(1, 12, "Request a new feature (30 candies)") && game->candy >= 30)
        {
            game->featuresUnlocked++;
            game->candy -= 30;
        }
    }

    if (game->featuresUnlocked == 1)
        im_print_text(1, 13, "You've unlocked the status bar!");
}

void draw_forge(Game *game)
{ /*
     {
         im_print_text(1, 9, "|          |         | |       ||_|_________|____                         |");
         im_print_text(1, 10, "|          |         | |      /||_|_________|___ \\                        |");
         im_print_text(1, 11, "|          |         | |      \\||_|_________|____/                        |");
         im_print_text(1, 12, "|          |         | |       || '         '                             |");
         im_print_text(1, 13, "|          |         | |                                   ______         |");
         im_print_text(1, 14, "|          |         | |                                .-' ____ '-.      |");
         im_print_text(1, 15, "|          |         | |                                \\.-'    '-./      |");
         im_print_text(1, 16, "|          |         | |                 __|_________|___\\        /       |");
         im_print_text(1, 17, "|          |         | |                |__|_________|___/        \\       |");
         im_print_text(1, 18, "|          |         | |                   '         '  /'-.____.-'\\      |");
         im_print_text(1, 19, "|    ______|         | |_______                         '-.______.-'      |");
         im_print_text(1, 20, "|   /      |_________|/       /\\                                          |");
         im_print_text(1, 21, "|  /                         / /                            ||            |");
         im_print_text(1, 22, "| /_________________________/ /                            /  \\           |");
         im_print_text(1, 23, "|/__________________________\\/                             \\  /     ____  |");
         im_print_text(1, 24, "|                                                          .\\/.    |____| |");
         im_print_text(1, 25, "|                                    _____                  /\\      :||:  |");
         im_print_text(1, 26, "|              )                    / ~~~ \\                /  \\      ||   |");
         im_print_text(1, 27, "|             (                     \\ 'c' /               /    \\     ||   |");
         im_print_text(1, 28, "|    _____)_________________    ____/\\_-_/\\____          /      \\         |");
         im_print_text(1, 29, "|   /  __(__________)____  /|  /    /     \\    \\    _________________     |");
         im_print_text(1, 30, "|  /  :@@@@@@@@@@@@(@@@@: / | (   )|       |(   )   \\________________\\    |");
         im_print_text(1, 31, "|  :. '-.@@@@@@@@@@@@.-' .: | |   ||       ||   |    \\               /    |");
         im_print_text(1, 32, "|  : '.  '-.______.-'  .' : |  \\   )|     |(   /    __'-._________.-'     |");
         im_print_text(1, 33, "|__:   '-.__________.-'   : |___\\==||_____||==/____|  |_____||  |_________|");
         im_print_text(1, 34, "|  :     |----------|     : |---/  |+-----++:0+----|  |    .'|  |_        |");
         im_print_text(1, 35, "|  :     |----------|     :/'---UUUU+--+--+0000----|  |   |\\.'__'.\\       |");
         im_print_text(1, 36, "|  '-.   |----------|   .-'         |  |  |        |__|    \\|_____|       |");
         im_print_text(1, 37, "|     '-.|__________|.-'            |  |  |                               |");
         im_print_text(1, 38, "|                                   |  |  |                               |");
         im_print_text(1, 39, "|                                   |__|__|                               |");
         im_print_text(1, 40, "|                                   (__|__)                               |");
         im_print_text(1, 41, "|                                                                         |");
         im_print_text(1, 42, "|                                                                         |");
         im_print_text(1, 43, "|_________________________________________________________________________|");
     }*/
    print_file(1, 9, "assets/forge.txt");

    im_print_text(1, 6, "Hello, I'm the lollypop maker.");
    im_print_text(1, 7, "I would do anything for some candies.");
    im_print_text(1, 8, "My lollypops are delicious!");

    if (im_button(1, 45, "One lollypop please! (60 candies)") && game->candy >= 60)
    {
        game->lollypop++;
        game->candy -= 60;
        clear_line(6);
        clear_line(7);
        clear_line(8);
        im_print_text(1, 7, "Here you go.");
    }

    if (game->check.foundForgeLolly == false)
        if (im_button_quiet(12, 36, "---o"))
        {
            game->lollypop++;
            game->check.foundForgeLolly = true;
        }
        else
            im_print_text(1, 47, "You found the hidden lollypop!");
}

void draw_savemenu(Game *game)
{
    if (im_button(1, 6, "Save binary"))
        game_save(game, "save.bin");
    if (im_button(1, 8, "Load binary"))
        game_load(game, "save.bin");
    change_bg_fg(game);

    if (im_button(1, HEIGTH - 4, "EXIT GAME"))
        game->check.EXIT_GAME = true;
}

void draw_debugmenu(Game *game)
{
    if (im_button(32, 6, "O"))
    {
        game->check.DARK_MODE = !game->check.DARK_MODE;
        change_bg_fg(game);
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
        draw_header(game);
    }

    ////////////////////
    // GAME BODY HERE //
    ////////////////////

    if (game->menu == ON_CANDY_BOX)
    {
        draw_candybox(game);
    }
    else if (game->menu == ON_DEBUG_MENU)
    {
        draw_debugmenu(game);
    }
    else if (game->menu == ON_SAVE_MENU)
    {
        draw_savemenu(game);
    }
    else if (game->menu == ON_FORGE)
    {
        draw_forge(game);
    }
}

void game_shutdown(Game *game)
{
    // rm *
}

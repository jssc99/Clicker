#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>
#include <playground_backend_glfw.h>

#include "game.h"

int main(int argc, char *argv[])
{
    GLFWwindow *window;
    char *tile1 = "assets/DB_curses_12x12.png";
    char *tile2 = "assets/Curses_640x300diag.png";
    char *tile3 = "assets/Bedstead-10-df.png";
    pg_backend_glfw_helper_init(&window, "Clicker", pg_config_simple(WIDTH, HEIGTH, tile2));

    pg_set_default_bg_color(0xFFFFFFFF);
    pg_set_default_fg_color(0xFF000000);

    int testIndex = 0;

    Game game = {0};
    game_init(&game);

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        pg_backend_glfw_poll_events();
        pg_clear_all();

        switch (testIndex)
        {/*
        case 1:
            test_button_update();
            break;

        case 2:
            test_save_update();
            break;*/

        default:
            game_update(&game);
        };

        pg_render();
        glfwSwapBuffers(window);

        if (game.EXIT_GAME)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    game_shutdown(&game);
    pg_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>

#include "gui.h"

int im_print_text(int x, int y, const char *text)
{
    for (int i = 0; i < strlen(text); i++)
        pg_put_char(x + i, y, text[i], PG_COL_DEFAULT);
    return 0;
}

int im_print(int x, int y, const char *format, ...)
{
    va_list info;
    va_start(info, format);
    char *str = (char *)malloc(sizeof(char) * 30);
    vsprintf(str, format, info);
    im_print_text(x, y, str);
    va_end(info);
    return 0;
}

bool im_button(int x, int y, const char *text)
{
    im_print_text(x, y, text);
    int Mx, My;
    pg_get_mouse_coords(&Mx, &My);
    if ((Mx >= x && Mx <= (x + strlen(text) - 1)) && My == y && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
        return true;
    else
        return false;
}
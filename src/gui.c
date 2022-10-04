#pragma

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <playground.h>

#include "game.h"
#include "gui.h"

int get_center(const char *text)
{
    return WIDTH / 2 - (strlen(text) / 2);
}

void clear_line(int line)
{
    for (int i = 0; i < WIDTH; i++)
        pg_put_char(i, line, ' ', PG_COL_DEFAULT);
}

int im_print_text(int x, int y, const char *text)
{
    for (int i = 0; i < strlen(text); i++)
        pg_put_char(x + i, y, text[i], PG_COL_DEFAULT);
    return 0;
}

int im_print_text_clicked(int x, int y, const char *text)
{
    for (int i = 0; i < strlen(text); i++)
        pg_put_char_ex(x + i, y, text[i], 0xFFFFFFFF, 0xFF000000, PG_COL_DEFAULT);
    return 0;
}

int im_print_text_greyed(int x, int y, const char *text)
{
    for (int i = 0; i < strlen(text); i++)
        pg_put_char_ex(x + i, y, text[i], 0xFF000000, 0xFFA4A4A4, PG_COL_DEFAULT);
    return 0;
}

int im_print_text_highlight(int x, int y, const char *text)
{
    for (int i = 0; i < strlen(text); i++)
        pg_put_char_ex(x + i, y, text[i], 0xFF000000, 0xFFDFDFDF, PG_COL_DEFAULT);
    return 0;
}

int im_print(int x, int y, const char *format, ...)
{
    va_list info;
    va_start(info, format);
    char str[1024];
    vsprintf(str, format, info);
    im_print_text(x, y, str);
    va_end(info);
    return 0;
}

int im_triple_print_text(int x, int y, const char *text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        pg_put_char(x + i, y, text[i], PG_COL_DEFAULT);
        pg_put_char(x + i, y + 1, text[i], PG_COL_DEFAULT);
        pg_put_char(x + i, y + 2, text[i], PG_COL_DEFAULT);
    }
    return 0;
}

int im_big_print_text(int x, int y, const char *text1, const char *text2, const char *text3)
{
    for (int i = 0; i < strlen(text2); i++)
    {
        pg_put_char(x + i, y, text1[i], PG_COL_DEFAULT);
        pg_put_char(x + i, y + 1, text2[i], PG_COL_DEFAULT);
        pg_put_char(x + i, y + 2, text3[i], PG_COL_DEFAULT);
    }
    return 0;
}

int im_big_print_text_greyed(int x, int y, const char *text1, const char *text2, const char *text3)
{
    for (int i = 0; i < strlen(text2); i++)
    {
        pg_put_char_ex(x + i, y, text1[i], 0xFF000000, 0xFFD3D3D3, PG_COL_DEFAULT);
        pg_put_char_ex(x + i, y + 1, text2[i], 0xFF000000, 0xFFD3D3D3, PG_COL_DEFAULT);
        pg_put_char_ex(x + i, y + 2, text3[i], 0xFF000000, 0xFFD3D3D3, PG_COL_DEFAULT);
    }
    return 0;
}

bool im_button(int x, int y, const char *text)
{
    int mX, mY;
    pg_get_mouse_coords(&mX, &mY);
    if ((mX >= x && mX <= (x + strlen(text) - 1)) && mY == y)
    {
        if (pg_io_mouse_button_released(GLFW_MOUSE_BUTTON_LEFT))
        {
            im_print_text_clicked(x, y, text);
            return true;
        }
        else
            im_print_text_highlight(x, y, text);
    }
    else
    {
        im_print_text_greyed(x, y, text);
        return false;
    }
}

bool im_button_quiet(int x, int y, const char *text)
{
    int mX, mY;
    pg_get_mouse_coords(&mX, &mY);
    im_print_text(x, y, text);
    if ((mX >= x && mX <= (x + strlen(text) - 1)) && mY == y && pg_io_mouse_button_released(GLFW_MOUSE_BUTTON_LEFT))
        return true;
    else
        return false;
}

bool im_big_button_quiet(int x, int y, const char *text1, const char *text2, const char *text3)
{
    if (im_button_quiet(x, y, text1) ||
        im_button_quiet(x, y + 1, text2) ||
        im_button_quiet(x, y + 2, text3))
        return true;
    else
        return false;
}

void change_bg_fg(int status)
{
    if (status)
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

void print_file(int x, int y, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error printing file\n");
        return;
    }

    char *buffer = NULL, c;
    int size = 1;
    size_t len;

    while ((c = fgetc(file)) != EOF)
        if (c == '\n')
            size++;
    fseek(file, 0, SEEK_SET);

    for (int i = -1; i != size; ++i, getline(&buffer, &len, file))
        if (buffer != NULL)
            im_print_text(x, y + i, buffer);

    fclose(file);
}

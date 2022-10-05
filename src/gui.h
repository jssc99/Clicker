#pragma once

#include <stdbool.h>
#include <stdio.h>

int im_print_text(int x, int y, const char *text);
int im_print_text_clicked(int x, int y, const char *text);
int im_print_text_greyed(int x, int y, const char *text);
int im_print_text_highlight(int x, int y, const char *text);
int im_print(int x, int y, const char *format, ...);
int im_triple_print_text(int x, int y, const char *text);
int im_big_print_text(int x, int y, const char *text1, const char *text2, const char *text3);
int im_big_print_text_greyed(int x, int y, const char *text1, const char *text2, const char *text3);

bool im_button(int x, int y, const char *text);
bool im_button_quiet(int x, int y, const char *text);
bool im_big_button_quiet(int x, int y, const char *text1, const char *text2, const char *text3);

void change_bg_fg(int status);
void print_file(int x, int y, const char *filename);

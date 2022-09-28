#pragma

#include <stdbool.h>

int im_print_text_clicked(int x, int y, const char *text);
int im_print_text(int x, int y, const char *text);
int im_print(int x, int y, const char *format, ...);
bool im_button(int x, int y, const char *text);
int get_center(const char *text);
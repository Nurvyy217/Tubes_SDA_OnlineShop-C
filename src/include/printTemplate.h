#ifndef PRINT_TEMPLATE_H
#define PRINT_TEMPLATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*PrintRowFn)(void* data, int index);

void clear_screen();
void print_center(const char *text, int width, int height);
void print_title(const char *title, int width);
void print_table(const char* headers[], int col_count, void* data[], int row_count, PrintRowFn print_row);

#endif

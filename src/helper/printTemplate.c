#include "printTemplate.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[1;1H");
#endif
}

/* Melakukan print center dengan parameter string, panjang dan lebar */
void print_center(const char *text, int width, int height) {
    clear_screen(); // clear screen first

    int text_len = strlen(text);
    
    int vertical_padding = height / 2;
    int horizontal_padding = (width - text_len) / 2;

    // Top empty lines
    for (int i = 0; i < vertical_padding; i++) {
        printf("\n");
    }

    // Centered text line
    for (int i = 0; i < horizontal_padding; i++) printf(" ");
    printf("%s\n", text);

    // Bottom padding (optional for symmetry)
    for (int i = 0; i < height - vertical_padding - 1; i++) {
        printf("\n");
    }
}

void print_top_center(const char *title, int width, int padding) {
    clear_screen();

    char *border = malloc(width + 1);
    if (!border) return;
    memset(border, '=', width);
    border[width] = '\0';

    int left_pad = (width - strlen(title)) / 2;

    printf("%s\n", border);
    printf("%*s%s\n", left_pad, "", title);
    printf("%s\n", border);
    for (int i = 0; i < padding; i++) printf("\n");

    free(border);
}

void print_table(const char* headers[], int col_count, void* data[], int row_count, PrintRowFn print_row) {
    // Print header
    printf("|");
    for (int i = 0; i < col_count; i++) {
        printf(" %-15s |", headers[i]);
    }
    printf("\n");

    // Print separator
    printf("|");
    for (int i = 0; i < col_count; i++) {
        printf("-----------------|");
    }
    printf("\n");

    // Print each row
    for (int i = 0; i < row_count; i++) {
        print_row(data[i], i + 1);
    }
}

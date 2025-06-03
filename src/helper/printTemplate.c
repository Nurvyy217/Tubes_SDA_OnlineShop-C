#include "../include/printTemplate.h"
#include "environment.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[1;1H");
#endif
}

/* Melakukan print center dengan parameter string, panjang dan lebar */
void print_center(const char *text, int width, int height) {
    int text_len = strlen(text);

    int vertical_padding = (height - 3) / 2;
    int horizontal_padding = (width - text_len) / 2;

    // Border atas
    for (int i = 0; i < width; i++) putchar('=');
    putchar('\n');

    // Padding atas
    for (int i = 0; i < vertical_padding; i++) {
        for (int j = 0; j < width; j++) putchar(' ');
        putchar('\n');
    }

    // Print Text
    for (int i = 0; i < horizontal_padding; i++) putchar(' ');
    printf("%s\n", text);

    // Padding bawah
    int bottom_padding = height - vertical_padding - 3;
    for (int i = 0; i < bottom_padding; i++) {
        for (int j = 0; j < width; j++) putchar(' ');
        putchar('\n');
    }

    // Border bawah
    for (int i = 0; i < width; i++) putchar('=');
    putchar('\n');
}
  
/* Melakukan print judul */
void print_title(const char *title, int width) {
    // Print border atas
    for (int i = 0; i < width; i++) {
        putchar('=');
    }
    putchar('\n');

    // Print text
    int len = strlen(title);
    int padding = (width - len) / 2;

    for (int i = 0; i < padding; i++) putchar(' ');
    printf("%s\n", title);

    // Print border bawah
    for (int i = 0; i < width; i++) {
        putchar('=');
    }
    putchar('\n');
    putchar('\n');
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

// Row Example
// void print_transaction_row(void* data, int index) {
//     Transaction* t = (Transaction*)data;
//     printf("| %-3d | %-3d | %-3d | %-3d | %-6d | %-10s |\n", index, t->user_id, t->item_id, t->quantity, t->total_price, t->status);
// }

// void print_user_row(void* data, int index) {
//     User* u = (User*)data;
//     printf("| %-3d | %-15s | %-20s | %-6d |\n", index, u->username, u->email, u->saldo);
// }
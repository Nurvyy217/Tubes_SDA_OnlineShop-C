#include "styleText.h"
#include <stdio.h>
#include <windows.h>
void inputPin(int *pin) {
    char pinChar[7];  // Maksimal 6 digit PIN, 1 untuk null-terminator
    int i = 0;
    char ch;

    while (1) {
        printf("Masukkan PIN (4-6 digit): ");
        i = 0;  // Reset array PIN pada setiap percakapan input
        while (1) {
            ch = getch();  // Mendapatkan input karakter satu per satu
            if (ch == 13) {  // Jika Enter ditekan, keluar dari loop
                pinChar[i] = '\0';  // Akhiri string dengan null-terminator
                break;
            } else if (ch == 8 && i > 0) {  // Jika tombol Backspace ditekan
                printf("\b \b");  // Hapus karakter di terminal
                i--;
            } else if (i < 6) {  // Maksimal 6 digit PIN
                pinChar[i] = ch;  // Simpan karakter PIN
                printf("X");  // Tampilkan X di terminal
                i++;
            }
        }

        // Jika panjang PIN tidak valid (kurang dari 4 atau lebih dari 6)
        if (i >= 4 && i <= 6) {
            // Konversi PIN (char) ke int
            *pin = 0;
            int j;
            for (j = 0; j < i; j++) {
                *pin = *pin * 10 + (pinChar[j] - '0');  // Konversi char ke int
            }
            printf("\n");  // Pindah ke baris baru setelah input selesai
            break;  // Keluar dari loop input
        } else {
            // Jika panjang PIN tidak sesuai
            printf("\nPIN harus terdiri dari 4 hingga 6 digit. Silakan coba lagi.\n");
        }
    }
}

void printCentered(char *text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    
    // Get console dimensions
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    // Calculate positions
    int textLength = strlen(text);
    int x = (columns - textLength) / 2;
    int y = rows / 2;

    // Move cursor to center and print text
    COORD pos = {x, y};
    SetConsoleCursorPosition(hConsole, pos);
    printf("%s", text);
}

void printTopCenter(const char *teks) {
    // Mendapatkan ukuran layar terminal
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int cols, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Menghitung posisi teks di tengah horizontal, tapi di 1/6 vertikal
    int x = (cols - strlen(teks)) / 2; // Posisi horizontal (kiri-kanan)
    int y = rows / 6;                  // Posisi vertikal (1/6 dari tinggi layar)

    // Pindahkan kursor ke posisi 1/6 layar
    int i;
    for (i = 0; i < y; i++) {
        printf("\n"); // Tambah baris kosong untuk mencapai 1/6 layar
    }
    for (i = 0; i < x; i++) {
        printf(" ");  // Tambah spasi untuk mencapai tengah horizontal
    }

    // Cetak teks
    printf("%s\n", teks);
}

void printBottomLeftCorner(const char *teks) {
    // Mendapatkan ukuran layar terminal
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int cols, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // Pindahkan kursor ke baris terakhir
    COORD coord = {0, rows - 1};  // Posisi di baris terakhir, kolom pertama
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Cetak teks di pojok kiri bawah
    printf("%s\n", teks);
}
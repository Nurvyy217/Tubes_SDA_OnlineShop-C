/*
=======================      NOTE     =============================

Setelah pull dan mendapatkan file ini (test.c), uncommand '# src/main/test.c' dalam .gitignore

File ini untuk melakukan testing pengganti main.case
Cara complie lakukan command
./test.sh

command ini bisa dihapus jika sudah melakukan step diatas
*/

#include <stdio.h>
#include <windows.h>
#include "styleText.h"
#include "login.h"
#include "katalog.h"
#include "global.h"
#include "printTemplate.h"

int main()
{
    char choice1, choice2;

    clear_screen();
    print_center("TESTING MODUL", WIDTH, HEIGHT);
    sleep(1);
    clear_screen();
    print_title("INI ADALAH JUDUL", WIDTH);
    printf("JFljasfjsalkfjs\n");
    printf("JFljasfjsalkfjs\n");
    printf("JFljasfjsalkfjs\n");
    printf("JFljasfjsalkfjs\n");
    printf("JFljasfjsalkfjs\n");
    printf("JFljasfjsalkfjs\n");
    printf("JFljasfjsalkfjs\n");
    sleep(1);

    return 0;
}
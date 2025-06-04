#include <stdio.h>
#include <windows.h>
#include "styleText.h"
#include "printTemplate.h"
#include "user.h"
#include "katalog.h"
#include "../include/environment.h"

int main()
{
    print_center("SELAMAT DATANG USER", WIDTH, HEIGHT);
    sleep(2);
    clear_screen();

    print_title("MODUL USER", WIDTH);

    return 0;
}
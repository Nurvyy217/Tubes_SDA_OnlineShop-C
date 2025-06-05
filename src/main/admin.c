#include <stdio.h>
#include <windows.h>
#include "../include/printTemplate.h"
#include "../include/styleText.h"
#include "../include/user.h"
#include "../include/tree.h"
#include "../include/environment.h"

int main()
{
    print_center("SELAMAT DATANG ADMIN", WIDTH, HEIGHT);
    sleep(2);
    clear_screen();

    print_title("MODUL ADMIN", WIDTH);

    return 0;
}
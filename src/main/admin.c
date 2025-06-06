#include "../include/printTemplate.h"
#include "../include/admin.h"
#include <windows.h>

int main()
{
    TreeManager tm;
    print_center("SELAMAT DATANG ADMIN", WIDTH, HEIGHT);
    sleep(2);
    clear_screen();
    InitTree(&tm);

    loginAdmin(&tm);
    return 0;
}
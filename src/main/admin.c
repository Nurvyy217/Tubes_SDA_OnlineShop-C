#include "../include/printTemplate.h"
#include "../include/admin.h"
#include <windows.h>
#include "../include/printTemplate.h"
#include "../include/user.h"
#include "../include/tree.h"
#include "../include/environment.h"

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
#include <stdio.h>
#include <windows.h>
#include "styleText.h"
#include "login.h"
#include "katalog.h"

// int main(){
//     initDatabase();
//     char choice1, choice2;
//     printf("\n\n\n\n\t\t\t\t\t\tWelcome to online shop\n");
//     Sleep(3000);
//     system("cls");
//     printTopCenter("LOGIN / REGISTRASI\n");
//     printf("\t\t\t\t\t\t\t<=====================================>\n");
//     printf("\n\n\n\nPilihan: ");scanf(" %c", &choice1);
// 	system("cls");
//     if (choice1 == '1') {
//     	printf("\t\t\t\t\t\t   1.ADMIN / 2. USER\n");
//     	printf("\t\t\t\t\t<=====================================>\n");
//     	printf("\n\n\n\nPilihan: ");scanf(" %c",&choice2);
//     	system("cls");
//     	if(choice2 == '1'){
//     		loginAdmin();
// 		}
//         else if(choice2 == '2'){
//         	loginUser();
// 	}
//     } else if (choice1 == '2') {
//     	system("cls");
//         registrasi();
//     } else {
//         printf("Pilihan tidak valid. Silakan jalankan ulang program.\n");
//     }
//     return 0;
// }

// int main(){
//     printf("YYYYYYYYYEEEEEEEEEEEEEEAAAAAAAAAAAAAAAAAASSSSSSSSSSSSS");
//     return 0;
// }#include "printTemplate.h"

// int main() {
//     clear_screen();

//     // 1. Center only
//     print_center_only("Welcome to My C App!");

//     sleep(2);
//     clear_screen();

//     // 2. Input menu
//     const char *menu[] = {"Login", "Register", "Exit"};
//     print_input("Main Menu", menu, 3);

//     sleep(2);
//     clear_screen();

//     // 3. Object
//     const char *profile =
//         "Name: John Doe\n"
//         "Email: john@example.com\n"
//         "Level: Admin\n"
//         "Joined: 2025-01-01";

//     print_object("User Profile", profile);

//     return 0;
// }

int main() {
    printf("SELAMAT DATANG USER!");
    return 0;
}

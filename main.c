#include <stdio.h>
#include <windows.h>
#include "styleText.h"
#include "login.h"

int main(){
    char choice1, choice2;
    printf("Welcome to online shop\n");
    Sleep(3000);
    system("cls");
    printf("LOGIN / REGISTRASI\n");
    printf("\t\t\t\t\t<=====================================>\n");
    printf("\n\n\n\nPilihan: ");scanf(" %c", &choice1);
	system("cls");
    if (choice1 == '1') {
    	printf("1.ADMIN / 2. USER");
    	printf("\t\t\t\t\t<=====================================>\n");
    	printf("\n\n\n\nPilihan: ");scanf(" %c",&choice2);
    	system("cls");
    	if(choice2 == '1'){
    		loginAdmin();
		}
        else if(choice2 == '2'){
        	loginUser();
	}
    } else if (choice1 == '2') {
    	system("cls");
        registrasi();
    } else {
        printf("Pilihan tidak valid. Silakan jalankan ulang program.\n");
    }
    return 0;
}
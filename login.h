#ifndef LOGIN_H
#define LOGIN_H
typedef struct {
    char username[50];
    long noRek;
    int pin;
    int saldo;
    int isBlocked;
} User;

void registrasi();
void loginAdmin();
int cekUsernameSudahAda(const char *username);
void loginUser();
#endif
#ifndef LOGIN_H
#define LOGIN_H
typedef struct {
    char username[50];
    int pin;
    int saldo;
} User;

void registrasi();
void loginAdmin();
int cekUsernameSudahAda(const char *username);
void loginUser();
#endif
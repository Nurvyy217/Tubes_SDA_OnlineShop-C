#include <stdio.h>
#include "../include/stack.h"
#include <stdlib.h>
#include <string.h>

void CreateEmpty(Stack *S)
{
    Top(*S) = NULL;
}

void Push(Stack *S, addressTree tree) {
    addressStack newNode = (addressStack)malloc(sizeof(StackNode)); // alokasi memori untuk node baru
    if (newNode != NULL) { // jika alokasi berhasil
        strcpy(City(newNode), Name(tree)); // salin nama kota dari tree ke node baru
        Next(newNode) = Top(*S); // set next node ke top stack saat ini
        Top(*S) = newNode; // set top stack ke node baru
    }
}

void Pop(Stack *S) {
    if (Top(*S) == NULL) return; // jika stack kosong, tidak ada yang bisa di-pop
    addressStack temp = Top(*S); // simpan node paling atas
    printf("%s", City(temp)); // pint nama kota dari node paling atas
    Top(*S) = Next(temp); // set top stack ke node berikutnya
    free(temp);
}

void get_route_string(addressTree target, char *buffer) {
    // contoh implementasi: traversal dari target ke root, lalu simpan ke buffer
    // ini asumsi sederhana, sesuaikan sesuai struktur TreeManager kamu
    char temp[1000] = "";
    while (target != NULL) {
        char nama[100];
        strcpy(nama, target->name); // atau target->city_name, tergantung field-nya
        if (strlen(temp) == 0)
            strcpy(temp, nama);
        else {
            char newTemp[1000];
            sprintf(newTemp, "%s->%s", nama, temp);
            strcpy(temp, newTemp);
        }
        target = target->parent; // atau fungsi get_parent(target)
    }
    strcpy(buffer, temp);
}

// procedure untuk mencetak rute dari root ke node target
void print_route(addressTree target)
{
     if (!target) // jika target tidak valid
    {
        printf("Node tidak ditemukan.\n");
        return;
    }

    Stack S;
    CreateEmpty(&S); // buat stack kosong

    addressTree temp = target; // temp untuk menyimpan node saat ini
    while (temp) {
        Push(&S, temp); // push temp ke stack
        temp = Parent(temp); // pindah ke parent node
    }
    int helper = 1; // untuk mengatur format output agar tidak print " -> " di awal
    while (Top(S)) {
        if (!helper) printf(" -> ");
        Pop(&S);
        helper = 0;
    }
    printf("\n");
}

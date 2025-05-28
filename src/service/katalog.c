#include "katalog.h"
#include <malloc.h>
#include <string.h>
// #include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// MODUL POV ADMIN
void adminKatalog(){
    // Deklarasi variabel
    List katalog;
    int decision;
    char produk[MAX];
    char jenis[MAX];
    int stok;
    int harga;
    int subDecision = 0;
    int statusInt = 1;
    katalog.First = Nil;
    bool search;
    loadKatalogFromFile(&katalog);

    // Begin
    for(;;){
        system("cls");
        printf("KATALOG");
        printf("\n========================");
        printKatalog(katalog);
        printf("========================\n");
        printf("Selamat Datang admin");
        printf("\n1.Tambah Jenis\n2.Hapus Jenis\n3.Tambah Produk\n4.Hapus Produk\n");
        printf("5.Ganti Harga\n6.Tambah Stok\n7.Kurangi Stok\n8.Keluar");
        printf("\nPilihan anda : ");
        scanf("%d", &decision);
        if(decision == 1){
            system("cls");
            printf("\nStatus Pilihan : 1. Tambah Jenis");
            printf("\nMasukkan Jenis barang baru : ");
            scanf("%s", jenis);
            addJenis(&katalog, jenis);
            printf("\nData telah dipdate");
            sleep(2);
        }else if(decision == 2){
            system("cls");
            printf("\nStatus Pilihan : 2. Hapus Jenis");
            printf("\nMasukkan Jenis barang yang akan dihapus : ");
            scanf("%s", jenis);
            delJenis(&katalog, jenis);
            printf("\nData telah di update");
            sleep(2);
        }else if(decision == 3){
            subDecision = 0;
            while(subDecision == 0){
                system("cls");
                printf("\nStatus Pilihan : 3. Tambah Produk");
                printf("\nMasukkan Produk yang akan ditambahkan : ");
                scanf("%s", produk);
                printf("Masukkan Jenis produk yang akan ditambahkan barangnya : ");
                scanf("%s", jenis);
                printf("Masukkan Jumlah stok barang : ");
                scanf("%d", &stok);
                printf("Masukkan Harga barang : ");
                scanf("%d", &harga);
                system("cls");
                printf("Status Tambahan \n");
                printf("%-5s | %-20s | %-5s | %-10s\n", "No", "Barang", "Stok", "Harga");
                printf("----------------------------------------------------------\n");
                printf("%-5d | %-20s | %-5d | %-10d\n", statusInt, produk, stok, harga);
                sleep(1);
                printf("\nApakah data sudah sesuai ?\n1. Ya\n2. Tidak\nMasukkan pilihan anda : ");
                scanf("%d", &subDecision);
                if(subDecision == 1){
                    addProduk(&katalog, harga, stok, produk, jenis);
                    printf("Data telah di update...");
                    sleep(2);
                }
            }
        }else if(decision == 4){
            subDecision = 0;
            while(subDecision == 0){
                system("cls");
                printf("\nStatus Pilihan : 4. Hapus Produk");
                printf("\nMasukkan Jenis dari produk yang akan dihapus : ");
                scanf("%s", jenis);
                printf("\nMasukkan Produk yang akan dihapus : ");
                scanf("%s", produk);
                printf("Data %s ditemukan di kategori %s", produk, jenis);
                printf("\nApakah anda yakin ingin menghapus ? \n1.Ya\n2.tidak\nMasukkan pilihan : ");
                scanf("%d", &subDecision);
                if(subDecision == 1){
                    delProduk(&katalog, produk, jenis);
                }else{
                    subDecision = 0;
                }
            }
        }else if(decision == 5){
            int temp;
            addressProduk P;
            subDecision = 0;
            while(subDecision == 0){
                system("cls");
                printf("\nStatus Pilihan : 5. Ganti Harga");
                printf("\nMasukkan produk yang akan diganti harganya : ");
                scanf("%s", produk);
                P = searchProduk(&katalog, produk);
                if(P != Nil){
                    printf("Data ditemukan\n");
                    printf("%-5s | %-20s | %-5s | %-10s\n", "No", "Barang", "Stok", "Harga");
                    printf("----------------------------------------------------------\n");
                    printf("%-5d | %-20s | %-5d | %-10d\n", statusInt, P->barang, P->stok, P->harga);
                    printf("\nApakah barang yang dicari sudah sesuai ? \n1.Ya\n2.Tidak\nMasukkan pilihan anda : ");
                    scanf("%d", &temp);
                    if(temp == 1){
                        printf("Masukkan harga baru dari produk : ");
                        scanf("%d", &harga);
                        updateHargaProduk(&katalog, harga, produk);
                        printf("Harga barang telah diganti....");
                        sleep(2);
                        subDecision = 1;
                    }else{
                        subDecision = 0;
                    }
                }else{
                    printf("Barang yang dicari tidak ada.....");
                    sleep(1);
                }
            }
        }else if(decision == 6){
            subDecision = 0;
            while(subDecision == 0){
                system("cls");
                printf("\nStatus Pilihan : 6. Tambah Stok");
                printf("\nMasukkan nama produk yang ingin ditambah stoknya: ");
                scanf("%s", produk);
                addressProduk P = searchProduk(&katalog, produk);
                if(P != Nil){
                    printf("Produk ditemukan: %s\nStok saat ini: %d\n", P->barang, P->stok);
                    printf("Masukkan jumlah stok yang ingin ditambahkan: ");
                    scanf("%d", &stok);
                    addStokProduk(&katalog, stok, produk);
                    printf("Stok berhasil ditambah.");
                    sleep(2);
                    subDecision = 1;
                } else {
                    printf("Produk tidak ditemukan.");
                    sleep(2);
                    subDecision = 1;
                }
            }
        }else if(decision == 7){
            subDecision = 0;
            while(subDecision == 0){
                system("cls");
                printf("\nStatus Pilihan : 7. Kurangi Stok");
                printf("\nMasukkan nama produk yang ingin dikurangi stoknya: ");
                scanf("%s", produk);
                addressProduk P = searchProduk(&katalog, produk);
                if(P != Nil){
                    printf("Produk ditemukan: %s\nStok saat ini: %d\n", P->barang, P->stok);
                    printf("Masukkan jumlah stok yang ingin dikurangi: ");
                    scanf("%d", &stok);
                    if(stok > 0){
                        minusStokProduk(&katalog, stok, produk);
                        printf("Stok berhasil dikurangi.");
                    } else {
                        printf("Jumlah pengurangan harus lebih dari 0.");
                    }
                    sleep(2);
                    subDecision = 1;
                } else {
                    printf("Produk tidak ditemukan.");
                    sleep(2);
                    subDecision = 1;
                }
            }
        }else if(decision == 8){
            printf("Update disimpan....");
            sleep(2);
            printf("\nSampai Jumpa Admin...");
            sleep(2);
            break;
        }else{
            printf("Pilihan tidak valid....");
        }
        saveKatalogToFile(katalog);
    }

}

// konstruktor 
addressProduk alokasi_Produk(int harga, int stok, char* barang){
    addressProduk P = (addressProduk)malloc(sizeof(PRODUK));
    if(P != Nil){
        strcpy(P->barang, barang);
        P->stok = stok;
        P->harga = harga;
        P->next = Nil;
        return P;
    }else{
        printf("alokasi gagal!!!");
        return NULL;
    }
}

addressJenis alokasi_Jenis(char* Jenis){
    addressJenis P = (addressJenis)malloc(sizeof(JENIS));
    if(P != Nil){
        strcpy(P->Jenis, Jenis);
        P->next_jenis = Nil;
        P->produkJenis = Nil;
        return P;
    }else{
        printf("alokasi jenis barang gagal!!!");
        return Nil;
    }
}

// MODUL CONTROL
void addProduk(List *P, int harga, int stok, char* barang, char* jenis){
    // (*P) akan selalu menunjuk ke depan jenis katalog
    addressProduk X = alokasi_Produk(harga, stok, barang);
    addressProduk temp;
    addressJenis tempJenis = (*P).First;
    bool duplikat;
    
    if(X == Nil){
        printf("alokasi barang gagal!!!");
        return;
    }
    if(tempJenis != Nil){
        if(strcmp(tempJenis->Jenis, jenis) != 0){
            while( tempJenis != Nil && strcmp(tempJenis->Jenis, jenis) != 0){
                tempJenis = tempJenis->next_jenis;
            }

            if(tempJenis == Nil){
                printf("tidak ada jenis barang yang sesuai...");
                free(X);
                return;
            }
        }
        temp = tempJenis->produkJenis; // tempJenis->produkJenis akan menjadi first untuk list produk
        if(temp != Nil){
            duplikat = isDuplikatProduk(&temp, barang);
            if(duplikat == false){
                while(temp->next != Nil){
                    temp = temp->next;
                }
            }else{
                printf("sudah ada barang di list...");
                free(X);
                return;
            }

            temp->next = X;
            temp = Nil;
        }else{
            tempJenis->produkJenis = X;
        }
    }else{
        printf("tidak ada jenis barang!!!");
        free(X);
        return;
    }
}

void addJenis(List *P, char* Jenis){
    // (*P) akan selalu menunjuk ke depan jenis katalog
    addressJenis X = alokasi_Jenis(Jenis);
    addressJenis temp;
    addressJenis head = (*P).First;
    bool duplikat;
    if(X != Nil){
        if((*P).First != Nil){
            duplikat = isDuplikatJenis(P, Jenis);
            if(duplikat == false){
                while(head->next_jenis != Nil){
                    head = head->next_jenis;
                }
                if(head->next_jenis == Nil){
                    head->next_jenis = X;
                    printf("Jenis %s berhasil ditambahkan di toko", Jenis);
                }
            }else if(duplikat == true){
                printf("Sudah ada jenis barang yang sama....");
                free(X);
                return;
            }
        }else{
            (*P).First = X;
            printf("Jenis %s sudah ditambahkan di toko", Jenis);
        }
    }else{
        printf("alokasi jenis gagal!!!");
        return;
    }
}

void delProduk(List *P, char* produk, char* jenis){
    // (*P) menunujuk ke node jenis yang paling depan
    addressJenis X = (*P).First;
    addressProduk temp; // wadah untuk menghapus
    addressProduk prev;
    
    if(X != Nil){
        while(X != Nil && strcmp(X->Jenis, jenis) != 0){
            X = X->next_jenis;
        }
        if(X == Nil){
            printf("tidak ada Jenis yang sesuai dengan list...");
            return;
        }else if(strcmp(X->Jenis, jenis) == 0){
            if(X->produkJenis != Nil){
                if(strcmp(X->produkJenis->barang, produk) == 0){
                    temp = X->produkJenis;
                    X->produkJenis = X->produkJenis->next;
                    free(temp);
                    printf("data %s dalam jenis %s sudah berhasil dihapus...", produk, jenis);
                    return;
                }else{
                    temp = X->produkJenis;
                    while(temp != Nil && strcmp(temp->barang, produk) != 0){
                        prev = temp;
                        temp = temp->next;
                    }
                    
                    if(temp == Nil){
                        printf("tidak ada produk %s di dalam jenis %s ", produk, jenis );
                        return;
                    }

                    if(strcmp(temp->barang, produk) == 0){
                        prev->next = temp->next;
                        temp->next = Nil;
                        free(temp);
                        printf("data %s dalam jenis %s sudah berhasil dihapus...", produk, jenis);
                        return;
                    }
                }
            }else{
                printf("tidak ada produk %s di dalam jenis %s ", produk, jenis );
                return;
            }
        }
    }else{
        printf("tidak ada produk didalam list...");
        return;
    }
}

void delJenis(List* P, char* jenis){
    // local variabel
    addressJenis head = (*P).First;
    addressProduk tempProduk;
    addressJenis temp;
    addressJenis prev = Nil;
    // begin
    if((*P).First != Nil){
        while(head != Nil && strcmp(head->Jenis, jenis) != 0){
            prev = head;
            head = head->next_jenis;
        }
        if(head == Nil){
            printf("tidak ada jenis %s yang sesuai di list..", jenis);
            return;
        }
        if(strcmp(head->Jenis, jenis) == 0){
            if(head->produkJenis != Nil){
                while(head->produkJenis != Nil){
                    tempProduk = head->produkJenis;
                    head->produkJenis = head->produkJenis->next;
                    free(tempProduk);
                }
            }
            temp = head;
            head = head->next_jenis;
            if(prev == Nil){
                (*P).First = head;
            }else{
                prev->next_jenis = head;
            }
            free(temp);
            printf("Jenis %s dan semua produknya sudah dihapus...", jenis);
            return;
        }
    }else{
        printf("tidak ada list....");
        return;
    }
}

void addStokProduk(List *P, int stok, char* produk){
    addressProduk barang;
    barang = searchProduk(P, produk);
    if(barang != Nil){
        barang->stok = barang->stok + stok;
        printf("stok sudah ditambahkan");
    }else{
        printf("tidak ada barang di list...");
    }
}

void minusStokProduk(List *P, int stok, char* produk){
    addressProduk barang;
    barang = searchProduk(P, produk);
    if(barang != Nil){
        if(barang->stok == 0){
            printf("tidak ada stok barang");
        }else if(barang->stok < stok){
            printf("Stok tidak mencukupi! Stok saat ini: %d, permintaan: %d\n", barang->stok, stok);
        }else{
            barang->stok = barang->stok - stok;
        }
    }else{
        printf("tidak ada barang di list");
    }
}

void updateHargaProduk(List *P, int harga, char* produk){
    addressProduk barang;
    barang = searchProduk(P, produk);
    if(barang != Nil){
        barang->harga = harga;
    }else{
        printf("Tidak ada barang di list....");
    }
}  

// MODUL NON CONTROL
void printKatalog(List P){
    addressJenis head = P.First;
    addressProduk produk = Nil;
    int i;

    if(head != Nil){
        while(head != Nil){
            i = 1;
            printf("\nJenis: %s\n", head->Jenis);
            printf("=====================================\n");

            produk = head->produkJenis;

            if(produk != Nil){
                printf("%-5s | %-20s | %-5s | %-10s\n", "No", "Barang", "Stok", "Harga");
                printf("----------------------------------------------------------\n");

                while(produk != Nil){
                    printf("%-5d | %-20s | %-5d | %-10d\n", i, produk->barang, produk->stok, produk->harga);
                    i++;
                    produk = produk->next;
                }
            }else{
                printf("Mohon maaf, barang jenis '%s' belum tersedia.\n", head->Jenis);
            }

            head = head->next_jenis;
        }
    }else{
        printf("\nMohon maaf, tidak ada barang di toko...\n");
    }
}

addressProduk searchProduk(List *P, char* barang){
    addressJenis tempJenis = (*P).First;
    addressProduk tempProduk = Nil;
    if(tempJenis!= Nil){
        while(tempJenis != Nil){
            tempProduk = tempJenis->produkJenis;
            while(tempProduk != Nil && strcmp(tempProduk->barang, barang) != 0){
                tempProduk = tempProduk->next;
            }
            if(tempProduk != Nil && strcmp(tempProduk->barang, barang) == 0){
                return tempProduk;
            }
            tempJenis = tempJenis->next_jenis;
        }
    }else{
        printf("tidak ada list....");
        return Nil;
    }
}

int getHargaProduk(List *P, char* barang){
    addressProduk tempProduk;
    tempProduk = searchProduk(P,barang);
    if(tempProduk != Nil){
        return tempProduk->harga;
    }else{
        printf("tidak ada barang di list...");
        return -1;
    }
}

int getStokProduk(List *P, char* barang){
    addressProduk tempProduk;
    tempProduk = searchProduk(P, barang);
    if(tempProduk != Nil){
        return tempProduk->stok;    
    }else{
        printf("tidak ada barang %s di toko...", barang);
        return -1;
    }
}

bool isDuplikatJenis(List *P, char* jenis){
    // (*P) adalah pointer menunjuk ke jenis paling depan
    addressJenis tempJenis;
    tempJenis = (*P).First;
    if(tempJenis != Nil){
        while(tempJenis != Nil && strcmp(tempJenis->Jenis, jenis) != 0 ){
            tempJenis = tempJenis->next_jenis;
        }
        if(tempJenis == Nil){
            return false;
        }else{
            return true;
        }
    }else{
        return false;
    }
}

bool isDuplikatProduk(addressProduk *P, char* produk){
    // (*P) adalah poiner menunjuk ke jenis paling depan
    addressProduk tempProduk = (*P);
    if(tempProduk != Nil){
        while(tempProduk != Nil){
            if(strcmp(tempProduk->barang, produk) == 0){
                return true;
            }
            tempProduk = tempProduk->next;
        }
        if(tempProduk == Nil){
            return false;
        }
    }else{
        return false;
    }
}

// MODUL FILE OPERATION
void loadKatalogFromFile(List *L){
    FILE *fp = fopen("data/katalog.txt", "r");
    if(fp == NULL){
        printf("File katalog.txt tidak ditemukan. Memulai katalog kosong.\n");
        return;
    }

    char line[256];
    addressJenis currentJenis = NULL;

    while(fgets(line, sizeof(line), fp)){
        if(strncmp(line, "Jenis:", 6) == 0){
            char namaJenis[MAX];
            sscanf(line, "Jenis: %[^\n]", namaJenis);

            // Alokasi jenis baru
            addressJenis newJenis = (addressJenis) malloc(sizeof(JENIS));
            strcpy(newJenis->Jenis, namaJenis);
            newJenis->next_jenis = NULL;
            newJenis->produkJenis = NULL;

            // Insert ke list
            if(L->First == NULL){
                L->First = newJenis;
            } else {
                addressJenis temp = L->First;
                while(temp->next_jenis != NULL) temp = temp->next_jenis;
                temp->next_jenis = newJenis;
            }

            currentJenis = newJenis;
        } else if(strncmp(line, "Produk:", 7) == 0){
            char namaProduk[MAX];
            int harga, stok;
            sscanf(line, "Produk: %[^;];Harga:%d;Stok:%d", namaProduk, &harga, &stok);

            // Alokasi produk baru
            addressProduk newProduk = (addressProduk) malloc(sizeof(PRODUK));
            strcpy(newProduk->barang, namaProduk);
            newProduk->harga = harga;
            newProduk->stok = stok;
            newProduk->next = NULL;

            // Masukkan ke produkJenis
            if(currentJenis != NULL){
                if(currentJenis->produkJenis == NULL){
                    currentJenis->produkJenis = newProduk;
                } else {
                    addressProduk tempP = currentJenis->produkJenis;
                    while(tempP->next != NULL) tempP = tempP->next;
                    tempP->next = newProduk;
                }
            }
        }
    }

    fclose(fp);
}

void saveKatalogToFile(List L){
    addressJenis J = Nil;
    addressProduk P = Nil;
    FILE *fp = fopen("katalog.txt", "w");
    if(fp == NULL){
        printf("Gagal membuka file untuk menyimpan katalog.\n");
        return;
    }

    J = L.First;
    while(J != NULL){
        fprintf(fp, "Jenis: %s\n", J->Jenis);

        P = J->produkJenis;
        while(P != NULL){
            fprintf(fp, "Produk: %s;Harga:%d;Stok:%d\n", P->barang, P->harga, P->stok);
            P = P->next;
        }

        J = J->next_jenis;
    }

    fclose(fp);
}

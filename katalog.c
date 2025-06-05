#include "katalog.h"
#include <malloc.h>
#include <string.h>
#include <unistd.h>
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
    int id = 0;

    loadKatalogFromFile(&katalog);
    id = getMaxIdOfProduk(katalog);
    // Begin
    for(;;){
        system("cls");
        printf("KATALOG");
        printf("\n========================");
        printKatalog(katalog);
        printf("========================\n");
        printf("Selamat Datang admin");
        printf("\n1.Tambah Jenis\n2.Hapus Jenis\n3.Tambah Produk\n4.Hapus Produk\n");
        printf("5.Update Harga\n6.Tambah Stok\n7.Kurangi Stok\n8.Keluar");
        printf("\nPilihan anda : ");
        scanf("%d", &decision);
        if(decision == 1){
            system("cls");
            printf("\nStatus Pilihan : 1. Tambah Jenis");
            printf("\nMasukkan Jenis barang baru : ");
            getchar();
            fgets(jenis, sizeof(jenis), stdin);
            jenis[strcspn(jenis, "\n")] = '\0';
            addJenis(&katalog, jenis);
            printf("\nData telah dipdate");
            sleep(2);
        }else if(decision == 2){
            system("cls");
            printf("\nStatus Pilihan : 2. Hapus Jenis");
            printf("\nMasukkan Jenis barang yang akan dihapus : ");
            getchar();
            fgets(jenis, sizeof(jenis), stdin);
            jenis[strcspn(jenis, "\n")] = '\0';
            delJenis(&katalog, jenis);
            printf("\nData telah di update");
            sleep(2);
        }else if(decision == 3){
            subDecision = 0;
            while(subDecision == 0){
            system("cls");
            printf("\nStatus Pilihan : 3. Tambah Produk");
            printf("\nMasukkan Produk yang akan ditambahkan : ");
            getchar();
            fgets(produk, sizeof(produk), stdin);
            produk[strcspn(produk, "\n")] = '\0';
            printf("Masukkan Jenis produk yang akan ditambahkan barangnya : ");
            fgets(jenis, sizeof(jenis), stdin);
            jenis[strcspn(jenis, "\n")] = '\0';
            printf("Masukkan Jumlah stok barang : ");
            scanf("%d", &stok);
            printf("Masukkan Harga barang : ");
            scanf("%d", &harga);

            // Bersihkan sisa newline di buffer sebelum looping ulang, karena scanf tidak menghabiskan newline
            while(getchar() != '\n');
            system("cls");
            printf("Status Tambahan \n");
            printf("%-5s | %-20s | %-5s | %-10s\n", "No", "Barang", "Stok", "Harga");
            printf("----------------------------------------------------------\n");
            printf("%-5d | %-20s | %-5d | %-10d\n", statusInt, produk, stok, harga);
            sleep(1);
            printf("\nApakah data sudah sesuai ?\n1. Ya\n2. Tidak\nMasukkan pilihan anda : ");
            scanf("%d", &subDecision);

            while(getchar() != '\n'); // bersihkan buffer newline lagi
            if(subDecision == 1){
                id++;
                addProduk(&katalog, harga, stok, produk, jenis, id);
                printf("Data telah di update...");
                sleep(2);
            }
    }
        }else if(decision == 4){
            addressProduk temp;
            subDecision = 0;
            while(subDecision == 0){
                system("cls");
                printf("\nStatus Pilihan : 4. Hapus Produk");
                printf("\nMasukkan Jenis dari produk yang akan dihapus : ");
                getchar();
                fgets(jenis, sizeof(jenis), stdin);
                jenis[strcspn(jenis, "\n")] = '\0'; 
                printf("Masukkan Produk yang akan dihapus : ");
                fgets(produk, sizeof(produk), stdin);
                produk[strcspn(produk, "\n")] = '\0'; 
                temp = searchProduk(&katalog, produk);
                if(temp != Nil){
                    temp = searchProduk(&katalog, produk);
                    if(temp != Nil){
                        printf("Data %s ditemukan di kategori %s", temp->barang, jenis);
                        printf("\nApakah anda yakin ingin menghapus ? \n1.Ya\n2.tidak\nMasukkan pilihan : ");
                        scanf("%d", &subDecision);
                        while(getchar() != '\n');
                        if(subDecision == 1){
                            delProduk(&katalog, produk, jenis);
                        }else{
                            subDecision = 0;
                        }
                    }else{
                        printf("data tidak ada di list");
                        sleep(1);
                    }

                }else{
                    printf("produk tidak ditemukan..");
                }
            }
        }else if(decision == 5){
            int temp;
            addressProduk P;
            subDecision = 0;
            while(subDecision == 0){
                system("cls");
                printf("\nStatus Pilihan : 5. Update Harga");
                printf("\nMasukkan produk yang akan diganti harganya : ");
                getchar();
                fgets(produk, sizeof(produk), stdin);
                produk[strcspn(produk, "\n")] = '\0'; 
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
                getchar();
                fgets(produk, sizeof(produk), stdin);
                produk[strcspn(produk, "\n")] = '\0'; 
                addressProduk P = searchProduk(&katalog, produk);
                if(P != Nil){
                    printf("Produk ditemukan: %s\nStok saat ini: %d\n", P->barang, P->stok);
                    printf("Masukkan jumlah stok yang ingin ditambahkan: ");
                    scanf("%d", &stok);
                    addStokProduk(&katalog, stok, produk);
                    printf("\nData telah diupdate");
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
                getchar();
                fgets(produk, sizeof(produk), stdin);
                produk[strcspn(produk, "\n")] = '\0'; 
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
    system("cls");
    userPrintKatalogByKategori(katalog);
}

// MODUL POV USER

// KONSTRUKTOR 
addressProduk alokasi_Produk(int harga, int stok, char* barang, int id){
    addressProduk P = (addressProduk)malloc(sizeof(PRODUK));
    if(P != Nil){
        strcpy(P->barang, barang);
        P->stok = stok;
        P->harga = harga;
        P->next = Nil;
        P->id = id;
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
void addProduk(List *P, int harga, int stok, char* barang, char* jenis, int id){
    // (*P) akan selalu menunjuk ke depan jenis katalog
    addressProduk X = alokasi_Produk(harga, stok, barang, id);
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
            duplikat = isDuplikatProduk(temp, barang);
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

bool isDuplikatProduk(addressProduk P, char* produk){
    // (*P) adalah poiner menunjuk ke jenis paling depan
    addressProduk tempProduk = P;
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

void userPrintKatalogByKategori(List P){
    char jenis[MAX];
    addressJenis kategori = Nil;
    addressProduk produk = Nil;
    addressJenis temp = Nil;
    int i;
    char choice;

    for(;;){
        i = 1;
        temp = P.First;
        kategori = P.First;
        printf("============================\n");
        printf("%-10s | %-20s\n", "No", "Jenis");
        printf("============================\n");
        while(temp != Nil){
            printf("%-5d | %-20s\n", i, temp->Jenis);
            temp = temp->next_jenis;
            i++;
        }
        printf("\nmasukkan kategori barang : ");
        getchar();
        fgets(jenis, sizeof(jenis), stdin);
        jenis[strcspn(jenis, "\n")] = '\0';
        system("cls");
        if(kategori != Nil){
            while(kategori != Nil && strcmp(kategori->Jenis, jenis) != 0){
                kategori = kategori->next_jenis;
            }

            if(kategori == Nil){
                printf("tidak ada sebuah jenis yang sesuai....");
                return;
            }

            if(strcmp(kategori->Jenis, jenis) == 0){
                produk = kategori->produkJenis;
                printf("Jenis : %s\n", jenis);
                printf("%-5s | %-20s | %-5s | %-10s\n", "No", "Barang", "Stok", "Harga");
                printf("----------------------------------------------------------\n");
                i = 1;
                while(produk != Nil){
                    printf("%-5d | %-20s | %-5d | %-10d\n", i, produk->barang, produk->stok, produk->harga);
                    produk = produk->next;
                    i++;
                }
            }
        }else{
            printf("belum ada kategori yang ditambahkan di toko ini....");
            sleep(2);
        }
        printf("\n\n1.kembali\n2.beli barang\nMasukkan pilihan anda : ");
        scanf("%c", &choice);
        if(choice == '1'){
            system("cls");    
        }else if(choice == '2'){
            printf("modul pembelian...");
            break;
        }
    }
    return;
    
}

int getMaxIdOfProduk(List P){
    addressJenis tempJenis = P.First;
    addressProduk tempProduk;
    int tempId = 0;

    if(tempJenis != Nil){
        while(tempJenis != Nil){
            tempProduk = tempJenis->produkJenis;
            if(tempProduk != Nil){
                while(tempProduk != Nil){
                    if(tempProduk->id > tempId){
                        tempId = tempProduk->id;
                    }
                    tempProduk = tempProduk->next;
                }
            }
            tempJenis = tempJenis->next_jenis;
        }
    }else{
        printf("tidak ada data jenis di toko");
        return -1;
    }
    return tempId;
}

// MODUL FILE OPERATION
void saveKatalogToFile(List L){
    addressProduk produk = Nil;
    addressJenis jenis = Nil;
    FILE *fp = fopen("id_katalog.txt", "w");
    if(fp == Nil){
        printf("Gagal membuka file untuk menyimpan katalog.\n");
        return;
    }
    
    jenis = L.First;
    if(jenis != Nil){
        while(jenis != Nil){
            fprintf(fp, "Jenis: %s\n", jenis->Jenis);
            produk = jenis->produkJenis;
            while(produk != Nil){
                // id;produk;jenis;harga;stok
                fprintf(fp, "%d; %s; %s; %d; %d\n", produk->id, produk->barang, jenis->Jenis, produk->harga, produk->stok);
                produk = produk->next;
            }
            jenis = jenis->next_jenis;
        }
    }else{
        printf("tidak ada node");
    }

    fclose(fp);
}
   
void loadKatalogFromFile(List *L){
    char line[256];
    addressJenis tempJenis = Nil;
    addressJenis nodeJenis = Nil;
    addressProduk tempProduk = Nil;
    addressProduk nodeProduk = Nil;
    int id, harga, stok;
    char namaProduk[MAX], jenis[MAX];

    FILE *fp = fopen("id_katalog.txt", "r");
    if(fp == Nil){
        printf("File id_katalog.txt tidak ditemukan. Memulai katalog kosong.\n");
        return;
    }

    while(fgets(line, sizeof(line), fp)){
        if(strncmp(line, "Jenis:", 6) == 0){
            sscanf(line, "Jenis: %[^\n]", jenis);

            // Cek apakah jenis sudah ada
            tempJenis = (*L).First;
            while(tempJenis != Nil && strcmp(tempJenis->Jenis, jenis) != 0){
                tempJenis = tempJenis->next_jenis;
            }

            // Jika belum ada, alokasi dan tambahkan ke list
            if(tempJenis == Nil){
                nodeJenis = alokasi_Jenis(jenis);
                if(nodeJenis != Nil){
                    if((*L).First == Nil){
                        (*L).First = nodeJenis;
                    }else{
                        tempJenis = (*L).First;
                        while(tempJenis->next_jenis != Nil){
                            tempJenis = tempJenis->next_jenis;
                        }
                        tempJenis->next_jenis = nodeJenis;
                    }
                    tempJenis = nodeJenis; // set sebagai jenis aktif
                }else{
                    printf("Alokasi gagal untuk jenis '%s'\n", jenis);
                    continue;
                }
            }
        }else if(strlen(line) > 1){
            sscanf(line, "%d; %[^;]; %[^;]; %d; %d", &id, namaProduk, jenis, &harga, &stok);
            nodeProduk = alokasi_Produk(harga, stok, namaProduk, id);
            if(nodeProduk != Nil){
                if(tempJenis != Nil){
                    if(tempJenis->produkJenis == Nil){
                        tempJenis->produkJenis = nodeProduk;
                    }else{
                        tempProduk = tempJenis->produkJenis;
                        while(tempProduk->next != Nil){
                            tempProduk = tempProduk->next;
                        }
                        tempProduk->next = nodeProduk;
                    }
                }else{
                    printf("Jenis belum diinisialisasi saat menambahkan produk.\n");
                }
            }else{
                printf("Alokasi gagal untuk produk '%s'\n", namaProduk);
            }
        }
    }

    fclose(fp);
}
   

// if(nodeJenis != Nil){
//             if(tempJenis != Nil){
//                 booleanJenis = isDuplikatJenis(L, jenis);
//                 if(booleanJenis == false){
//                     while(tempJenis->next_jenis != Nil){
//                         tempJenis = tempJenis->next_jenis;
//                     }
//                     tempJenis->next_jenis = nodeJenis;
//                     tempProduk = nodeJenis->produkJenis;
//                     if(tempProduk != Nil){
//                         while(tempProduk->next != Nil){
//                             tempProduk = tempProduk->next;
//                         }
//                         tempProduk->next = nodeProduk;
//                     }else{
//                         nodeJenis->produkJenis = nodeProduk;
//                     }
//                 }else{
//                     free(nodeJenis); 
//                     while(strcmp(tempJenis->Jenis, jenis) != 0){
//                         tempJenis = tempJenis->next_jenis;
//                     }
//                     tempProduk = tempJenis->produkJenis;
//                     if(tempJenis->produkJenis != Nil){
//                         while(tempProduk->next != Nil){
//                             tempProduk = tempProduk->next;
//                         }
//                         tempProduk->next = nodeProduk;
//                     }else{
//                         tempJenis->produkJenis = nodeProduk;
//                     }
//                 }
//             }else{
//                 (*L).First = nodeJenis;
//                 nodeJenis->produkJenis = nodeProduk;
//             }
//         }else{
//             printf("alokasi gagal...");
//         }
//     }
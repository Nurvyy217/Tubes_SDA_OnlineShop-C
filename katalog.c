#include "katalog.h"
#include <malloc.h>
#include <string.h>


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
            while(temp->next != Nil && strcmp(temp->barang, barang) != 0){
                temp = temp->next;
            }

            if(strcmp(temp->barang, barang) == 0){
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
    if(X != Nil){
        if((*P).First != Nil){
            while(head->next_jenis != Nil && strcmp(head->Jenis, Jenis) != 0){
                head = head->next_jenis;
            }
            if(head->next_jenis == Nil){
                head->next_jenis = X;
            }else if(strcmp(head->Jenis, Jenis) == 0){
                printf("Sudah ada jenis barang yang sama....");
                free(X);
                return;
            }
        }else{
            (*P).First = X;
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
            printf("\n=====================================\n");
            printf("Jenis: %s\n", head->Jenis);
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
        printf("Mohon maaf, tidak ada barang di toko...\n");
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


#include "katalog.h"
#include <malloc.h>
#include <string.h>


// konstruktor 
addressProduk alokasi_Produk(int harga, int jumlah, char* barang){
    addressProduk P = (addressProduk)malloc(sizeof(PRODUK));
    if(P != Nil){
        strcpy(P->barang, barang);
        P->jumlah = jumlah;
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

// Modul CONTROL
void addProduk(List *P, int harga, int jumlah, char* barang, char* jenis){
    // (*P) akan selalu menunjuk ke depan jenis katalog
    addressProduk X = alokasi_Produk(harga, jumlah, barang);
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
                print("Sudah ada jenis barang yang sama....");
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


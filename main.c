/* Saya Nuansa Bening Aura Jelita mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah
Algoritma dan Pemrograman II untuk keberkahanNya maka saya tidak
melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin. */

#include "header.h"

int main()
{
    system("cls"); // membersihkan layar konsol

    char pita[501];  // deklarasi pita untuk menyimpan masukan perintah dari user
    int selesai = 0; // tanda untuk menentukan kapan program selesai
    ANIMATED();      // memanggil prosedur ANIMATED untuk animasi tampilan awal

    while (selesai == 0) // looping utama, berjalan hingga selesai == 1
    {
        printf("\n[DBMS BENING] >"); // menampilkan prompt untuk input user
        scanf(" %500[^\n]s", pita);  // meminta masukkan perintah dari user

        // memeriksa apakah user menginput "jangan lupa bahagia hari ini;"
        if (strcmp(pita, "jangan lupa bahagia hari ini;") == 0)
        {
            // jika iya, maka itu artinya user selesai menggunakan dbmsnya
            // menampilkan pesan keluar dengan warna kuning
            printf(YELLOW_COLOR "Yippeeee! Sampai Berjumpa Lagi [^._.^]\n" RESET_COLOR);
            selesai = 1; // set tanda selesai menjadi 1 untuk keluar dari looping
        }
        else
        {
            // jika tidak, maka:
            JALANKAN(pita); // memanggil prosedur JALANKAN dengan masukan user berupa perintah yang ada
        }
    }
}
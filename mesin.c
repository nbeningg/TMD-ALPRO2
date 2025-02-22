/* Saya Nuansa Bening Aura Jelita mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah
Algoritma dan Pemrograman II untuk keberkahanNya maka saya tidak
melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin. */

#include "header.h"

data proyek[300]; // tabel pertama untuk menyimpan data proyek/program yang akan di kerjakan
data tim[300];    // tabel kedua untuk menyimpan data tim yang mengikuti proyek/progam tabel pertama

int idx;                                                        // untuk index dari karakter terakhir pada kata
int wlen;                                                       // untuk word length
char cw[100];                                                   //  untuk current word
int ip;                                                         // untuk jumlah data proyek
int it;                                                         // untuk jumlah data tim
char idProyek[100], namaProyek[100], lokasi[100], tanggal[100]; // untuk menyimpan data proyek/program
char idTim[100], namaTim[100], jumlah[100], fk[100];            // untuk menyimpan data tim

// untuk menyimpan kata terpanjang dari setiap kolom pada data proyek dan tim
int idP_max = 0, kp1_max = 0, kp2_max = 0, kp3_max = 0; // untuk data proyek
int idT_max = 0, kt1_max = 0, kt2_max = 0, kt3_max = 0; // untuk data tim

// definisi prosedur untuk menunggu waktu selama x detik
void WAIT(float x)
{
    time_t start, current;
    time(&start); // menyimpan waktu mulai
    do
    {
        time(&current); // menyimpan waktu saat ini
    } while (difftime(current, start) < x); // menghitung perbedaan waktu dan menunggu hingga mencapai x detik
}

// definisi prosedur untuk animasi tampilan awal
void ANIMATED()
{
    // menyimpan pesan-pesan yang akan di tampilkan dalam array string
    char *pesan[9];
    pesan[0] = "+===========================================+";
    pesan[1] = "|>-----------------------------------------<|";
    pesan[2] = "|> Selamat Datang di DBMS Edukasi [bening] <|";
    pesan[3] = "|>           Server version: 1.0           <|";
    pesan[4] = "|>           Commands end with ;           <|";
    pesan[5] = "|>          Type 'HELP;' for help          <|";
    pesan[6] = "|>       Copyright (c) 2024, nbening       <|";
    pesan[7] = "|>-----------------------------------------<|";
    pesan[8] = "+===========================================+";

    // menampilkan pesan dengan animasi
    for (int i = 0; i < 9; i++)
    {
        printf("%s\n", pesan[i]);
        WAIT(1); // menunggu 1 detik sebelum menampilkan baris berikutnya dengan memanggil prosedur WAIT
    }
}

// definisi fungsi untuk memeriksa end of process
int EOP(char str[])
{
    // memeriksa apakah karakter saat ini merupakan simbol akhir pita berupa titik koma
    if (str[idx] == ';')
        return 1; // mengembalikan 1 jika karakter saat ini adalah titik koma
    else
        return 0; // mengembalikan 0 jika karakter saat ini bukan titik koma
}

// definisi prosedur untuk memulai mesin kata
void START(char str[])
{
    // inisialisasi index dan panjang kata
    idx = 0;
    wlen = 0;

    // jika karakter dalam index merupakan spasi, index akan terus maju
    while (str[idx] == ' ')
    {
        idx++;
    }

    // jika masukan berupa karakter selain SPASI dan EOP, kata diatur ke variabel global
    while ((str[idx] != ' ') && (EOP(str) == 0))
    {
        cw[wlen] = str[idx];
        wlen++;
        idx++;
    }

    cw[wlen] = '\0'; // jangan lupa di NULL in
}

// definisi prosedur untuk mereset atau mengosongkan kata yang dibaca dalam mesin kata
void RESET()
{
    // inisialisasi panjang kata dan kata saat ini agar NULL
    wlen = 0;
    cw[wlen] = '\0';
}

// definisi prosedur untuk memajukan kata
void INC(char str[])
{
    // inisialisasi ulang panjang kata
    wlen = 0;

    // jika karakter dalam pita adalah spasi, index akan terus maju
    while (str[idx] == ' ')
    {
        idx++;
    }

    // jika masukan berupa karakter selain SPASI dan EOP, kata diatur ke variabel global
    while ((str[idx] != ' ') && (EOP(str) == 0))
    {
        cw[wlen] = str[idx];
        wlen++;
        idx++;
    }

    cw[wlen] = '\0'; // jangan lupa di NULL in
}

// definisi fungsi untuk mendapatkan panjang kata saat ini
int GETLEN()
{
    return wlen;
}

// definisi fungsi untuk mendapatkan current word
char *GETCW()
{
    return cw;
}

// definisi fungsi untuk menghitung jumlah kata dalam satu perintah
int HITUNG_KATA(char pita[])
{
    int jumlah = 0; // inisialisasi untuk menghitung jumlah kata
    START(pita);    // memulai mesin kata

    while (EOP(pita) == 0) // looping selama belum mencapai akhir pita
    {
        jumlah++;  // menambah jumlah kata setiap kali menemukan sebuah kata
        INC(pita); // memajukan pita ke kata berikutnya
    }

    // memeriksa apakah masih ada kata yang belum dihitung setelah looping selesai
    if (GETLEN() > 0)
    {
        jumlah++; // menambah jumlah kata jika masih ada kata yang belum dihitung
    }

    return jumlah; // mengembalikan jumlah total kata
}

// definisi prosedur untuk menampilkan tampilan bantuan
void HELP()
{
    printf("Additional commands specific to DBMS BENING:\n");
    printf("Note: Commands must be first on line and end with ';'\n");
    printf("INPUT tProyek [id_proyek] [nama_proyek] [lokasi] [tanggal];     => Input a project into tProyek table.\n");
    printf("INPUT tTim [id_tim] [nama_tim] [jumlah] [id_proyek];            => Input a team into tTim table associated with id_proyek.\n");
    printf("UPDATE tProyek [id_proyek] [nama_proyek] [lokasi] [tanggal];    => Update details of a project in tProyek table.\n");
    printf("UPDATE tTim [id_tim] [nama_tim] [jumlah] [id_proyek];           => Update details of a team in tTim table associated with id_proyek.\n");
    printf("DELETE tProyek [id_proyek];                                     => Delete a project from tProyek table.\n");
    printf("DELETE tTim [id_tim];                                           => Delete a team from tTim table associated with id_proyek.\n");
    printf("SHOW tProyek;                                                   => Show all records from tProyek table.\n");
    printf("SHOW tTim;                                                      => Show all records from tTim table.\n");
    printf("SHOW [table1] [table2];                                         => Show all records from multiple tables, table1 and table2.\n");
}

// definisi prosedur untuk sorting secara ascending berdasarkan id pada data proyek
void SORT_PROYEK(data proyek[], int n)
{
    int i, j;
    data temp; // variabel sementara untuk pertukaran

    // looping untuk setiap isi dalam data proyek (kecuali isi terakhir)
    for (i = 0; i < n - 1; i++)
    {
        // looping untuk isi setelah isi ke-i hingga isi terakhir
        for (j = i + 1; j < n; j++)
        {
            // membandingkan ID proyek ke-i dengan ID proyek ke-j
            if (strcmp(proyek[i].id, proyek[j].id) > 0)
            {
                // melakukan pertukaran jika ID proyek ke-i lebih besar dari ID proyek ke-j
                temp = proyek[i];
                proyek[i] = proyek[j];
                proyek[j] = temp;
            }
        }
    }
}

// definisi prosedur untuk sorting secara ascending berdasarkan id pada tim
void SORT_TIM(data tim[], int n)
{
    int i, j;
    data temp; // variabel sementara untuk pertukaran

    // looping untuk setiap isi dalam data tim (kecuali isi terakhir)
    for (i = 0; i < n - 1; i++)
    {
        // looping untuk isi setelah isi ke-i hingga isi terakhir
        for (j = i + 1; j < n; j++)
        {
            // membandingkan ID tim ke-i dengan ID tim ke-j
            if (strcmp(tim[i].id, tim[j].id) > 0)
            {
                // melakukan pertukaran jika ID tim ke-i lebih besar dari ID tim ke-j
                temp = tim[i];
                tim[i] = tim[j];
                tim[j] = temp;
            }
        }
    }
}

// definisi prosedur untuk melakukan pembacaan data pada file dat
void READ()
{
    FILE *fproyek; // deklarasi pointer file untuk data proyek
    ip = 0;        // Inisialisasi indeks proyek
    it = 0;        // Inisialisasi indeks tim

    fproyek = fopen("tProyek.dat", "r"); // buka file tProyek.dat untuk dibaca

    // membaca isi baris pertama data proyek
    int returnValP = fscanf(fproyek, "%s %s %s %s", proyek[ip].id, proyek[ip].kolom1, proyek[ip].kolom2, proyek[ip].kolom3);
    if (strcmp(proyek[ip].id, "####") == 0 || returnValP == EOF)
        ;
    // jika ID proyek pertama adalah #### atau mencapai EOF, tidak melakukan apa-apa (harusnya printf file kosong)
    else
    {
        // looping untuk membaca data proyek sampai menemukan ID #### atau mencapai EOF
        while (strcmp(proyek[ip].id, "####") != 0)
        {
            ip++;
            fscanf(fproyek, "%s %s %s %s", proyek[ip].id, proyek[ip].kolom1, proyek[ip].kolom2, proyek[ip].kolom3);
        }
    }
    fclose(fproyek); // menutup file tProyek.dat

    FILE *ftim;                    // deklarasi pointer file untuk data tim
    ftim = fopen("tTim.dat", "r"); // buka file tTim.dat untuk dibaca

    // membaca isi baris pertama data tim
    int returnValT = fscanf(ftim, "%s %s %s %s", tim[it].id, tim[it].kolom1, tim[it].kolom2, tim[it].kolom3);
    if (strcmp(tim[it].id, "####") == 0 || returnValT == EOF)
        ;
    // jika ID tim pertama adalah #### atau mencapai EOF, tidak melakukan apa-apa (harusnya printf file kosong)
    else
    {
        // looping untuk membaca data tim sampai menemukan ID #### atau mencapai EOF
        while (strcmp(tim[it].id, "####") != 0)
        {
            it++;
            fscanf(ftim, "%s %s %s %s", tim[it].id, tim[it].kolom1, tim[it].kolom2, tim[it].kolom3);
        }
    }
    fclose(ftim); // menutup file tTim.dat
}

// definisi prosedur untuk untuk melakukan simpan data ke file dat
void WRITE()
{
    FILE *fproyek; // deklarasi pointer file untuk data proyek
    FILE *ftim;    // deklarasi pointer file untuk data tim

    // melakukan sorting sebelum meyimpan ke file
    SORT_PROYEK(proyek, ip); // sorting untuk data proyek dengan memanggil prosedur SORT_PROYEK
    SORT_TIM(tim, it);       // sorting untuk data tim dengan memanggil prosedur SORT_TIM

    fproyek = fopen("tProyek.dat", "w"); // membuka file tProyek.dat untuk ditulis/disimpan
    for (int i = 0; i < ip; i++)
    {
        // menulis/menyimpan setiap baris data proyek ke file tProyek.dat
        fprintf(fproyek, "%s %s %s %s\n", proyek[i].id, proyek[i].kolom1, proyek[i].kolom2, proyek[i].kolom3);
    }
    fprintf(fproyek, "%s %s %s %s\n", "####", "####", "####", "####"); // menulis penanda akhir data
    fclose(fproyek);                                                   // menutup file tProyek.dat

    ftim = fopen("tTim.dat", "w"); // membuka file tTim.dat untuk ditulis/disimpan
    for (int i = 0; i < it; i++)
    {
        // menulis/menyimpan setiap baris data tim ke file tTim.dat
        fprintf(ftim, "%s %s %s %s\n", tim[i].id, tim[i].kolom1, tim[i].kolom2, tim[i].kolom3);
    }
    fprintf(ftim, "%s %s %s %s\n", "####", "####", "####", "####"); // menulis penanda akhir data
    fclose(ftim);                                                   // menutup file tTim.dat
}

// definisi fungsi untuk primary key pada data proyek
int PK_P()
{
    int ketemu = 0; // tanda primary key untuk ditemukan/tidak (0 tidak ditemukan, 1 sebaliknya)
    int i = 0;

    // looping untuk mencari idProyek dalam data proyek
    while (i < ip && ketemu == 0)
    {
        // memeriksa apakah idProyek sama seperti proyek[i].id (yang ada di dalam data)
        if (strcmp(idProyek, proyek[i].id) == 0)
        {
            ketemu = 1; // set nilai ketemu menjadi 1 jika sama (ditemukan)
        }
        i++;
    }
    return ketemu; // mengembalikan nilai ketemu
}

// definisi fungsi untuk primary key pada data tim
int PK_T()
{
    int ketemu = 0; // tanda untuk primary key ditemukan/tidak (0 tidak ditemukan, 1 sebaliknya)
    int i = 0;

    // looping untuk mencari idTim dalam data tim
    while (i < it && ketemu == 0)
    {
        // memeriksa apakah idTim sama seperti tim[i].id (yang ada di dalam data)
        if (strcmp(idTim, tim[i].id) == 0)
        {
            ketemu = 1; // set nilai ketemu menjadi 1 jika sama (ditemukan)
        }
        i++;
    }
    return ketemu; // mengembalikan nilai ketemu
}

// definisi fungsi untuk cek apakah id proyek bisa ditambahkan menjadi foreign key
int ADD_FK()
{
    int ketemu = 0; // untuk menandakan apakah fk dapat ditambahkan sebagai foreign key (0 tidak ditemukan, 1 sebaliknya)
    int i = 0;

    // loop untuk mencari fk dalam data proyek
    while (i < ip && ketemu == 0)
    {
        // memeriksa apakah fk sama seperti proyek[i].id
        if (strcmp(fk, proyek[i].id) == 0)
        {
            ketemu = 1; // set nilai ketemu menjadi 1 jika sama (ditemukan)
        }
        i++;
    }
    return ketemu; // mengembalikan nilai ketemu
}

// definisi fungsi untuk cek apakah id proyek sedang menjadi foreign key
int CHECK_FK()
{
    int ketemu = 0; // tanda untuk foreign key ditemukan/tidak (0 tidak ditemukan, 1 sebaliknya)
    int i = 0;

    // looping untuk mencari idProyek dalam kolom 3 dari data tim
    while (i < it && ketemu == 0)
    {
        // memeriksa apakah idProyek sama seperti tim[i].kolom3 (yang ada di dalam data)
        if (strcmp(idProyek, tim[i].kolom3) == 0)
        {
            ketemu = 1; // set nilai ketemu menjadi 1 jika sama (ditemukan)
        }
        i++;
    }
    return ketemu; // mengembalikan nilai ketemu
}

// definisi prosedur untuk menampilkan data proyek setelah di input/update
void TAMPILPROYEK1()
{
    READ(); // memanggil prosedur READ untuk membaca data proyek

    idP_max = 0, kp1_max = 0, kp2_max = 0, kp3_max = 0;

    // menghitung panjang maksimum untuk setiap kolom
    for (int i = 0; i < ip; i++)
    {
        // memeriksa apakah idProyek sama dengan proyek[i].id
        if (strcmp(proyek[i].id, idProyek) == 0)
        {
            // Menghitung panjang setiap kolom proyek[i]
            int pro1 = strlen(proyek[i].id);
            int pro2 = strlen(proyek[i].kolom1);
            int pro3 = strlen(proyek[i].kolom2);
            int pro4 = strlen(proyek[i].kolom3);

            // memperbarui panjang maksimum untuk setiap kolom
            if (pro1 > idP_max)
                idP_max = pro1;
            if (pro2 > kp1_max)
                kp1_max = pro2;
            if (pro3 > kp2_max)
                kp2_max = pro3;
            if (pro4 > kp3_max)
                kp3_max = pro4;
        }
    }

    // menampilkan header dengan penyesuaian spasi
    printf("ID PROYEK   ");
    for (int i = 0; i < idP_max - 9; i++)
        printf(" ");
    printf("NAMA PROYEK   ");
    for (int i = 0; i < kp1_max - 11; i++)
        printf(" ");
    printf("LOKASI   ");
    for (int i = 0; i < kp2_max - 6; i++)
        printf(" ");
    printf("TANGGAL");
    printf("\n");

    // menampilkan hanya data yang dimasukkan/diupdate
    for (int i = 0; i < ip; i++)
    {
        // memeriksa apakah idProyek sama dengan proyek[i].id
        if (strcmp(proyek[i].id, idProyek) == 0)
        {
            // mencetak nilai dari setiap kolom proyek[i], disesuaikan dengan panjang maksimumnya
            printf("%s   ", proyek[i].id); // menampilkan value pertama, berupa id proyek
            if (idP_max > 9)               // proses tampilan spasi jika panjang maksimum lebih dari panjang header
            {
                for (int j = 0; j < idP_max - strlen(proyek[i].id); j++)
                    printf(" ");
            }
            else if (idP_max <= 9) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
            {
                for (int j = 0; j < 9 - strlen(proyek[i].id); j++)
                    printf(" ");
            }
            printf("%s   ", proyek[i].kolom1); // menampilkan value kedua, berupa nama proyek
            if (kp1_max > 11)                  // proses tampilan spasi jika panjang maksimum lebih dari panjang header
            {
                for (int j = 0; j < kp1_max - strlen(proyek[i].kolom1); j++)
                    printf(" ");
            }
            else if (kp1_max <= 11) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
            {
                for (int j = 0; j < 11 - strlen(proyek[i].kolom1); j++)
                    printf(" ");
            }
            printf("%s   ", proyek[i].kolom2); // menampilkan value ketiga, beruapa lokasi
            if (kp2_max > 6)                   // proses tampilan spasi jika panjang maksimum lebih dari panjang header
            {
                for (int j = 0; j < kp2_max - strlen(proyek[i].kolom2); j++)
                    printf(" ");
            }
            else if (kp2_max <= 6) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
            {
                for (int j = 0; j < 6 - strlen(proyek[i].kolom2); j++)
                    printf(" ");
            }
            printf("%s", proyek[i].kolom3); // menampilkan value keempat, berupa tanggal
            printf("\n");
        }
    }
}

// definisi prosedur untuk menampilkan data tim setelah di input/update
void TAMPILTIM1()
{
    READ(); // memanggil prosedur READ untuk membaca data tim

    idT_max = 0, kt1_max = 0, kt2_max = 0, kt3_max = 0;

    // menghitung panjang maksimum untuk setiap kolom
    for (int i = 0; i < it; i++)
    {
        // memeriksa apakah idTim sama dengan tim[i].id
        if (strcmp(tim[i].id, idTim) == 0)
        {
            // Menghitung panjang setiap kolom tim[i]
            int ti1 = strlen(tim[i].id);
            int ti2 = strlen(tim[i].kolom1);
            int ti3 = strlen(tim[i].kolom2);
            int ti4 = strlen(tim[i].kolom3);

            // memperbarui panjang maksimum untuk setiap kolom
            if (ti1 > idT_max)
                idT_max = ti1;
            if (ti2 > kt1_max)
                kt1_max = ti2;
            if (ti3 > kt2_max)
                kt2_max = ti3;
            if (ti4 > kt3_max)
                kt3_max = ti4;
        }
    }

    // menampilkan header dengan penyesuaian spasi
    printf("ID TIM   ");
    for (int i = 0; i < idT_max - 6; i++)
        printf(" ");
    printf("NAMA TIM   ");
    for (int i = 0; i < kt1_max - 8; i++)
        printf(" ");
    printf("JUMLAH ANGGOTA   ");
    for (int i = 0; i < kt2_max - 14; i++)
        printf(" ");
    printf("ID PROYEK   ");
    for (int i = 0; i < kt3_max - 9; i++)
        printf(" ");
    printf("\n");

    // menampilkan hanya data yang dimasukkan/diupdate
    for (int i = 0; i < it; i++)
    {
        // memeriksa apakah idTim sama dengan tim[i].id
        if (strcmp(tim[i].id, idTim) == 0)
        {
            // mencetak nilai dari setiap kolom tim[i], disesuaikan dengan panjang maksimum
            printf("%s   ", tim[i].id); // menampilkan value pertama, berupa id proyek
            if (idT_max > 6)            // proses tampilan spasi jika panjang maksimum lebih dari panjang header
            {
                for (int j = 0; j < idT_max - strlen(tim[i].id); j++)
                    printf(" ");
            }
            else if (idT_max <= 6) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
            {
                for (int j = 0; j < 6 - strlen(tim[i].id); j++)
                    printf(" ");
            }
            printf("%s   ", tim[i].kolom1); // menampilkan value kedua, berupa nama tim
            if (kt1_max > 8)                // proses tampilan spasi jika panjang maksimum lebih dari panjang header
            {
                for (int j = 0; j < kt1_max - strlen(tim[i].kolom1); j++)
                    printf(" ");
            }
            else if (kt1_max <= 8) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
            {
                for (int j = 0; j < 8 - strlen(tim[i].kolom1); j++)
                    printf(" ");
            }
            printf("%s   ", tim[i].kolom2); // menampilkan value ketiga, beruapa jumlah anggota tim
            if (kt2_max > 14)               // proses tampilan spasi jika panjang maksimum lebih dari panjang header
            {
                for (int j = 0; j < kt2_max - strlen(tim[i].kolom2); j++)
                    printf(" ");
            }
            else if (kt2_max <= 14) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
            {
                for (int j = 0; j < 14 - strlen(tim[i].kolom2); j++)
                    printf(" ");
            }
            printf("%s   ", tim[i].kolom3); // menampilkan value keempat, berupa id proyek (foreign key)
            printf("\n");
        }
    }
}

// definisi prosedur untuk menginput/menambahkan data baru pada data proyek dan tim
void INPUT(char tape[])
{
    int PK = 0, FK = 0;            // variabel untuk mengecek primary key dan foreign key
    int jKata = HITUNG_KATA(tape); // menghitung jumlah kata dalam satu perintah

    READ(); // membaca data proyek dan tim dari file

    START(tape); // memulai mesin kata

    // memerika apakah perintah INPUT benar atau tidak
    if (strcmp(GETCW(), "INPUT") == 0)
    {
        INC(tape); // maju ke kata berikutnya

        // memerika jumlah kata dalam satu perintah
        // perintah input memiliki jumlah 6 kata --> INPUT file [value1] [value2] [value3] [value4]
        if (jKata < 6) // jika kata kurang dari 6, maka:
        {
            // tampilkan pesan error seperti dibawah ini
            printf(RED_COLOR "Error: Input tidak dapat diterima karena jumlah kata kurang dari batas yang diizinkan.\n" RESET_COLOR);
        }
        else if (jKata > 6) // jika kata lebih dari 6, maka:
        {
            // tampilkan pesan error seperti dibawah ini
            printf(RED_COLOR "Error: Input tidak dapat diterima karena jumlah kata melebihi batas yang diizinkan.\n" RESET_COLOR);
        }
        else // jika pas 6, maka:
        {
            if (strcmp(GETCW(), "tProyek") == 0) // memeriksa apakah tabel yang dituju adalah tProyek
            {
                INC(tape);                          // maju ke kata berikutnya
                strcpy(proyek[ip].id, GETCW());     // salin value pertama dari pita ke id proyek
                strcpy(idProyek, GETCW());          // salin value pertama juga dari pita ke idProyek
                INC(tape);                          // maju ke kata berikutnya
                strcpy(proyek[ip].kolom1, GETCW()); // salin value kedua dari pita ke kolom1 proyek
                INC(tape);                          // maju ke kata berikutnya
                strcpy(proyek[ip].kolom2, GETCW()); // salin value ketiga dari pita ke kolom2 proyek
                INC(tape);                          // maju ke kata berikutnya
                strcpy(proyek[ip].kolom3, GETCW()); // salin value keempat dari pita ke kolom3 proyek

                PK = PK_P(); // periksa apakah primary key proyek sudah terdaftar (berupa id)
                if (PK == 0) // jika primay key belum terdaftar, maka:
                {
                    ip++;
                    WRITE(); // data dapat disimpan dengan memanggil prosedur simpan
                    // menampilkan pesan sukses
                    printf(GREEN_COLOR "Success: Data telah berhasil disimpan dalam tProyek.\n\n" RESET_COLOR);
                    TAMPILPROYEK1();
                }
                else // jika primay sudah terdaftar, maka:
                {
                    // tampilkan pesan error seperti dibawah ini
                    printf(RED_COLOR "Error: ID sudah terdaftar di tProyek. Silakan gunakan ID yang berbeda.\n" RESET_COLOR);
                }
            }
            else if (strcmp(GETCW(), "tTim") == 0) // memeriksa apakah tabel yang dituju adalah tTim
            {
                INC(tape);                       // maju ke kata berikutnya
                strcpy(tim[it].id, GETCW());     // salin value pertama dari pita ke id tim
                strcpy(idTim, GETCW());          // salin value pertama juga dari pita ke idTim
                INC(tape);                       // maju ke kata berikutnya
                strcpy(tim[it].kolom1, GETCW()); // salin value kedua dari pita ke kolom1 tim
                INC(tape);                       // maju ke kata berikutnya
                strcpy(tim[it].kolom2, GETCW()); // salin value ketiga dari pita ke kolom2 tim
                INC(tape);                       // maju ke kata berikutnya
                strcpy(tim[it].kolom3, GETCW()); // salin value keempat dari pita ke kolom3 tim
                strcpy(fk, GETCW());             // salin value keempat juga dari pita ke fK (foreign key)

                PK = PK_T(); // periksa apakah primary key tim sudah terdaftar (berupa id)
                if (PK == 0) // jika primay key belum terdaftar, maka:
                {
                    FK = ADD_FK(); // periksa apakah foreign key (berupa id proyek) terdafar dalam data proyek
                    if (FK == 1)   // jika foreign key terdaftar, maka:
                    {
                        it++;
                        WRITE(); // data dapat disimpan dengan memanggil prosedur simpan
                        // menampilkan pesan sukses
                        printf(GREEN_COLOR "Success: Data telah berhasil disimpan dalam tTim.\n\n" RESET_COLOR);
                        TAMPILTIM1();
                    }
                    else // jika foreign key belum terdaftar, maka:
                    {
                        // tampilkan pesan error seperti dibawah ini
                        printf(RED_COLOR "Error: ID_PROYEK yang dimasukkan tidak terdaftar. Silakan pilih ID_PROYEK yang valid dari tProyek.\n" RESET_COLOR);
                    }
                }
                else // jika primary key sudah terdaftar, maka:
                {
                    // tampilkan pesan error seperti dibawah ini
                    printf(RED_COLOR "Error: ID sudah terdaftar di tTim. Silakan gunakan ID yang berbeda.\n" RESET_COLOR);
                }
            }
            else // jika input tabel selain tProyek dan tTim, maka:
            {
                // tampilkan pesan error seperti dibawah ini
                printf(RED_COLOR "Error: Tidak dapat menemukan tabel yang dituju. Pastikan nama tabel yang dimasukkan benar.\n" RESET_COLOR);
            }
        }
    }
}

// definisi prosedur untuk mengupdate/memperbarui value pada data proyek dan tim
void UPDATE(char tape[])
{
    int PK = 0, FK = 0;            // variabel untuk mengecek primary key dan foreign key
    int jKata = HITUNG_KATA(tape); // menghitung jumlah kata dalam satu perintah

    READ(); // membaca data proyek dan tim dari file

    START(tape); // memulai mesin kata

    // memerika apakah perintah UPDATE benar atau tidak
    if (strcmp(GETCW(), "UPDATE") == 0)
    {
        INC(tape); // maju ke kata berikutnya

        // memerika jumlah kata dalam satu perintah
        // perintah update memiliki jumlah 6 kata --> UPDATE file [value1] [value2] [value3] [value4]
        if (jKata < 6) // jika kata kurang dari 6, maka:
        {
            // tampilkan pesan error seperti dibawah ini
            printf(RED_COLOR "Error: Update tidak dapat diterima karena jumlah kata kurang dari batas yang diizinkan.\n" RESET_COLOR);
        }
        else if (jKata > 6) // jika kata lebih dari 6, maka:
        {
            // tampilkan pesan error seperti dibawah ini
            printf(RED_COLOR "Error: Update tidak dapat diterima karena jumlah kata melebihi batas yang diizinkan.\n" RESET_COLOR);
        }
        else // jika pas 6 kata, maka:
        {
            if (strcmp(GETCW(), "tProyek") == 0) // memeriksa apakah tabel yang dituju adalah tProyek
            {
                INC(tape);                   // maju ke kata berikutnya
                strcpy(idProyek, GETCW());   // salin value pertama dari pita ke idProyek
                INC(tape);                   // maju ke kata berikutnya
                strcpy(namaProyek, GETCW()); // salin value kedua dari pita ke namaProyek
                INC(tape);                   // maju ke kata berikutnya
                strcpy(lokasi, GETCW());     // salin value ketiga dari pita ke lokasi
                INC(tape);                   // maju ke kata berikutnya
                strcpy(tanggal, GETCW());    // salin value keempat dari pita ke tanggal

                PK = PK_P(); // periksa apakah primary key proyek sudah terdaftar
                if (PK == 1) // jika primary key sudah terdaftar, maka:
                {
                    // update dapat di lakukan
                    for (int i = 0; i < ip; i++)
                    {
                        if (strcmp(proyek[i].id, idProyek) == 0)
                        {
                            strcpy(proyek[i].kolom1, namaProyek); // update kolom1 proyek, dengan menyalin namaProyek
                            strcpy(proyek[i].kolom2, lokasi);     // update kolom2 proyek, dengan menyalin lokasi
                            strcpy(proyek[i].kolom3, tanggal);    // update kolom3 proyek, dengan menyalin tanggal
                            WRITE();                              // tulis perubahan ke file dengan memanggil prosedur write
                            // tampilkan pesan sukses
                            printf(GREEN_COLOR "Success: Data telah berhasil diupdate dalam tProyek.\n\n" RESET_COLOR);
                            TAMPILPROYEK1();
                        }
                    }
                }
                else // jika primary key belum terdaftar, maka:
                {
                    // tampilkan pesan error seperti dibawah ini
                    printf(RED_COLOR "Error: ID yang dimaksud untuk update tidak terdaftar dalam tProyek. Pastikan ID yang dimasukkan benar.\n" RESET_COLOR);
                }
            }
            else if (strcmp(GETCW(), "tTim") == 0) // memeriksa apakah tabel yang dituju adalah tTim
            {
                INC(tape);                // maju ke kata berikutnya
                strcpy(idTim, GETCW());   // salin value pertama dari pita ke idTim
                INC(tape);                // maju ke kata berikutnya
                strcpy(namaTim, GETCW()); // salin value kedua dari pita ke namaTim
                INC(tape);                // maju ke kata berikutnya
                strcpy(jumlah, GETCW());  // salin value ketiga dari pita ke jumlah
                INC(tape);                // maju ke kata berikutnya
                strcpy(fk, GETCW());      // salin value keempat dari pita ke fk (foreign key)

                PK = PK_T(); // periksa apakah primary key tim sudah terdaftar
                if (PK == 1) // jika primary key sudah terdaftar, maka:
                {
                    FK = ADD_FK(); // periksa apakah foreign key (berupa id proyek) terdafar dalam data proyek
                    if (FK == 1)   // jika foreign key terdaftar, maka:
                    {
                        // update dapat di lakukan
                        for (int i = 0; i < it; i++)
                        {
                            if (strcmp(tim[i].id, idTim) == 0)
                            {
                                strcpy(tim[i].kolom1, namaTim); // update kolom1 tim, dengan menyalin namaTim
                                strcpy(tim[i].kolom2, jumlah);  // update kolom2 tim, dengan menyalin jumlah
                                strcpy(tim[i].kolom3, fk);      // // update kolom3 tim, dengan menyalin fk
                                WRITE();                        // tulis perubahan ke file dengan memanggil prosedur write
                                // tampilkan pesan sukses
                                printf(GREEN_COLOR "Success: Data telah berhasil diupdate dalam tTim.\n\n" RESET_COLOR);
                                TAMPILTIM1();
                            }
                        }
                    }
                    else // jika foreign key belum terdaftar, maka:
                    {
                        // tampilkan pesan error seperti dibawah ini
                        printf(RED_COLOR "Error: ID_PROYEK yang dimasukkan tidak terdaftar. Silakan pilih ID_PROYEK yang valid dari tProyek.\n" RESET_COLOR);
                    }
                }
                else // jika primary key belum terdaftar, maka:
                {
                    // tampilkan pesan error seperti dibawah ini
                    printf(RED_COLOR "Error: ID yang dimaksud untuk update tidak terdaftar dalam tTim. Pastikan ID yang dimasukkan benar.\n" RESET_COLOR);
                }
            }
            else // jika update tabel selain tProyek dan tTim, maka:
            {
                // tampilkan pesan error seperti dibawah ini
                printf(RED_COLOR "Error: Tidak dapat menemukan tabel yang dituju. Pastikan nama tabel yang dimasukkan benar.\n" RESET_COLOR);
            }
        }
    }
}

// definisi prosedur untuk delete/menghapus data pada data proyek dan tim
void DELETE(char tape[])
{
    int PK = 0, FK = 0;            // variabel untuk mengecek primary key dan foreign key
    int jKata = HITUNG_KATA(tape); // menghitung jumlah kata dalam satu perintah

    READ(); // membaca data proyek dan tim dari file

    START(tape); // memulai mesin kata

    // memeriksa apakah perintah DELETE benar atau tidak
    if (strcmp(GETCW(), "DELETE") == 0)
    {
        INC(tape); // maju ke kata berikutnya

        // memerika jumlah kata dalam satu perintah
        // perintah update memiliki jumlah 3 kata --> DELETE file [value1]
        if (jKata < 3) // jika kata kurang dari 3, maka:
        {
            // tampilkan pesan error seperti dibawah ini
            printf(RED_COLOR "Error: Delete tidak dapat diterima karena jumlah kata kurang dari batas yang diizinkan.\n" RESET_COLOR);
        }
        else if (jKata > 3) // jika kata lebih dari 3, maka:
        {
            // tampilkan pesan error seperti dibawah ini
            printf(RED_COLOR "Error: Delete tidak dapat diterima karena jumlah kata melebihi batas yang diizinkan.\n" RESET_COLOR);
        }
        else // jika kata pas 3, maka:
        {
            if (strcmp(GETCW(), "tProyek") == 0) // memeriksa apakah tabel yang dituju adalah tProyek
            {
                INC(tape);                 // maju ke kata berikutnya
                strcpy(idProyek, GETCW()); // salin value pertama dari pita ke idProyek

                PK = PK_P(); // periksa apakah primary key proyek sudah terdaftar
                if (PK == 1) // jika primary key sudah terdaftar, maka:
                {
                    FK = CHECK_FK(); // periksa apakah foreign key (berupaa id proyek) sedang digunakan di tabel tim
                    if (FK == 0)     // jika tidak digunakan, maka:
                    {
                        // penghapusan data dapat dilakukan
                        for (int i = 0; i < ip; i++)
                        {
                            if (strcmp(proyek[i].id, idProyek) == 0)
                            {
                                // geser data-data di proyek untuk menutup data yang dihapus
                                for (int j = i; j < ip - 1; j++)
                                {
                                    proyek[j] = proyek[j + 1];
                                }
                                ip--;    // kurangi jumlah data proyek
                                WRITE(); // tulis perubahan ke file
                                // tampilkan pesan sukses
                                printf(GREEN_COLOR "Success: Data telah berhasil didelete dalam tProyek.\n" RESET_COLOR);
                            }
                        }
                    }
                    else // jika foreign key sedang digunakan, maka:
                    {
                        // tampilkan pesan error seperti dibawah ini
                        printf(RED_COLOR "Error: Tidak dapat menghapus data karena ID yang dimaksud saat ini digunakan sebagai foreign key dalam tTim\n" RESET_COLOR);
                    }
                }
                else // jika primary key belum terdaftar, maka:
                {
                    // tampilkan pesan error seperti dibawah ini
                    printf(RED_COLOR "Error: ID yang dimaksud untuk delete tidak terdaftar dalam tProyek. Pastikan ID yang dimasukkan benar.\n" RESET_COLOR);
                }
            }
            else if (strcmp(GETCW(), "tTim") == 0) // memeriksa apakah tabel yang dituju adalah tTim
            {
                INC(tape);              // maju ke kata berikutnya
                strcpy(idTim, GETCW()); // salin value pertama dari pita ke idTim

                PK = PK_T(); // periksa apakah primay key tim sudah terdaftar
                if (PK == 1) // jika primary key sudah terdaftar, maka:
                {
                    // penghapusan dapat dilakukan
                    for (int i = 0; i < it; i++)
                    {
                        if (strcmp(tim[i].id, idTim) == 0)
                        {
                            // geser data-data di tim untuk menutup data yang dihapus
                            for (int j = i; j < it - 1; j++)
                            {
                                tim[j] = tim[j + 1];
                            }
                            it--;    // kurangi jumlah data tim
                            WRITE(); // tulis perubahan ke file
                            // tampilkan pesan sukses
                            printf(GREEN_COLOR "Success: Data telah berhasil didelete dalam tTim.\n" RESET_COLOR);
                        }
                    }
                }
                else // jika primary key belum terdaftar, maka:
                {
                    // tampilkan pesan error seperti dibawah ini
                    printf(RED_COLOR "Error: ID yang dimaksud untuk delete tidak terdaftar dalam tTim. Pastikan ID yang dimasukkan benar.\n" RESET_COLOR);
                }
            }
            else // jika delete tabel selain tProyek dan tTim, maka:
            {
                // tampilkan pesan error seperti dibawah ini
                printf(RED_COLOR "Error: Tidak dapat menemukan tabel yang dituju. Pastikan nama tabel yang dimasukkan benar.\n" RESET_COLOR);
            }
        }
    }
}

// definisi prosedur untuk mencari panjang maksimum kata dari setiap kolom
void MAX()
{
    int p1, p2, p3, p4; // variabel untuk menyimpan panjang string tiap kolom

    // mencari untuk data proyek
    for (int i = 0; i < ip; i++)
    {
        // menghitung panjang setiap kolom proyek[i]
        p1 = strlen(proyek[i].id);
        p2 = strlen(proyek[i].kolom1);
        p3 = strlen(proyek[i].kolom2);
        p4 = strlen(proyek[i].kolom3);

        // memperbarui panjang maksimum untuk setiap kolom
        if (p1 > idP_max)
        {
            idP_max = p1; // panjang maksimum kolom id proyek
        }
        if (p2 > kp1_max)
        {
            kp1_max = p2; // panjang maksimum kolom nama proyek
        }
        if (p3 > kp2_max)
        {
            kp2_max = p3; // panjang maksimum kolom lokasi
        }
        if (p4 > kp3_max)
        {
            kp3_max = p4; // panjang maksimum kolom tanggal
        }
    }

    // mencari untuk data tim
    for (int i = 0; i < it; i++)
    {
        // menghitung panjang setiap kolom tim[i]
        p1 = strlen(tim[i].id);
        p2 = strlen(tim[i].kolom1);
        p3 = strlen(tim[i].kolom2);
        p4 = strlen(tim[i].kolom3);

        // memperbarui panjang maksimum untuk setiap kolom
        if (p1 > idT_max)
        {
            idT_max = p1; // panjang maksimum id tim
        }
        if (p2 > kt1_max)
        {
            kt1_max = p2; // panjang maksimum nama tim
        }
        if (p3 > kt2_max)
        {
            kt2_max = p3; // panjang maksimum jumlah anggota
        }
        if (p4 > kt3_max)
        {
            kt3_max = p4; // panjang maksimum foreign key
        }
    }
}

// definisi prosedur untuk membuat garis bagian atas dan bawah pada tabel proyek
void GARIS_PROYEK()
{
    // menampilkan garis untuk bagian atas dan bawah dengan panjang yang sesuai
    printf("+---------"); // untuk id proyek
    for (int i = 0; i < idP_max - 9; i++)
        printf("-");
    printf("+-----------"); // untuk nama proyek
    for (int i = 0; i < kp1_max - 11; i++)
        printf("-");
    printf("+------"); // untuk lokasi
    for (int i = 0; i < kp2_max - 6; i++)
        printf("-");
    printf("+-------"); // untuk tanggal
    for (int i = 0; i < kp3_max - 7; i++)
        printf("-");
}

// definisi prosedur untuk bagian header proyek
void HEADER_PROYEK()
{
    // akan ditampilkan setelah garis pertama, sebagai header dengan panjang sesuai
    printf("|ID PROYEK"); // bagian id proyek
    for (int i = 0; i < idP_max - 9; i++)
        printf(" ");
    printf("|NAMA PROYEK"); // bagian nama proyek
    for (int i = 0; i < kp1_max - 11; i++)
        printf(" ");
    printf("|LOKASI"); // bagian lokasi
    for (int i = 0; i < kp2_max - 6; i++)
        printf(" ");
    printf("|TANGGAL"); // bagian tanggal
    for (int i = 0; i < kp3_max - 7; i++)
        printf(" ");
}

// definisi prosedur untuk menampilakn bagian isi data/value yang ada pada data proyek
void ISI_PROYEK(int i)
{
    // mencetak nilai dari setiap kolom proyek[i], disesuaikan dengan panjang maksimumnya
    printf("|%s", proyek[i].id); // menampilkan value pertama, berupa id proyek
    if (idP_max > 9)             // proses tampilan spasi jika panjang maksimum lebih dari panjang header
    {
        for (int j = 0; j < idP_max - strlen(proyek[i].id); j++)
            printf(" ");
    }
    else if (idP_max <= 9) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
    {
        for (int j = 0; j < 9 - strlen(proyek[i].id); j++)
            printf(" ");
    }
    printf("|%s", proyek[i].kolom1); // menampilkan value kedua, berupa nama proyek
    if (kp1_max > 11)                // proses tampilan spasi jika panjang maksimum lebih dari panjang header
    {
        for (int j = 0; j < kp1_max - strlen(proyek[i].kolom1); j++)
            printf(" ");
    }
    else if (kp1_max <= 11) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
    {
        for (int j = 0; j < 11 - strlen(proyek[i].kolom1); j++)
            printf(" ");
    }
    printf("|%s", proyek[i].kolom2); // menampilkan value ketiga, berupa lokasi
    if (kp2_max > 6)                 // proses tampilan spasi jika panjang maksimum lebih dari panjang header
    {
        for (int j = 0; j < kp2_max - strlen(proyek[i].kolom2); j++)
            printf(" ");
    }
    else if (kp2_max <= 6) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
    {
        for (int j = 0; j < 6 - strlen(proyek[i].kolom2); j++)
            printf(" ");
    }
    printf("|%s", proyek[i].kolom3); // menampilkan value keempat, berupa tanggal
    if (kp3_max > 7)                 // proses tampilan spasi jika panjang maksimum lebih dari panjang header
    {
        for (int j = 0; j < kp3_max - strlen(proyek[i].kolom3); j++)
            printf(" ");
    }
    else if (kp3_max <= 7) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
    {
        for (int j = 0; j < 7 - strlen(proyek[i].kolom3); j++)
            printf(" ");
    }
}

// definisi prosedur untuk menampilkan data proyek secara keseluruhan ketika perintah show
void TAMPILPROYEK()
{
    READ(); // membaca file dengan memanggil prosedur READ
    MAX();  // mencari panjang maksimum setiap kolom dengan memanggil prosedur MAX

    GARIS_PROYEK(); // membuat garis proyek dengan memanggil prosedur GARIS_PROYEK
    printf("+\n");

    HEADER_PROYEK(); // menampilkan header proyek, dengan memanggil HEADER_PROYEK
    printf("|\n");

    GARIS_PROYEK(); // membuat garis proyek dengan memanggil prosedur GARIS_PROYEK
    printf("+\n");

    // menampilkan isi datanya
    for (int i = 0; i < ip; i++)
    {
        ISI_PROYEK(i); // menampilkan isi proyek dengan memanggil prosedur ISI_PROYEK
        printf("|\n");
    }

    GARIS_PROYEK(); // membuat garis proyek dengan memanggil prosedur GARIS_PROYEK
    printf("+\n");
}

// definisi prosedur untuk membuat garis bagian atas dan bawah pada tabel tim
void GARIS_TIM()
{
    // menampilkan garis untuk bagian atas dan bawah dengan panjang yang sesuai
    printf("+------"); // untuk id tim
    for (int i = 0; i < idT_max - 6; i++)
        printf("-");
    printf("+--------"); // untuk nama tim
    for (int i = 0; i < kt1_max - 8; i++)
        printf("-");
    printf("+--------------"); // untuk jumlah anggota
    for (int i = 0; i < kt2_max - 14; i++)
        printf("-");
}

// definisi prosedur untuk bagian header tim
void HEADER_TIM()
{
    // akan ditampilkan setelah garis pertama, sebagai header dengan panjang sesuai
    printf("|ID TIM"); // bagian id tim
    for (int i = 0; i < idT_max - 6; i++)
        printf(" ");
    printf("|NAMA TIM"); // bagian nama tim
    for (int i = 0; i < kt1_max - 8; i++)
        printf(" ");
    printf("|JUMLAH ANGGOTA"); // bagian jumlah anggota
    for (int i = 0; i < kt2_max - 14; i++)
        printf(" ");
}

// definisi prosedur untuk menampilakn bagian isi data/value yang ada pada data tim
void ISI_TIM(int i)
{
    // mencetak nilai dari setiap kolom timk[i], disesuaikan dengan panjang maksimumnya
    printf("|%s", tim[i].id); // menampilkan value pertama, berupa id tim
    if (idT_max > 6)          // proses tampilan spasi jika panjang maksimum lebih dari panjang header
    {
        for (int j = 0; j < idT_max - strlen(tim[i].id); j++)
            printf(" ");
    }
    else if (idT_max <= 6) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
    {
        for (int j = 0; j < 6 - strlen(tim[i].id); j++)
            printf(" ");
    }
    printf("|%s", tim[i].kolom1); // menampilkan value kedua, berupa nama tim
    if (kt1_max > 8)              // proses tampilan spasi jika panjang maksimum lebih dari panjang header
    {
        for (int j = 0; j < kt1_max - strlen(tim[i].kolom1); j++)
            printf(" ");
    }
    else if (kt1_max <= 8) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
    {
        for (int j = 0; j < 8 - strlen(tim[i].kolom1); j++)
            printf(" ");
    }
    printf("|%s", tim[i].kolom2); // menampilkan value ketiga, berupa jumlah anggota
    if (kt3_max > 14)             // proses tampilan spasi jika panjang maksimum lebih dari panjang header
    {
        for (int j = 0; j < kt3_max - strlen(tim[i].kolom2); j++)
            printf(" ");
    }
    else if (kt3_max <= 14) // proses tampilan spasi jika panjang maksimum kurang dari panjang header
    {
        for (int j = 0; j < 14 - strlen(tim[i].kolom2); j++)
            printf(" ");
    }
}

// definisi prosedur untuk menampilkan data tim secara keseluruhan ketika perintah show
void TAMPILTIM()
{
    READ(); // membaca file dengan memanggil prosedur READ
    MAX();  // mencari panjang maksimum setiap kolom dengan memanggil prosedur MAX

    GARIS_TIM(); // membuat garis tim dengan memanggil prosedur GARIS_TIM
    printf("+---------");
    for (int i = 0; i < kt3_max - 9; i++)
        printf("-");
    printf("+\n");

    HEADER_TIM();         // menampilkan header tim dengan memanggil HEADER_TIM
    printf("|ID PROYEK"); // menambahkan header tim untuk foreign key
    for (int i = 0; i < kt3_max - 9; i++)
        printf(" ");
    printf("|\n");

    GARIS_TIM();          // membuat garis tim dengan memanggil prosedur GARIS_TIM
    printf("+---------"); // menambahkan garis untuk foreign key
    for (int i = 0; i < kt3_max - 9; i++)
        printf("-");
    printf("+\n");

    // menampilkan isi datanya
    for (int i = 0; i < it; i++)
    {
        ISI_TIM(i);                   // menampilkan isi tim dengan memanggil prosedur ISI_TIM
        printf("|%s", tim[i].kolom3); // menambahkan untuk foreign key
        if (kt3_max > 9)
        {
            for (int j = 0; j < kt3_max - strlen(tim[i].kolom3); j++)
                printf(" ");
        }
        else if (kt3_max <= 9)
        {
            for (int j = 0; j < 9 - strlen(tim[i].kolom3); j++)
                printf(" ");
        }
        printf("|\n");
    }

    GARIS_TIM();          // membuat garis tim dengan memanggil prosedur GARIS_TIM
    printf("+---------"); // menambahkan garis untuk foreign key
    for (int i = 0; i < kt3_max - 9; i++)
        printf("-");
    printf("+\n");
}

// definisi prosedur untuk menampilkan data join proyek tim
void JOIN1()
{
    READ(); // membaca file dengan memanggil prosedur READ
    MAX();  // mencari panjang maksimum setiap kolom dengan memanggil prosedur MAX

    // membuat garis pada tabel dengan memanggil dua prosedur, GARIS_PROYEK dan GARIS_TIM
    GARIS_PROYEK();
    GARIS_TIM();
    printf("+\n");

    // membuat header pada tabel dengan memanggil dua prosedur, HEADER_PROYEK dan HEADER_TIM
    HEADER_PROYEK();
    HEADER_TIM();
    printf("|\n");

    // membuat garis pada tabel dengan memanggil dua prosedur, GARIS_PROYEK dan GARIS_TIM
    GARIS_PROYEK();
    GARIS_TIM();
    printf("+\n");

    // menampilkan isi joinnya
    for (int i = 0; i < ip; i++)
    {
        for (int j = 0; j < it; j++)
        {
            // bisa ditampilkan ketika saling terikat dengan foreign key
            if (strcmp(proyek[i].id, tim[j].kolom3) == 0)
            {
                // menampilkan isinya nya dengan memanggil dua prosedur, ISI_PROYEK dan ISI_TIM
                ISI_PROYEK(i);
                ISI_TIM(j);
                printf("|\n");
            }
        }
    }

    // membuat garis pada tabel dengan memanggil dua prosedur, GARIS_PROYEK dan GARIS_TIM
    GARIS_PROYEK();
    GARIS_TIM();
    printf("+\n");
}

// definisi prosedur untuk menampilkan data join tim proyek
void JOIN2()
{
    READ(); // membaca file dengan memanggil prosedur READ
    MAX();  // mencari panjang maksimum setiap kolom dengan memanggil prosedur MAX

    // membuat garis pada tabel dengan memanggil dua prosedur, GARIS_TIM dan GARIS_PROYEK
    GARIS_TIM();
    GARIS_PROYEK();
    printf("+\n");

    // menampilkan header pada tabel dengan memanggil dua prosedur, HEADER_TIM dan HEADER_PROYEK
    HEADER_TIM();
    HEADER_PROYEK();
    printf("|\n");

    // membuat garis pada tabel dengan memanggil dua prosedur, GARIS_TIM dan GARIS_PROYEK
    GARIS_TIM();
    GARIS_PROYEK();
    printf("+\n");

    // Iterate through the project array and match with team data
    for (int i = 0; i < ip; i++)
    {
        // bisa ditampilkan ketika saling terikat dengan foreign key
        for (int j = 0; j < it; j++)
        {
            if (strcmp(proyek[i].id, tim[j].kolom3) == 0)
            {
                // menampilkan isinya nya dengan memanggil dua prosedur, ISI_TIM dan ISI_PROYEK
                ISI_TIM(j);
                ISI_PROYEK(i);
                printf("|\n");
            }
        }
    }

    // membuat garis pada tabel dengan memanggil dua prosedur, GARIS_TIM dan GARIS_PROYEK
    GARIS_TIM();
    GARIS_PROYEK();
    printf("+\n");
}

// definisi prosedur untuk show/menampilkan data yang tersedia pada data proyek dan tim
void SHOW(char tape[])
{
    int jKata = HITUNG_KATA(tape); // menghitung jumlah kata dalam satu perintah

    // memerika jumlah kata dalam satu perintah
    // perintah SHOW memiliki jumlah 2 dan 3 kata --> SHOW file dan SHOW file file (untuk join)
    if (jKata < 2) // jika kata kurang dari 2, maka:
    {
        // tampilkan pesan error seperti dibawah ini
        printf(RED_COLOR "Error: Show tidak dapat diterima karena jumlah kata kurang dari batas yang diizinkan.\n" RESET_COLOR);
    }
    else if (jKata > 3) // jika kata lebih dari 3, maka:
    {
        // tampilkan pesan error seperti dibawah ini
        printf(RED_COLOR "Error: Show tidak dapat diterima karena jumlah kata melebihi batas yang diizinkan.\n" RESET_COLOR);
    }
    else
    {
        START(tape); // memulai mesin kata

        // memeriksa apakah perintah SHOW benar atau tidak
        if (strcmp(GETCW(), "SHOW") == 0)
        {
            INC(tape); // maju ke kata berikutnya

            if (strcmp(GETCW(), "tProyek") == 0) // memeriksa apakah tabel yang dituju adalah tProyek
            {
                // jika hanya ingin menampilkan tabel proyek
                if (jKata == 2)
                {
                    TAMPILPROYEK(); // panggil prosedur TAMPILPROYEK
                }
                else
                {
                    // jika ingin melakukan join, pastikan perintahnya sesuai
                    INC(tape);                        // maju ke kata berikutnya
                    if (strcmp(GETCW(), "tTim") == 0) // periksa apakah join ke tabel tTim, jika iya
                    {
                        // tampilkan pesan sukses
                        printf(GREEN_COLOR "Success: Silakan tabel JOIN nya.\n\n" RESET_COLOR);
                        JOIN1(); // panggil prosedur JOIN1
                    }
                    else if (strcmp(GETCW(), "tProyek") == 0) // jika ke tabel sendiri
                    {
                        // tampilkan pesan error seperti dibawah ini
                        printf(RED_COLOR "Error: Tidak dapat melakukan JOIN pada tabel yang sama.\n" RESET_COLOR);
                    }
                    else // jika selain tTim / tProyek
                    {
                        // tampilkan pesan error seperti dibawah ini
                        printf(RED_COLOR "Error: Tidak dapat menemukan tabel JOIN yang dituju. Pastikan nama tabel yang dimasukkan benar.\n" RESET_COLOR);
                    }
                }
            }
            else if (strcmp(GETCW(), "tTim") == 0) // memeriksa apakah tabel yang dituju adalah tTim
            {
                // jika hanya ingin menampilkan tabel tim
                if (jKata == 2)
                {
                    TAMPILTIM(); // panggil prosedur TAMPILTIM
                }
                else
                {
                    // jika ingin melakukan join, pastikan perintahnya sesuai
                    INC(tape);                           // maju ke kata berikutnya
                    if (strcmp(GETCW(), "tProyek") == 0) // periksa apakah join ke tabel tProyek, jika iya
                    {
                        // tampilkan pesan sukses
                        printf(GREEN_COLOR "Success: Silakan tabel JOIN nya.\n\n" RESET_COLOR);
                        JOIN2(); // panggil prosedur JOIN2
                    }
                    else if (strcmp(GETCW(), "tTim") == 0) // jika ke tabel sendiri
                    {
                        // tampilkan pesan error seperti dibawah ini
                        printf(RED_COLOR "Error: Tidak dapat melakukan JOIN pada tabel yang sama.\n" RESET_COLOR);
                    }
                    else // jika selain tProyek / tTim
                    {
                        // tampilkan pesan error seperti dibawah ini
                        printf(RED_COLOR "Error: Tidak dapat menemukan tabel JOIN yang dituju. Pastikan nama tabel yang dimasukkan benar.\n" RESET_COLOR);
                    }
                }
            }
            else // jika show tabel selain tProyek dan tTim, maka:
            {
                // tampilkan pesan error seperti dibawah ini
                printf(RED_COLOR "Error: Tidak dapat menemukan tabel yang dituju. Pastikan nama tabel yang dimasukkan benar.\n" RESET_COLOR);
            }
        }
    }
}

// definisi prosedur untuk menjalankan dbmsnya
void JALANKAN(char tape[])
{
    START(tape); // memulai mesin kata

    //  memeriksa apakah ada tanda semikolon (;) di akhir perintah
    int panjang_tape = strlen(tape);
    if (tape[panjang_tape - 1] != ';') // jika tidak ada, maka:
    {
        // tampilkan pesan error seperti di bawah ini
        printf(RED_COLOR "Error: Perintah tidak lengkap karena kurangnya tanda titik koma (;) di akhir perintah.\n" RESET_COLOR);
    }
    else
    {
        // memproses perintah berdasarkan kata kunci pertama dari pita
        if (strcmp(GETCW(), "INPUT") == 0) // jika input
        {
            INPUT(tape); // panggil prosedur INPUT
        }
        else if (strcmp(GETCW(), "UPDATE") == 0) // jika update
        {
            UPDATE(tape); // panggil prosedur update
        }
        else if (strcmp(GETCW(), "DELETE") == 0) // jika delete
        {
            DELETE(tape); // panggil prosedur delete
        }
        else if (strcmp(GETCW(), "SHOW") == 0) // jika show
        {
            SHOW(tape); // panggil prosedur show
        }
        else if (strcmp(GETCW(), "HELP") == 0) // ini bonus untuk membantu, yaitu help
        {
            HELP(); // panggil prosedur HELP
        }
        else // jika bukan perintah selain di atas, maka:
        {
            // tampilkan pesan error seperti di bawah ini
            printf(RED_COLOR "Error: Tidak dapat mengenali perintah yang dimaksud. Mohon periksa kembali perintah yang Anda masukkan.\n" RESET_COLOR);
        }
    }
}
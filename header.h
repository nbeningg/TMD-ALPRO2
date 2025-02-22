/* Saya Nuansa Bening Aura Jelita mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah
Algoritma dan Pemrograman II untuk keberkahanNya maka saya tidak
melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin. */

// deklarasi library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// konstanta untuk kode warna ANSI
#define RED_COLOR "\033[31m"    // kode warna merah, untuk error
#define GREEN_COLOR "\033[32m"  // kode warna hijau, untuk success
#define YELLOW_COLOR "\033[33m" // kode warna kuning, untuk exit
#define RESET_COLOR "\033[0m"   // kode untuk mengatur ulang warna ke default

// deklarasi tipe data terstruktur atau bungkusan
typedef struct
{
    char id[100], kolom1[100], kolom2[100], kolom3[100]; // deklrasi variabel untuk isi datanya, terdapat 4 value
} data;                                                  // nama tipe data atau bungkusannya adalah "data"

// menyimpan dua data, yaitu data proyek dan tim
extern data proyek[300]; // tabel pertama untuk menyimpan data proyek/program yang akan di kerjakan
extern data tim[300];    // tabel kedua untuk menyimpan data tim yang mengikuti proyek/progam tabel pertama

// deklarasi variabel global
extern int idx;                                                        // untuk index dari karakter terakhir pada kata
extern int wlen;                                                       // untuk word length
extern char cw[100];                                                   //  untuk current word
extern int ip;                                                         // untuk jumlah data proyek
extern int it;                                                         // untuk jumlah data tim
extern char idProyek[100], namaProyek[100], lokasi[100], tanggal[100]; // untuk menyimpan data proyek/program
extern char idTim[100], namaTim[100], jumlah[100], fk[100];            // untuk menyimpan data tim

// deklarasi prosedur untuk menunggu waktu selama x detik
void WAIT(float x);

// deklarasi prosedur untuk animasi tampilan awal
void ANIMATED();

// deklarasi fungsi untuk memeriksa end of process
int EOP(char str[]);

// deklarasi prosedur untuk memulai mesin kata
void START(char str[]);

// deklarasi prosedur untuk mereset atau mengosongkan kata yang dibaca dalam mesin kata
void RESET();

// deklarasi prosedur untuk memajukan kata
void INC(char str[]);

// deklarasi fungsi untuk mendapatkan panjang kata saat ini
int GETLEN();

// deklarasi fungsi untuk mendapatkan current word
char *GETCW();

// deklarasi fungsi untuk menghitung jumlah kata dalam satu perintah
int HITUNG_KATA(char pita[]);

// deklarasi prosedur untuk menampilkan tampilan bantuan
void HELP();

// deklarasi prosedur untuk sorting secara ascending berdasarkan id pada data proyek dan tim
void SORT_PROYEK(data proyek[], int n); // sorting untuk data proyek
void SORT_TIM(data tim[], int n);       // sorting untuk data tim

// deklarasi prosedur sequentiel file
void READ();  // untuk melakukan pembacaan data pada file dat
void WRITE(); // untuk melakukan simpan data ke file dat

// deklarasi fungsi untuk mencari primary key pada data proyek dan tim
int PK_P(); // untuk primary key pada data proyek
int PK_T(); // untuk primary key pada data tim

// deklarasi fungsi terkait foreign key
int ADD_FK();   // untuk cek apakah id proyek bisa ditambahkan menjadi foreign key
int CHECK_FK(); // untuk cek apakah id proyek sedang menjadi foreign key

// deklarasi prosedur untuk perintah dbms nya
void INPUT(char tape[]);  // untuk menginput/menambahkan data baru pada data proyek dan tim
void UPDATE(char tape[]); // untuk mengupdate/memperbarui value pada data proyek dan tim
void DELETE(char tape[]); // untuk delete/menghapus data pada data proyek dan tim
void SHOW(char tape[]);   // untuk show/menampilkan data yang tersedia pada data proyek dan tim

// deklarasi prosedur untuk tampilan tabel
void MAX(); // untuk mencari panjang maksimum kata dari setiap kolom
// data proyek
void TAMPILPROYEK1();   // untuk menampilkan data proyek setelah di input/update
void GARIS_PROYEK();    // untuk membuat garis bagian atas dan bawah pada tabel proyek
void HEADER_PROYEK();   // untuk bagian header proyek
void ISI_PROYEK(int i); // untuk menampilakn bagian isi data/value yang ada pada data proyek
void TAMPILPROYEK();    // untuk menampilkan data proyek secara keseluruhan ketika perintah show
// data tim
void TAMPILTIM1();   // untuk menampilkan data tim setelah di input/update
void GARIS_TIM();    // untuk membuat garis bagian atas dan bawah pada tabel tim
void HEADER_TIM();   // untuk bagian header tim
void ISI_TIM(int i); // untuk menampilakn bagian isi data/value yang ada pada data tim
void TAMPILTIM();    // untuk menampilkan data tim secara keseluruhan ketika perintah show
// data proyek dan tim
void JOIN1(); // untuk menampilkan data join proyek tim
void JOIN2(); // untuk menampilkan data join tim proyek

// deklarasi prosedur untuk menjalankan dbmsnya
void JALANKAN(char tape[]);
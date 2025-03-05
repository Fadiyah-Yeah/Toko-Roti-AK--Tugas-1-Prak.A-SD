#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

//deklarasi struct
struct roti{
    string nama;
    int kode=000;
    float harga;
};

//data dari struct roti
roti rt[5]={
    {"Tawar", 001,15000.00},
    {"Coklat", 002, 18000.00},
    {"Keju", 003, 20000.00},
    {"Gandum", 004, 22000.00},
    {"Pisang", 005, 17000.00}
};
//untuk menghitung panjang data
int jml =sizeof(rt)/sizeof(*rt);

// void tampilan menu
void tampil(){
    //headline
    cout << setfill('=') << setw(50) << " " << endl;
    cout << setfill(' ') << setw(30) << "MENU TOKO ROTI AK" << endl;
    cout << setfill('=') << setw(50) << " " << endl;
    //data apa yang ditampilan
    cout <<left << setfill(' ') << setw(6) << "No" << setw(1) << "|"
         << setw(15) << "Nama" << setw(1) << "|"
         << setw(10) << "Kode" << setw(1) << "|"
         << setw(10) << "Harga" << endl;
    cout << setfill('=') << setw(50) << " " << endl;
    //penampilan data
    for(int i=0; i <5; i++){
        cout << setfill(' ') << setw(6) << i+1 << setw(1)
             << "|" << setw(15) << rt[i].nama << setw(1)
             << "|" << setw(10) << rt[i].kode << setw(1)
             << "|" << setw(10) << rt[i].harga << endl;
    }

    cout << setfill('=') << setw(50) << " " << endl;
}

//void cari kode
void cari_kode(int cari){
    //deklarasi
    bool found = false;
    int i=0;
    //pencarian linier search
    while ((i < 5) && (!found)) {
        if (rt[i].kode == cari) {
            found = true;
        } else {
            i++;
        } 
    }
    //tampilan data yang dicari
    if(found){
        cout << "Data ditemukan" << endl;
        cout << "Nama  : Roti " << rt[i].nama << endl;
        cout << "Kode  : " << rt[i].kode << endl;
        cout << "Harga : " << rt[i].harga << endl;
    }else{
        cout << "Data tidak ditemukan" << endl;
    }

}

//void cari nama
void cari_nama(string cari){
    // diurutkan berdasarkan nama
    sort(rt, rt + jml, [](roti a, roti b) {
        return a.nama < b.nama;
    });

    // deklarasi
    int tengah, awal = 0, akhir = jml - 1; 
    bool found = false;

    // Pencarian
    while (awal <= akhir && !found) { 
        tengah = (awal + akhir) / 2;
        if (rt[tengah].nama == cari) {
            found = true;
        } else if (rt[tengah].nama < cari) {
            awal = tengah + 1;
        } else {
            akhir = tengah - 1;
        }
    }

    // Penampilan data jika ditemukan
    if (found) {
        cout << "Data ditemukan" << endl;
        cout << "Nama  : " << rt[tengah].nama << endl;
        cout << "Kode  : " << rt[tengah].kode << endl;
        cout << "Harga : " << rt[tengah].harga << endl;
    } else {
        cout << "Data tidak ditemukan" << endl;
    }
}

//void sorting ascending dengan menggunakan quick short
void sort_asc(int n1, int n2){
    //deklarasi
    int L=n1, H=n2;
    //pengurutan
    do {
        while (rt[L].harga < rt[(n1 + n2) / 2].harga )
            L++;
        while (rt[H].harga > rt[(n1 + n2) / 2].harga)
            H--;
        if (L <= H) {
            swap(rt[L].harga, rt[H].harga);
            swap(rt[L].nama, rt[H].nama);
            swap(rt[L].kode, rt[H].kode);
            L++;
            H--;
        }
    } while (L <= H);

    if (n1 < H)
        sort_asc(n1, H);
    if (L < n2)
        sort_asc(L, n2);
    //tampilan data yang sudah terurut
    cout << "Data yang Sudah terurut" << endl;
    tampil();
    cout << endl;
}

//void sorting descending dengan menggunakan bubble short
void sort_desc(){
    //pengurutan
    for (int i = 0; i < jml - 1; i++) {
        for (int j = 0; j < jml - 1 - i; j++) {
            if (rt[j].harga < rt[j + 1].harga) {
                swap(rt[j].kode, rt[j + 1].kode);
                swap(rt[j].nama, rt[j + 1].nama);
                swap(rt[j].harga, rt[j + 1].harga);
                
            }
        } 
    }
    //tampilan data yang sudah terurut
    cout << "Data yang Sudah terurut" << endl;
    tampil();
    cout << endl;
}

//void keluar
void exit(){
    //ucapan
    cout << setfill('=') << setw(20) << " " ;
    cout << setfill(' ') << setw(6) << "TERIMA KASIH" << setw(1) << " ";
    cout << setfill('=') << setw(20) << " ";
    cout << endl;
    exit(0);
}

//void menu
void menu(){
    //headline
    cout << setfill('=') << setw(20) << " " ;
    cout << setfill(' ') << setw(6) << "TOKO ROTI AK" << setw(1) << " ";
    cout << setfill('=') << setw(20) << " ";
    cout << endl;
    //menu
    cout << "1. Tampilkan Menu Roti" << endl;
    cout << "2. Cari Berdasarkan Kode Roti" << endl;
    cout << "3. Cari Berdasarkan Nama Roti" << endl;
    cout << "4. Sort Harga Roti (asc)" << endl;
    cout << "5. Sort Harga Roti (desc)" << endl;
    cout << "6. Exit" << endl;

    cout << setfill('=') << setw(54) << " " << endl;
}

int main(){
    //deklarasi
    char jawab;
    int kode;
    string nama;
    //perulangan menu
    do{
    menu(); 
    //input menu
    int pilih;
    cout << "Pilih Menu : ";
    cin >> pilih;

    switch (pilih)//untuk menuju menu yang dipilih
    {
    case 1://menu 1
        system("CLS");
        tampil();
        break;
    
    case 2://menu2
        system("CLS");
        cout << "Masukkan Kode Roti (1/2/3/4/5) : ";
        cin >> kode;
        cout << endl;
        cari_kode(kode);
        break;

    case 3://menu 3
        system("CLS");
        cout << "Masukkan Nama Roti(Tawar/Coklat/keju/Gandum/Pisang) : ";
        cin >> nama;
        cout << endl;
        cari_nama(nama);
        break;

    case 4://menu 4
        system("CLS");
        sort_asc(0, jml-1);
        break;

    case 5://menu 5
        system("CLS");
        sort_desc();
        break;

    case 6://menu 6
        system("CLS");
        exit();
        break;

    default:
        break;
    }
    //tanya ingin keluar atau tidak
    cout << "Apakah Anda Ingin Melakukan Pilihan Lagi? (y/n) : ";
    cin >> jawab;
    cout << endl;
    system("CLS");
    }while(jawab == 'y' || jawab == 'Y');//jawaban untuk terus melanjutkan atau
    cout << endl;
    return 0;
}

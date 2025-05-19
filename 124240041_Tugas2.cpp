#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// Struktur Pesanan
struct Pesanan
{
    char nama[50];
    char jenisRoti[50];
    int totalHarga;
};

// NODE Queue
struct QueueNode
{
    Pesanan data;
    QueueNode *next;
};

// NODE Stack
struct StackNode
{
    Pesanan data;
    StackNode *next;
};

// Pointer queue
QueueNode *depan = NULL;
QueueNode *belakang = NULL;

// Pointer stack
StackNode *awal = NULL;
StackNode *top = NULL;

// Queue kosong
bool queueKosong()
{
    return depan == NULL;
}

// Stack kosong
bool stackKosong()
{
    return awal == NULL;
}

// Tambah antrean
void enqueue(Pesanan p)
{
    QueueNode *baru = new QueueNode;
    baru->data = p;
    baru->next = NULL;

    if (queueKosong())
    {
        depan = belakang = baru;
    }
    else
    {
        belakang->next = baru;
        belakang = baru;
    }
}

// Hapus dari antrean dan masukkan ke stack
void dequeue()
{
    if (queueKosong())
    {
        cout << "Antrean kosong." << endl;
        return;
    }

    QueueNode *hapus = depan;
    Pesanan p = hapus->data;

    // Push ke stack (riwayat)
    StackNode *newNode = new StackNode;
    newNode->data = p;
    newNode->next = NULL;

    if (stackKosong())
    {
        awal = top = newNode;
    }
    else
    {
        newNode->next = awal;
        awal = newNode;
    }

    depan = depan->next;
    if (depan == NULL)
        belakang = NULL;
    delete hapus;

    cout << "Pesanan " << p.nama << " telah dilayani." << endl;
}

// Batalkan pesanan terakhir (dari belakang antrean)
void batalkanPesanan()
{
    if (queueKosong())
    {
        cout << "Tidak ada pesanan untuk dibatalkan." << endl;
        return;
    }

    if (depan == belakang)
    {
        cout << "Pesanan " << depan->data.nama << " dibatalkan." << endl;
        delete depan;
        depan = belakang = NULL;
        return;
    }

    QueueNode *temp = depan;
    while (temp->next != belakang)
    {
        temp = temp->next;
    }

    cout << "Pesanan " << belakang->data.nama << " dibatalkan." << endl;
    delete belakang;
    belakang = temp;
    belakang->next = NULL;
}

// Tampilkan antrean
void tampilAntrean()
{
    if (queueKosong())
    {
        cout << "Antrean kosong." << endl;
        return;
    }

    cout << setfill('=') << setw(100) << "=" << endl;
    cout << setfill(' ') << setw(60) << "DAFTAR PESANAN DALAM ANTREAN" << endl;
    cout << setfill('=') << setw(100) << "=" << endl;

    cout << setfill(' ')
         << setw(4) << "No" << " | "
         << setw(30) << "Nama" << " | "
         << setw(30) << "Jenis Roti" << " | "
         << setw(25) << "Total Harga" << endl;
    cout << setfill('=') << setw(100) << "=" << endl;

    int no = 1;
    QueueNode *temp = depan;
    while (temp != NULL)
    {
        cout << setfill(' ')
             << setw(4) << no++ << " | "
             << setw(30) << temp->data.nama << " | "
             << setw(30) << temp->data.jenisRoti << " | "
             << setw(25) << temp->data.totalHarga << endl;
        temp = temp->next;
    }

    cout << setfill('=') << setw(100) << "=" << endl;
}

// Tampilkan riwayat dari stack
void tampilRiwayat()
{
    if (stackKosong())
    {
        cout << "Belum ada pesanan yang dilayani." << endl;
        return;
    }

    cout << setfill('=') << setw(100) << "=" << endl;
    cout << setfill(' ') << setw(60) << "RIWAYAT PESANAN DILAYANI" << endl;
    cout << setfill('=') << setw(100) << "=" << endl;

    cout << setfill(' ')
         << setw(4) << "No" << " | "
         << setw(30) << "Nama" << " | "
         << setw(30) << "Jenis Roti" << " | "
         << setw(25) << "Total Harga" << endl;
    cout << setfill('=') << setw(100) << "=" << endl;

    int no = 1;
    StackNode *temp = awal;
    while (temp != NULL)
    {
        cout << setfill(' ')
             << setw(4) << no++ << " | "
             << setw(30) << temp->data.nama << " | "
             << setw(30) << temp->data.jenisRoti << " | "
             << setw(25) << temp->data.totalHarga << endl;
        temp = temp->next;
    }

    cout << setfill('=') << setw(100) << "=" << endl;
}

// Main
int main()
{
    int pilihan;
    Pesanan p;
    char jawab;

    do
    {
        cout << endl;
        cout << "=== TOKO ROTI MANIS LEZAT ===" << endl;
        cout << "1. Ambil Antrean" << endl;
        cout << "2. Layani Pembeli" << endl;
        cout << "3. Tampilkan Pesanan" << endl;
        cout << "4. Batalkan Pesanan Terakhir" << endl;
        cout << "5. Tampilkan History Pesanan" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();
        system("CLS");

        switch (pilihan)
        {
        case 1:
            cout << "Nama Pelanggan  : ";
            cin.getline(p.nama, 50);
            cout << "Jenis Roti      : ";
            cin.getline(p.jenisRoti, 50);
            cout << "Total Harga (Rp): ";
            cin >> p.totalHarga;
            cin.ignore();
            enqueue(p);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            tampilAntrean();
            break;
        case 4:
            batalkanPesanan();
            break;
        case 5:
            tampilRiwayat();
            break;
        case 6:
            cout << "Terima kasih telah menggunakan sistem." << endl;
            exit(0);
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
        cout << "Apakah Anda Ingin Melakukan Pilihan Lagi? (y/n) : ";
        cin >> jawab;
    } while (jawab == 'y' || jawab == 'Y');
    system("CLS");
    return 0;
}

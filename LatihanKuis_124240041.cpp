#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
using namespace std;

struct data_penduduk
{
    char nomor[100];
    char nama[200];
    char alamat[500];
    char jenis[100];
};

char file[] = "data_penduduk.dat";

data_penduduk dp[100];
int jml;

void input()
{
    FILE *fp = fopen(file, "ab");
    if (!fp)
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Masukkan jumlah data: ";
    cin >> jml;
    cin.ignore();
    cout << setfill('-') << setw(50) << " " << endl;
    for (int i = 0; i < jml; i++)
    {
        cout << "Masukkan Nomor: ";
        cin.getline(dp[i].nomor, 100);
        cout << "Masukkan Nama: ";
        cin.getline(dp[i].nama, 200);
        cout << "Masukkan Alamat: ";
        cin.getline(dp[i].alamat, 500);
        cout << "Masukkan Jenis: ";
        cin.getline(dp[i].jenis, 100);
        cout << setfill('-') << setw(50) << " " << endl;
        fwrite(&dp[i], sizeof(data_penduduk), 1, fp);
    }
    cout << setfill('-') << setw(50) << " " << endl;
    fclose(fp);
}

void output()
{
    FILE *fp = fopen(file, "rb");
    if (!fp)
    {
        cout << "Tidak ada data." << endl;
        return;
    }

    int c = 0;
    while (fread(&dp[c], sizeof(data_penduduk), 1, fp))
    {
        c++;
    }
    fclose(fp);

    // Bubble Sort untuk mengurutkan berdasarkan nomor kependudukan
    for (int i = 0; i < c - 1; i++)
    {
        for (int j = 0; j < c - i - 1; j++)
        {
            if (strcmp(dp[j].nomor, dp[j + 1].nomor) > 0)
            {
                swap(dp[j], dp[j + 1]);
            }
        }
    }

    cout << setfill('=') << setw(125) << " " << endl;
    cout << setfill(' ') << setw(70) << "Data Penduduk" << endl;
    cout << setfill('=') << setw(125) << " " << endl;

    cout << setfill(' ') << setw(10) << "No" << setw(1) << "|"
         << setw(37) << "Nama" << setw(1) << "|"
         << setw(40) << "Alamat" << setw(1) << "|"
         << setw(27) << "Jenis" << setw(1) << "|" << endl;
    cout << setfill('=') << setw(125) << " " << endl;

    for (int i = 0; i < jml; i++)
    {
        cout << setfill(' ') << setw(10) << dp[i].nomor << setw(1) << "|"
             << setw(37) << dp[i].nama << setw(1) << "|"
             << setw(40) << dp[i].alamat << setw(1) << "|"
             << setw(27) << dp[i].jenis << setw(1) << "|" << endl;
    }
    cout << setfill('=') << setw(125) << " " << endl;
}

void search()
{
    FILE *fp = fopen(file, "rb");
    if (!fp)
    {
        cout << "Tidak ada data." << endl;
        return;
    }

    char cari[100];
    cout << "Masukkan Nomor yang dicari: ";
    cin >> cari;

    int c = 0;
    while (fread(&dp[c], sizeof(data_penduduk), 1, fp))
    {
        c++;
    }
    fclose(fp);

    bool found = false;
    for (int i = 0; i < c; i++)
    {
        if (strcmp(dp[i].nomor, cari) == 0)
        {
            cout << "Data ditemukan!" << endl;
            cout << "Nomor  : " << dp[i].nomor << endl;
            cout << "Nama   : " << dp[i].nama << endl;
            cout << "Alamat : " << dp[i].alamat << endl;
            cout << "Jenis  : " << dp[i].jenis << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Data tidak ditemukan." << endl;
    }
}

void edit()
{
    FILE *fp = fopen(file, "rb+");
    if (!fp)
    {
        cout << "Tidak ada data." << endl;
        return;
    }

    char cari[100];
    cout << "Masukkan Nomor yang ingin diedit: ";
    cin >> cari;
    cin.ignore();

    data_penduduk temp;
    bool found = false;
    long pos;
    while (fread(&temp, sizeof(data_penduduk), 1, fp))
    {
        if (strcmp(temp.nomor, cari) == 0)
        {
            found = true;
            cout << "Data ditemukan!" << endl;
            cout << "Nama   : " << temp.nama << endl;
            cout << "Alamat : " << temp.alamat << endl;
            cout << "Jenis  : " << temp.jenis << endl;

            cout << "Masukkan Alamat Baru: ";
            cin.getline(temp.alamat, 500);

            pos = ftell(fp) - sizeof(data_penduduk);
            fseek(fp, pos, SEEK_SET);
            fwrite(&temp, sizeof(data_penduduk), 1, fp);
            break;
        }
    }
    fclose(fp);

    if (found)
        cout << "Data berhasil diperbarui." << endl;
    else
        cout << "Data tidak ditemukan." << endl;
}

void hapus()
{
    FILE *fp = fopen(file, "rb");
    if (!fp)
    {
        cout << "Tidak ada data." << endl;
        return;
    }

    int count = 0;
    while (fread(&dp[count], sizeof(data_penduduk), 1, fp))
    {
        count++;
    }
    fclose(fp);

    if (count == 0)
    {
        cout << "Data masih kosong, tidak bisa menghapus." << endl;
        return;
    }

    char cari[100];
    cout << "Masukkan Nomor yang ingin dihapus: ";
    cin >> cari;

    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(dp[i].nomor, cari) == 0)
        {
            found = true;
            cout << "Data yang akan dihapus:" << endl;
            cout << "Nomor  : " << dp[i].nomor << endl;
            cout << "Nama   : " << dp[i].nama << endl;
            cout << "Alamat : " << dp[i].alamat << endl;
            cout << "Jenis  : " << dp[i].jenis << endl;

            for (int j = i; j < count - 1; j++)
            {
                dp[j] = dp[j + 1];
            }
            count--;
            break;
        }
    }

    if (!found)
    {
        cout << "Data tidak ditemukan." << endl;
        return;
    }

    fp = fopen(file, "wb");
    fwrite(dp, sizeof(data_penduduk), count, fp);
    fclose(fp);

    cout << "Data berhasil dihapus." << endl;
}

void exit()
{
    // ucapan
    cout << setfill('=') << setw(20) << " ";
    cout << setfill(' ') << setw(6) << "SAMPAI JUMPA" << setw(1) << " ";
    cout << setfill('=') << setw(20) << " ";
    cout << endl;
    exit(0);
}

int main()
{
    char pilihan;
    int pilih;
    do
    {
        cout << setfill('=') << setw(50) << " " << endl;
        cout << setfill(' ') << setw(30) << "DATA PENDUDUK" << setw(20) << " " << endl;
        cout << setfill('=') << setw(50) << " " << endl;

        cout << "1. Input Data" << endl;
        cout << "2. Output Data" << endl;
        cout << "3. Search Data" << endl;
        cout << "4. Edit Data" << endl;
        cout << "5. Hapus Data" << endl;
        cout << "6. Keluar" << endl;

        cout << setfill('=') << setw(50) << " " << endl;

        cout << "Masukkan Pilihan Anda : ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            input();
            break;

        case 2:
            output();
            break;

        case 3:
            search();
            break;

        case 4:
            edit();
            break;

        case 5:
            hapus();
            break;

        case 6:
            exit();
            break;

        default:
            break;
        }
        cout << "Apakah Anda Ingin Mengulang program (y/n) : ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
    return 0;
}

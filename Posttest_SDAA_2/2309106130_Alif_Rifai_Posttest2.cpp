#include <iostream>
#include <string>
using namespace std;

struct komik {
    string judul;
    string penulis;
    int tahunTerbit;
    int rating;
    string genre;
};

void clear_screen() {
    system("cls");
}

void tampil_header(string title) {
    cout << "=======================================" << endl;
    cout << "            " << title << endl;
    cout << "=======================================" << endl;
}

void tambah_komik(komik kom[], int *index) {
    komik temp;

    clear_screen();
    tampil_header("Tambah Komik");

    cout << "Masukkan Judul komik: ";
    cin.ignore(); 
    getline(cin, temp.judul);

    cout << "Masukkan Penulis komik: ";
    getline(cin, temp.penulis);

    cout << "Masukkan Tahun Terbit komik: ";
    cin >> temp.tahunTerbit;
    cin.ignore();

    cout << "Masukkan Rating komik (1-10): ";
    cin >> temp.rating;
    cin.ignore();

    cout << "Masukkan Genre komik: ";
    getline(cin, temp.genre);

    kom[*index] = temp;
    *index += 1;
    clear_screen();
    cout << "Komik berhasil ditambahkan!" << endl;
}

void tampilkan_komik(komik kom[], int *index) {
    clear_screen();
    tampil_header("Daftar Komik");

    if (*index == 0) {
        cout << "Belum ada data komik yang terisi!" << endl;
        return;
    }

    for (int i = 0; i < *index; i++) {
        cout << i + 1 << ". " << "Judul: " << kom[i].judul << endl;
        cout << "   Penulis: " << kom[i].penulis << endl;
        cout << "   Tahun Terbit: " << kom[i].tahunTerbit << endl;
        cout << "   Rating: " << kom[i].rating << "/10" << endl;
        cout << "   Genre: " << kom[i].genre << endl;
        cout << "-------------------------------" << endl;
    }
}

void ubah_data(komik kom[], int *index) {
    string judul;
    int nomor = -1;

    clear_screen();
    tampil_header("Ubah Data Komik");

    if (*index == 0) {
        cout << "Tidak ada komik yang tersedia untuk diubah!" << endl;
        return;
    }

    cout << "Masukkan judul komik yang ingin diubah: ";
    cin.ignore();
    getline(cin, judul);

    for (int i = 0; i < *index; i++) {
        if (kom[i].judul == judul) {
            nomor = i;
            break;
        }
    }

    if (nomor != -1) {
        cout << "Masukkan Judul komik baru: ";
        getline(cin, kom[nomor].judul);

        cout << "Masukkan Penulis komik baru: ";
        getline(cin, kom[nomor].penulis);

        cout << "Masukkan Tahun Terbit baru: ";
        cin >> kom[nomor].tahunTerbit;
        cin.ignore();

        cout << "Masukkan Rating komik baru (1-10): ";
        cin >> kom[nomor].rating;
        cin.ignore();

        cout << "Masukkan Genre komik baru: ";
        getline(cin, kom[nomor].genre);

        clear_screen();
        cout << "Data komik berhasil diubah!" << endl;
    } else {
        cout << "Komik dengan judul \"" << judul << "\" tidak ditemukan!" << endl;
    }
}

void hapus_data(komik kom[], int *index) {
    string judul;
    int nomor = -1;

    clear_screen();
    tampil_header("Hapus Data Komik");

    if (*index == 0) {
        cout << "Tidak ada komik yang tersedia untuk dihapus!" << endl;
        return;
    }

    cout << "Masukkan judul komik yang ingin dihapus: ";
    cin.ignore();
    getline(cin, judul);

    for (int i = 0; i < *index; i++) {
        if (kom[i].judul == judul) {
            nomor = i;
            break;
        }
    }

    if (nomor != -1) {
        for (int i = nomor; i < *index - 1; i++) {
            kom[i] = kom[i + 1];
        }
        *index -= 1;
        clear_screen();
        cout << "Komik \"" << judul << "\" berhasil dihapus!" << endl;
    } else {
        cout << "Komik dengan judul \"" << judul << "\" tidak ditemukan!" << endl;
    }
}

int main() {
    clear_screen();
    komik kom[50];
    int index = 0;
    int pilihan;

    while (true) {
        cout << endl;
        tampil_header("Program Data Komik");
        cout << "1. Tambah Komik" << endl;
        cout << "2. Tampilkan Komik" << endl;
        cout << "3. Ubah Data Komik" << endl;
        cout << "4. Hapus Komik" << endl;
        cout << "5. Keluar Program" << endl;
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambah_komik(kom, &index);
                break;
            case 2:
                tampilkan_komik(kom, &index);
                break;
            case 3:
                ubah_data(kom, &index);
                break;
            case 4:
                hapus_data(kom, &index);
                break;
            case 5:
                clear_screen();
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                return 0;
            default:
                clear_screen();
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
                break;
        }
    }
}

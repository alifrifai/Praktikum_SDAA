#include <iostream>
#include <string>
using namespace std;

struct komik {
    string judul;
    string penulis;
    int tahunTerbit;
    int rating;
    string genre;
    komik* next; 
};

void clear_screen() {
    system("cls"); 
}

void tampil_header(string title) {
    cout << "=======================================" << endl;
    cout << "            " << title << endl;
    cout << "=======================================" << endl;
}

void tambah_komik(komik** head) {
    komik* temp = new komik;
    temp->next = nullptr;

    clear_screen();
    tampil_header("Tambah Komik");

    cout << "Masukkan Judul komik: ";
    cin.ignore();
    getline(cin, temp->judul);

    cout << "Masukkan Penulis komik: ";
    getline(cin, temp->penulis);

    cout << "Masukkan Tahun Terbit komik: ";
    cin >> temp->tahunTerbit;
    cin.ignore();

    cout << "Masukkan Rating komik (1-10): ";
    cin >> temp->rating;
    cin.ignore();

    cout << "Masukkan Genre komik: ";
    getline(cin, temp->genre);

    if (*head == nullptr) {
        *head = temp;
    } else {
        komik* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
    }

    clear_screen();
    cout << "Komik berhasil ditambahkan!" << endl;
}

void tampilkan_komik(komik* head) {
    clear_screen();
    tampil_header("Daftar Komik");

    if (head == nullptr) {
        cout << "Belum ada data komik yang terisi!" << endl;
        return;
    }

    int i = 1;
    komik* current = head;
    while (current != nullptr) {
        cout << i++ << ". " << "Judul: " << current->judul << endl;
        cout << "   Penulis: " << current->penulis << endl;
        cout << "   Tahun Terbit: " << current->tahunTerbit << endl;
        cout << "   Rating: " << current->rating << "/10" << endl;
        cout << "   Genre: " << current->genre << endl;
        cout << "-------------------------------" << endl;
        current = current->next;
    }
}

void ubah_data(komik* head) {
    string judul;
    komik* current = head;

    clear_screen();
    tampil_header("Ubah Data Komik");

    if (head == nullptr) {
        cout << "Tidak ada komik yang tersedia untuk diubah!" << endl;
        return;
    }

    cout << "Masukkan judul komik yang ingin diubah: ";
    cin.ignore();
    getline(cin, judul);

    while (current != nullptr && current->judul != judul) {
        current = current->next;
    }

    if (current != nullptr) {
        cout << "Masukkan Judul komik baru: ";
        getline(cin, current->judul);

        cout << "Masukkan Penulis komik baru: ";
        getline(cin, current->penulis);

        cout << "Masukkan Tahun Terbit baru: ";
        cin >> current->tahunTerbit;
        cin.ignore();

        cout << "Masukkan Rating komik baru (1-10): ";
        cin >> current->rating;
        cin.ignore();

        cout << "Masukkan Genre komik baru: ";
        getline(cin, current->genre);

        clear_screen();
        cout << "Data komik berhasil diubah!" << endl;
    } else {
        cout << "Komik dengan judul \"" << judul << "\" tidak ditemukan!" << endl;
    }
}

void hapus_data(komik** head) {
    string judul;
    komik* current = *head;
    komik* prev = nullptr;

    clear_screen();
    tampil_header("Hapus Data Komik");

    if (*head == nullptr) {
        cout << "Tidak ada komik yang tersedia untuk dihapus!" << endl;
        return;
    }

    cout << "Masukkan judul komik yang ingin dihapus: ";
    cin.ignore();
    getline(cin, judul);

    while (current != nullptr && current->judul != judul) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev == nullptr) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        clear_screen();
        cout << "Komik \"" << judul << "\" berhasil dihapus!" << endl;
    } else {
        cout << "Komik dengan judul \"" << judul << "\" tidak ditemukan!" << endl;
    }
}

int main() {
    komik* head = nullptr; 
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
                tambah_komik(&head);
                break;
            case 2:
                tampilkan_komik(head);
                break;
            case 3:
                ubah_data(head);
                break;
            case 4:
                hapus_data(&head);
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

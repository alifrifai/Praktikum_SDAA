#include <iostream>
#include <string>
#include <cmath> 
#include <vector> 
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

void push_stack(komik** head) {
    komik* temp = new komik;
    temp->next = nullptr;

    clear_screen();
    tampil_header("Push Komik (Stack)");

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

    temp->next = *head;
    *head = temp;

    clear_screen();
    cout << "Komik berhasil ditambahkan menggunakan Stack!" << endl;
}

void enqueue(komik** head) {
    komik* temp = new komik;
    temp->next = nullptr;

    clear_screen();
    tampil_header("Enqueue Komik (Queue)");

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
    cout << "Komik berhasil di-enqueue!" << endl;
}

void ubah_data(komik* head) {
    if (!head) {
        cout << "Tidak ada data komik untuk diubah!" << endl;
        return;
    }

    string judul;
    cout << "Masukkan judul komik yang ingin diubah: ";
    cin.ignore();
    getline(cin, judul);

    komik* current = head;
    while (current && current->judul != judul) {
        current = current->next;
    }

    if (current) {
        cout << "Masukkan Judul baru: ";
        getline(cin, current->judul);
        cout << "Masukkan Penulis baru: ";
        getline(cin, current->penulis);
        cout << "Masukkan Tahun Terbit baru: ";
        cin >> current->tahunTerbit;
        cin.ignore();
        cout << "Masukkan Rating baru (1-10): ";
        cin >> current->rating;
        cin.ignore();
        cout << "Masukkan Genre baru: ";
        getline(cin, current->genre);

        cout << "Data komik berhasil diubah!" << endl;
    } else {
        cout << "Komik dengan judul \"" << judul << "\" tidak ditemukan!" << endl;
    }
}

void hapus_data(komik** head) {
    if (!*head) {
        cout << "Tidak ada komik untuk dihapus!" << endl;
        return;
    }

    string judul;
    cout << "Masukkan judul komik yang ingin dihapus: ";
    cin.ignore();
    getline(cin, judul);

    komik* current = *head;
    komik* prev = nullptr;

    while (current && current->judul != judul) {
        prev = current;
        current = current->next;
    }

    if (current) {
        if (prev) {
            prev->next = current->next;
        } else {
            *head = current->next;
        }
        delete current;
        cout << "Komik berhasil dihapus!" << endl;
    } else {
        cout << "Komik dengan judul \"" << judul << "\" tidak ditemukan!" << endl;
    }
}

void split_list(komik* source, komik** front, komik** back) {
    komik* slow = source;
    komik* fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

komik* merge_sorted_tahun(komik* a, komik* b) {
    if (!a) return b;
    if (!b) return a;

    komik* result = nullptr;
    if (a->tahunTerbit <= b->tahunTerbit) {
        result = a;
        result->next = merge_sorted_tahun(a->next, b);
    } else {
        result = b;
        result->next = merge_sorted_tahun(a, b->next);
    }
    return result;
}

void merge_sort_tahun(komik** head_ref) {
    komik* head = *head_ref;
    if (!head || !head->next) return;

    komik* front;
    komik* back;
    split_list(head, &front, &back);

    merge_sort_tahun(&front);
    merge_sort_tahun(&back);

    *head_ref = merge_sorted_tahun(front, back);
}

komik* partition(komik* head, komik* end, komik** newHead, komik** newEnd) {
    komik* pivot = end;
    komik* prev = nullptr;
    komik* current = head;
    komik* tail = pivot;

    while (current != pivot) {
        if (current->tahunTerbit >= pivot->tahunTerbit) { 
            if (*newHead == nullptr) *newHead = current;
            prev = current;
            current = current->next;
        } else {
            if (prev) prev->next = current->next;
            komik* temp = current->next;
            current->next = nullptr;
            tail->next = current;
            tail = current;
            current = temp;
        }
    }

    if (*newHead == nullptr) *newHead = pivot;
    *newEnd = tail;

    return pivot;
}

komik* quick_sort_recursive(komik* head, komik* end) {
    if (!head || head == end) return head;  

    komik* newHead = nullptr;
    komik* newEnd = nullptr;

    komik* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        komik* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newHead = quick_sort_recursive(newHead, temp);

        temp = newHead;
        while (temp->next) temp = temp->next;
        temp->next = pivot;
    }

    pivot->next = quick_sort_recursive(pivot->next, newEnd);
    return newHead;
}

void quick_sort_tahun(komik** head_ref) {
    komik* end = *head_ref;
    while (end && end->next) end = end->next; 
    *head_ref = quick_sort_recursive(*head_ref, end);
}

void tampilkan_komik(komik* head) {
    clear_screen();
    tampil_header("Daftar Komik");

    if (!head) {
        cout << "Belum ada data komik yang terisi!" << endl;
        return;
    }

    int i = 1;
    komik* current = head;
    while (current) {
        cout << i++ << ". Judul: " << current->judul << endl;
        cout << "   Penulis: " << current->penulis << endl;
        cout << "   Tahun Terbit: " << current->tahunTerbit << endl;
        cout << "   Rating: " << current->rating << "/10" << endl;
        cout << "   Genre: " << current->genre << endl;
        cout << "-------------------------------" << endl;
        current = current->next;
    }
}

int fibonacci_search(vector<int>& arr, int x, int n) {
    int fib2 = 0;
    int fib1 = 1;
    int fibM = fib2 + fib1;

    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fib2, n - 1);

        if (arr[i] < x) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && arr[offset + 1] == x) {
        return offset + 1;
    }

    return -1;
}

int jump_search(vector<int>& arr, int x, int n) {
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if (arr[i] == x) return i;
    }

    return -1;
}

int boyer_moore_search(string text, string pattern) {
    int m = pattern.size();
    int n = text.size();
    if (m == 0) return -1;

    int bad_char[256];

    for (int i = 0; i < 256; i++) {
        bad_char[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        bad_char[(int)pattern[i]] = i;
    }

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            return s;
        } else {
            s += max(1, j - bad_char[(int)text[s + j]]);
        }
    }

    return -1;
}

void search_by_tahun(komik* head) {
    if (!head) {
        cout << "Data komik kosong!" << endl;
        return;
    }

    vector<pair<int, komik*>> tahunTerbitList;
    komik* current = head;

    // Sinkronisasi: Simpan tahun dan pointer ke komik
    while (current) {
        tahunTerbitList.push_back({current->tahunTerbit, current});
        current = current->next;
    }

    int pilihan_search, tahunCari;
    cout << "Pilih metode pencarian tahun terbit:\n1. Fibonacci Search\n2. Jump Search" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan_search;
    cout << "Masukkan tahun terbit yang ingin dicari: ";
    cin >> tahunCari;

    // Ekstrak hanya tahun terbit untuk pencarian
    vector<int> tahunOnly;
    for (auto& pair : tahunTerbitList) {
        tahunOnly.push_back(pair.first);
    }

    int index = -1;
    if (pilihan_search == 1) {
        index = fibonacci_search(tahunOnly, tahunCari, tahunOnly.size());
    } else if (pilihan_search == 2) {
        index = jump_search(tahunOnly, tahunCari, tahunOnly.size());
    }

    if (index != -1) {
        // Ambil komik yang sesuai dengan indeks
        komik* found = tahunTerbitList[index].second;
        cout << "\nKomik dengan tahun terbit " << tahunCari << " ditemukan:\n";
        cout << "-------------------------------" << endl;
        cout << "Judul: " << found->judul << endl;
        cout << "Penulis: " << found->penulis << endl;
        cout << "Tahun Terbit: " << found->tahunTerbit << endl;
        cout << "Rating: " << found->rating << "/10" << endl;
        cout << "Genre: " << found->genre << endl;
        cout << "-------------------------------" << endl;
    } else {
        cout << "Komik dengan tahun terbit " << tahunCari << " tidak ditemukan!" << endl;
    }
}

void search_by_string(komik* head) {
    if (!head) {
        cout << "Data komik kosong!" << endl;
        return;
    }

    string keyword;
    cout << "Masukkan judul atau penulis yang ingin dicari: ";
    cin.ignore();
    getline(cin, keyword);

    komik* current = head;
    bool found = false;
    while (current) {
        if (boyer_moore_search(current->judul, keyword) != -1 || boyer_moore_search(current->penulis, keyword) != -1) {
            cout << "Komik ditemukan: " << endl;
            cout << "Judul: " << current->judul << endl;
            cout << "Penulis: " << current->penulis << endl;
            cout << "Tahun Terbit: " << current->tahunTerbit << endl;
            cout << "Rating: " << current->rating << "/10" << endl;
            cout << "Genre: " << current->genre << endl;
            cout << "-------------------------------" << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Komik dengan keyword \"" << keyword << "\" tidak ditemukan!" << endl;
    }
}

int main() {
    komik* head = nullptr;
    int pilihan;

    while (true) {
        cout << endl;
        tampil_header("Program Data Komik");
        cout << "1. Push Komik (Stack)" << endl;
        cout << "2. Enqueue Komik (Queue)" << endl;
        cout << "3. Tampilkan Komik" << endl;
        cout << "4. Ubah Data Komik" << endl;
        cout << "5. Hapus Komik" << endl;
        cout << "6. Sorting Ascending by Tahun (Merge Sort)" << endl;
        cout << "7. Sorting Descending by Tahun (Quick Sort)" << endl;
        cout << "8. Search by Tahun" << endl;
        cout << "9. Search by Judul/Penulis" << endl;
        cout << "10. Keluar Program" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                push_stack(&head);
                break;
            case 2:
                enqueue(&head);
                break;
            case 3:
                tampilkan_komik(head);
                break;
            case 4:
                ubah_data(head);
                break;
            case 5:
                hapus_data(&head);
                break;
            case 6:
                merge_sort_tahun(&head);
                cout << "Data diurutkan secara ascending!" << endl;
                tampilkan_komik(head); 
                break;
            case 7:
                quick_sort_tahun(&head);
                cout << "Data diurutkan secara descending!" << endl;
                tampilkan_komik(head);  
                break;
            case 8:
                search_by_tahun(head);
                break;
            case 9:
                search_by_string(head);
                break;
            case 10:
                cout << "Terima kasih! Program selesai." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}

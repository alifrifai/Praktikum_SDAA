#include <iostream>

using namespace std;

int konfersi(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return konfersi(n - 1, k - 1) + konfersi(n - 1, k);
}

void cetakPascalRec(int baris, int i) {
    if (i > baris)
        return;
    cout << konfersi(baris, i) << " ";
    cetakPascalRec(baris, i + 1);
}

void cetakPascal(int tingkat, int baris = 0) {
    if (baris == tingkat)
        return;
    cetakPascalRec(baris, 0);
    cout << endl;
    cetakPascal(tingkat, baris + 1);
}

int main() {
    int tingkat = 3;
    cout << "Hasil dari perhitungan pascal tingkat 3:" << endl;
    cetakPascal(tingkat);
}
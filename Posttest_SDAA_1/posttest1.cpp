#include <iostream>
using namespace std;

int binomial(int n, int k) {
    int hasil = 1;

    if (k > n - k) {
        k = n - k;
    }

    for (int i = 0; i < k; i++) {
        hasil *= (n - i);
        hasil /= (i + 1);
    }

    return hasil;
}

void cetaksegitiga() {
    int derajat = 2; 
    for (int i = 0; i <= derajat; i++) {
        for (int j = 0; j <= i; j++) {
            cout << binomial(i, j) << " ";
        }
        cout << endl;
    }
}
int main() {
    cout << "Hasil dari segitiga pascal derajat (a + b)^2 adalah: " << endl;
    cetaksegitiga();
    return 0;
}

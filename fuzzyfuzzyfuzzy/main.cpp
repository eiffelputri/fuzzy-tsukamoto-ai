#include <iostream>

using namespace std;
double x_jumlah, data_jumlah[3];
double jarang_jumlah, lumayan_jumlah, sering_jumlah;

double x_nominal, data_nominal[3];
double sedikit_nominal, sedang_nominal, banyak_nominal;

double bonus, data_bonus[3];
double bKecil[4], bCukup[2], bBesar[3];

double sKecil[4], sCukup_N[2], sCukup_T[2], sBesar[3];

double tampung;

void input(){
    cout << "--------INPUT DATA JUMLAH TOP UP PER BULAN--------"<<endl;
    for(int i = 0; i <3; i++){
        cout << "Data ke-" << i + 1 << ": "; cin >> data_jumlah[i];
    }
    cout << "Berapa jumlah top up perbulannya? "; cin >> x_jumlah;

    cout << "\n--------INPUT DATA NOMINAL TOP UP PER BULAN--------"<<endl;
    for(int i = 0; i <3; i++){
        cout << "Data ke-" << i + 1 << ": "; cin >> data_nominal[i];
    }
    cout << "Berapa nominal top up perbulannya? "; cin >> x_nominal;

    cout << "\n--------INPUT DATA BONUS TOP UP PERBULAN--------"<<endl;
    for(int i = 0; i <3; i++){
        cout << "Data ke-" << i + 1 << ": "; cin >> data_bonus[i];
    }

}

void fuzzifikasi(){
    jarang_jumlah = 0.0;
    lumayan_jumlah = 0.0;
    sering_jumlah = 0.0;

    if (x_jumlah <= data_jumlah[0]) {
        jarang_jumlah = 1.0;
    }
    else if (x_jumlah > data_jumlah[0] && x_jumlah < data_jumlah[1]) {
        jarang_jumlah = (data_jumlah[1] - x_jumlah) / (data_jumlah[1] - data_jumlah[0]); // d-x/d-c
        lumayan_jumlah = (x_jumlah - data_jumlah[0]) / (data_jumlah[1] - data_jumlah[0]); // x-a/b-a
    }
    else if (x_jumlah == data_jumlah[1]) {
        lumayan_jumlah = 1.0;
    }

    else if (x_jumlah > data_jumlah[1] && x_jumlah < data_jumlah[2]) {
        lumayan_jumlah = (data_jumlah[2] - x_jumlah) / (data_jumlah[2] - data_jumlah[1]); // c-x/c-b
        sering_jumlah = (x_jumlah - data_jumlah[1]) / (data_jumlah[2] - data_jumlah[1]); // x-a/b-a
    }
    else if (x_jumlah >= data_jumlah[2]) {
        sering_jumlah = 1.0;
    }

    // Fuzzifikasi nominal top up
    sedikit_nominal = 0.0;
    sedang_nominal = 0.0;
    banyak_nominal = 0.0;

    if (x_nominal <= data_nominal[0]) {
        sedikit_nominal = 1.0;
    }
    else if (x_nominal > data_nominal[0] && x_nominal < data_nominal[1]) {
        sedikit_nominal = (data_nominal[1] - x_nominal) / (data_nominal[1] - data_nominal[0]);
        sedang_nominal = (x_nominal - data_nominal[0]) / (data_nominal[1] - data_nominal[0]);
    }
    else if (x_nominal == data_nominal[1]) {
        sedang_nominal = 1.0;
    }
    else if (x_nominal > data_nominal[1] && x_nominal < data_nominal[2]) {
        sedang_nominal = (data_nominal[2] - x_nominal) / (data_nominal[2] - data_nominal[1]);
        banyak_nominal = (x_nominal - data_nominal[1]) / (data_nominal[2] - data_nominal[1]);
    }
    else if (x_nominal >= data_nominal[2]) {
        banyak_nominal = 1.0;
    }

    // Menampilkan hasil fuzzifikasi
    cout << "\n--------HASIL FUZZIFIKASI--------" << endl;
    cout << "Jumlah Top Up: " << endl;
    cout << "Jarang: " << jarang_jumlah << endl;
    cout << "Lumayan: " << lumayan_jumlah << endl;
    cout << "Sering: " << sering_jumlah << endl;

    cout << "\nNominal Top Up: " << endl;
    cout << "Sedikit: " << sedikit_nominal << endl;
    cout << "Sedang: " << sedang_nominal << endl;
    cout << "Banyak: " << banyak_nominal << endl;
}

void rules(double a, double b, double *kesimpulan, int index)
{
    // AND
    tampung = min(a, b);
    kesimpulan[index] = max(tampung, kesimpulan[index]);
}

void kesimpulan() {
    cout << "\n--------KESIMPULAN BONUS YANG DI DAPAT--------" << endl;

    // Cetak nilai variabel bKecil
    cout << "Kecil: " << endl;
    for(int i = 0; i < 4; i++){
        if (bKecil[i] != 0){
            cout << "Kecil ke-" << i << ": " << bKecil[i] << endl;
        }
    }

    // Cetak nilai variabel bCukup
    cout << "\nCukup: " << endl;
    for(int i = 0; i < 2; i++){
        if (bCukup[i] != 0){
            cout << "Cukup ke-" << i << ": " << bCukup[i] << endl;
        }
    }

    cout << "\nBesar: " << endl;
    // Cetak nilai variabel bBesar
    for(int i = 0; i < 3; i++){
        if (bBesar[i] != 0){
            cout << "Besar ke-" << i << ": " << bBesar[i] << endl;
        }
    }
}

void sampel_tsukamoto(){
    sKecil[4] = {0.0};
    sCukup_N[2] = {0.0};
    sCukup_T[2] = {0.0};
    sBesar[3] = {0.0};

    cout << "\n--------HASIL SAMPLE--------" << endl;
    // Sampel Kecil (Trapesium)
    cout << "Sample Kecil: " << endl;
    for(int i = 0; i < 4; i++){
        if (bKecil[i] != 0){
            sKecil[i] = -((bKecil[i] * (data_bonus[1] - data_bonus[0])) - data_bonus[1]);
            cout << sKecil[i] << endl;
        }
    }

    // Sampel Cukup Naik (Segitiga)
    cout << "\nSample Cukup Naik: " << endl;
    for(int i = 0; i < 2; i++){
        if (bCukup[i] != 0){
            sCukup_N[i] = bCukup[i] * (data_bonus[1] - data_bonus[0]) + data_bonus[0];
            cout << sCukup_N[i] << endl;
        }
    }

    // Sampel Cukup Turun (Segitiga)
    cout << "\nSample Cukup Turun: " << endl;
    for(int i = 0; i < 2; i++){
        if (bCukup[i] != 0){
            sCukup_T[i] = -((bCukup[i] * (data_bonus[2] - data_bonus[1])) - data_bonus[2]);
            cout << sCukup_T[i] << endl;
        }
    }

    cout << "\nSample Besar: " << endl;
    // Sampel Besar (Trapesium)
    for(int i = 0; i < 3; i++){
        if (bBesar[i] != 0){
            sBesar[i] = bBesar[i] * (data_bonus[2] - data_bonus[1]) + data_bonus[1];
            cout << sBesar[i] << endl;
        }
    }
}

void defuzzifikasi() {
    cout << "\n--------DEFUZZIFIKASI--------" << endl;
    double pembilang = 0.0;
    double penyebut = 0.0;

    // pembilang n penyebut
    for (int i = 0; i < 4; i++) {
        pembilang += bKecil[i] * sKecil[i];
        penyebut += bKecil[i];
    }

    for (int i = 0; i < 2; i++) {
        pembilang += bCukup[i] * sCukup_N[i];
        penyebut += bCukup[i];
    }

    for (int i = 0; i < 2; i++) {
        pembilang += bCukup[i] * sCukup_T[i];
        penyebut += bCukup[i];
    }

    for (int i = 0; i < 3; i++) {
        pembilang += bBesar[i] * sBesar[i];
        penyebut += bBesar[i];
    }

    cout << "Pembilang: " << pembilang << endl;
    cout << "Penyebut: " << penyebut << endl;

    bonus = pembilang / penyebut;
    cout << "\nBonus yang didapat: " << bonus << endl;
}

int main()
{
    cout << "=====================KELOMPOK AI=====================" << endl;
    cout << "Clara Edrea Evelyna Sony Putri - A11.2021.13374" << endl;
    cout << "=====================================================\n" << endl;
    cout << "TEMA: FUZZY [TSUKAMOTO]\n" << endl;

    input();
    fuzzifikasi();

    rules(jarang_jumlah, sedikit_nominal, bKecil, 0);
    rules(jarang_jumlah, sedang_nominal, bKecil, 1);
    rules(jarang_jumlah, banyak_nominal, bCukup, 0);
    rules(lumayan_jumlah, sedikit_nominal, bKecil, 2);
    rules(lumayan_jumlah, sedang_nominal, bCukup, 1);
    rules(lumayan_jumlah, banyak_nominal, bBesar, 0);
    rules(sering_jumlah, sedikit_nominal, bKecil, 3);
    rules(sering_jumlah, sedang_nominal, bBesar, 1);
    rules(sering_jumlah, banyak_nominal, bBesar, 2);

    kesimpulan();
    sampel_tsukamoto();
    defuzzifikasi();

    return 0;
}

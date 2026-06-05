#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    int stok;
    int harga;
};

// Fungsi untuk menambah barang
void tambahBarang(vector<Barang>& daftarBarang) {
    system("cls");
    int jumlahBarang;
    cout << "Masukkan jumlah barang yang ingin ditambahkan: ";
    cin >> jumlahBarang;
    cin.ignore();
    system("cls");

    for (int i = 0; i < jumlahBarang; i++) {
        Barang b;
        cout << "=========== Barang " << (i + 1) << " ==========" << endl;
        cout << "Masukkan kode barang: ";
        getline(cin, b.kodeBarang);
        cout << "Masukkan nama barang: ";
        getline(cin, b.namaBarang);
        cout << "Masukkan stok barang: ";
        cin >> b.stok;
        cout << "Masukkan harga barang: ";
        cin >> b.harga;
        while (b.stok < 0 || b.harga < 0) {
            cout << "\nStok dan harga tidak boleh negatif. Silakan masukkan kembali." << endl;
            cout << "Masukkan stok barang: ";
            cin >> b.stok;
            cout << "Masukkan harga barang: ";
            cin >> b.harga;
        }
        cin.ignore();
        daftarBarang.push_back(b);
        cout << "\n";
    }
}

// Fungsi untuk menampilkan daftar barang
void tampilkanBarang(const vector<Barang>& daftarBarang) {
    system("cls");
    if (daftarBarang.empty()) {
        cout << "Belum ada barang yang dimasukkan!" << endl;
    } else {
        cout << "=========== Daftar Barang ==========" << endl;
        for (int i = 0; i < daftarBarang.size(); i++) {
            cout << "=========== Barang " << (i + 1) << " ==========" << endl;
            cout << "\nKode Barang: " << daftarBarang[i].kodeBarang << endl;
            cout << "Nama Barang: " << daftarBarang[i].namaBarang << endl;  
            cout << "Stok Barang: " << daftarBarang[i].stok << endl;
            cout << "Harga Barang: " << daftarBarang[i].harga << endl;
        }
    }
    system("pause");
}

// Fungsi untuk mencari barang termahal
void cariBarangTermahal(const vector<Barang>& daftarBarang) {
    system("cls");
    if (daftarBarang.empty()) {
        cout << "Belum ada barang yang dimasukkan!" << endl;
    } else {
        Barang barangTermahal = daftarBarang[0];
        for (int i = 1; i < daftarBarang.size(); i++) {
            if (daftarBarang[i].harga > barangTermahal.harga) {
                barangTermahal = daftarBarang[i];
            }
        }
        cout << "Barang Termahal:" << endl;
        cout << "Kode Barang: " << barangTermahal.kodeBarang << endl;
        cout << "Nama Barang: " << barangTermahal.namaBarang << endl;
        cout << "Stok Barang: " << barangTermahal.stok << endl;
        cout << "Harga Barang: " << barangTermahal.harga << endl;
    }
    system("pause");
}

// Fungsi untuk menghitung total nilai inventaris
void hitungTotalNilaiInventaris(const vector<Barang>& daftarBarang) {
    system("cls");
    if (daftarBarang.empty()) {
        cout << "Belum ada barang yang dimasukkan!" << endl;
    } else {
        int totalSemua = 0;
        for (int i = 0; i < daftarBarang.size(); i++) {
            int totalNilai = daftarBarang[i].stok * daftarBarang[i].harga;
            totalSemua += totalNilai;
            cout << "=========== Barang " << (i + 1) << " ==========" << endl;
            cout << "Kode Barang: " << daftarBarang[i].kodeBarang << endl;
            cout << "Nama Barang: " << daftarBarang[i].namaBarang << endl;
            cout << "Stok Barang: " << daftarBarang[i].stok << endl;
            cout << "Harga Barang: " << daftarBarang[i].harga << endl;
            cout << "Total Nilai Inventaris: " << totalNilai << endl;
            cout << "================================================" << endl;
        }
        cout << "Total Semua Nilai Inventaris: " << totalSemua << endl;
    }
    system("pause");
}

// Fungsi untuk mengecek barang yang perlu restock
void cekRestock(const vector<Barang>& daftarBarang) {
    system("cls");
    if (daftarBarang.empty()) {
        cout << "Belum ada barang yang dimasukkan!" << endl;
    } else {
        cout << "Barang yang perlu restock (stok < 5):" << endl;
        for (int i = 0; i < daftarBarang.size(); i++) {
            if (daftarBarang[i].stok < 5) {
                cout << "=========== Barang " << (i + 1) << " ==========" << endl;
                cout << "Kode Barang: " << daftarBarang[i].kodeBarang << endl;
                cout << "Nama Barang: " << daftarBarang[i].namaBarang << endl;
                cout << "Stok Barang: " << daftarBarang[i].stok << endl;
                cout << "Harga Barang: " << daftarBarang[i].harga << endl;
            }
        }
    }
    system("pause");
}

// Fungsi untuk mengupdate stok barang
void updateStock(vector<Barang>& daftarBarang) {
    system("cls");
    if (daftarBarang.empty()) {
        cout << "Belum ada barang yang dimasukkan!" << endl;
    } else {
        string kode;
        cout << "Masukkan kode barang yang ingin diupdate: ";
        getline(cin, kode);
        int *pStock = nullptr;
        string namaBarang;
        for (int i = 0; i < daftarBarang.size(); i++) {
            if (daftarBarang[i].kodeBarang == kode) {
                pStock = &daftarBarang[i].stok;
                namaBarang = daftarBarang[i].namaBarang;
                break;
            }
        }
        if (pStock == nullptr) {
            cout << "Barang dengan kode tersebut tidak ditemukan!" << endl;
        } else {
            int stokBaru;
            cout << "Stok saat ini untuk " << namaBarang << ": " << *pStock << endl;
            cout << "==============================================================" << endl;
            cout << "1. Tambah Stok" << endl;
            cout << "2. Kurangi Stok" << endl;
            cout << "Pilih opsi: ";
            int opsi;
            cin >> opsi;
            if (opsi == 1) {
                cout << "Masukkan jumlah stok yang ingin ditambahkan: ";
                cin >> stokBaru;
                while (stokBaru < 0) {
                    cout << "Jumlah stok tidak boleh negatif. Silakan masukkan kembali." << endl;
                    cout << "Masukkan jumlah stok yang ingin ditambahkan: ";
                    cin >> stokBaru;
                }
                *pStock += stokBaru;
                cout << "Stok berhasil ditambahkan. Stok baru untuk " << namaBarang << ": " << *pStock << endl;
            } else if (opsi == 2) {
                cout << "Masukkan jumlah stok yang ingin dikurangi: ";
                cin >> stokBaru;
                while (stokBaru < 0 || stokBaru > *pStock) {
                    cout << "Jumlah stok tidak valid. Silakan masukkan kembali." << endl;
                    cout << "Masukkan jumlah stok yang ingin dikurangi: ";
                    cin >> stokBaru;
                }
                *pStock -= stokBaru;
                cout << "Stok berhasil dikurangi. Stok baru untuk " << namaBarang << ": " << *pStock << endl;
            } else {
                cout << "Opsi tidak valid!" << endl;
            }
        }
    }
    system("pause");
}

int main() {
    vector<Barang> daftarBarang;
    int pilihan;

    do {
        system("cls");
        cout << "=========== MENU ===========" << endl;
        cout << "1. Tambah Barang" << endl;
        cout << "2. Tampilkan Barang" << endl;
        cout << "3. Cari Barang Termahal" << endl;
        cout << "4. Hitung Total Nilai Inventaris" << endl;
        cout << "5. Cek Restock (stock < 5)" << endl;
        cout << "6. Update Stock" << endl;
        cout << "7. Keluar" << endl;
        cout << "============================" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(); 

        switch (pilihan) {
            case 1:
                tambahBarang(daftarBarang);
                break;
            case 2:
                tampilkanBarang(daftarBarang);
                break;
            case 3:
                cariBarangTermahal(daftarBarang);
                break;
            case 4:
                hitungTotalNilaiInventaris(daftarBarang);
                break;
            case 5:
                cekRestock(daftarBarang);
                break;
            case 6:
                updateStock(daftarBarang);
                break;
            case 7:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                system("pause");
        }
    } while (pilihan != 7);

    return 0;
}
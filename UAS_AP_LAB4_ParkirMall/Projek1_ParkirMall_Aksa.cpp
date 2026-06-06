#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <windows.h>
using namespace std;

class berbagaiOpsi {
public:
        int jumlahMobil = 0;
        vector<string> platMobil, merkMobil, warnaMobil;
        vector<time_t> waktuMasuk;

    void tambahkanDaftarKehadiran() {
        int tambahanMobil;
        cout << "Masukkan jumlah mobil yang akan di parkirkan : ";
        cin >> tambahanMobil;
        cin.ignore();

        if ((jumlahMobil + tambahanMobil) > 20) {
            cout << "Maaf, parkiran hanya dapat memuat 20 mobil !" << endl;
            return;
        }

        for (int i = 0; i < tambahanMobil; i++) {
            string temp;
            cout << "\nMobil ke " << jumlahMobil + i + 1 << endl;
            cout << "Masukkan plat mobil  : "; getline(cin, temp); platMobil.push_back(temp);
            cout << "Masukkan merk mobil  : "; getline(cin, temp); merkMobil.push_back(temp);
            cout << "Masukkan warna mobil : "; getline(cin, temp); warnaMobil.push_back(temp);
            waktuMasuk.push_back(time(0));
        }
        jumlahMobil += tambahanMobil;
    }

    void tampilkanDaftarKehadiran() {
        int n = 60;
        cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR : " << endl;
        cout << string(n, '=') << endl;

        for (int i = 0; i < jumlahMobil; i++ ) {
            double selisih = difftime(time(0), waktuMasuk[i]);
            int jam   = selisih / 3600;
            int menit = ((int)selisih % 3600) / 60;
            int detik = (int)selisih % 60;

            cout << "Mobil ke " << i+1 << endl;
            cout << "Plat mobil   : " << platMobil[i] << endl;
            cout << "Merk mobil   : " << merkMobil[i] << endl;
            cout << "Warna mobil  : " << warnaMobil[i] << endl;
            cout << "Waktu parkir : " << jam << " jam " << menit << " menit " << detik << " detik" << endl;
            cout << endl;
            cout << endl;
            cout << string(n, '=') << endl;
        }
    }    

    void pembayaran() {
        int n = 60;
        tampilkanDaftarKehadiran();

        string inputPlat;
        bool ketemu = false;

        cout << "(Ketik '0' untuk batal)" << endl;

        do {
            cout << "\nMasukkan plat mobil yang ingin dibayar : ";
            getline(cin, inputPlat);

            if (inputPlat == "0") {  
            cout << "Pembayaran dibatalkan." << endl;
            return;
        }

            for (int i = 0; i < jumlahMobil; i++) {
                if (inputPlat == platMobil[i]) {
                    double selisih = difftime(time(0), waktuMasuk[i]);
                    int jam   = selisih / 3600;
                    int menit = ((int)selisih % 3600) / 60;
                    int detik = (int)selisih % 60;
                    int totalMenit = (int)selisih / 60;
                    int biaya = max(1, totalMenit) * 500;

                    cout << "\nB I A Y A  P A R K I R : Rp" << biaya << endl;
                    cout << string(n, '=') << endl;

                    platMobil.erase(platMobil.begin() + i);
                    merkMobil.erase(merkMobil.begin() + i);
                    warnaMobil.erase(warnaMobil.begin() + i);
                    waktuMasuk.erase(waktuMasuk.begin() + i);
                    jumlahMobil--;

                    cout << "Mobil berhasil keluar dari parkiran." << endl;
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu) cout << "PLAT TIDAK DITEMUKAN !" << endl;

        } while (!ketemu);
    }
    
    void keluarProgram() {
        exit(0);
    }

};

void tampilanAwal(string &nama, string &ID){
    int n = 83, j = 27;

    cout << string(n, '=') << endl;
    cout << string(j, '-') << " S E L A M A T   D A T A N G " << string(j,'-') << endl;
    cout << string(j, ' ') << "DI PORTAL PARKIR KHUSUS MOBIL" << endl;
    cout << string(j, ' ') << "        MALL PRIENAL" << endl;
    cout << string(n, '=') << endl;
    cout << endl;
    cout << "Kami senang Anda telah hadir." << endl;
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini." << endl;
    cout << endl;
    cout << "Masukkan nama : ";
    getline(cin, nama);
    cout << "Masukkan ID   : ";
    cin >> ID;
}

int tampilanAwalOpsi(string &nama, string &ID){
    int n = 84, j = 26, opsi;

    cout << string(n, '=') << endl;
    cout << "Nama Petugas : " << nama << endl;
    cout << "ID Petugas   : " << ID << endl;
    cout << endl;
    cout << string(j, ' ') << "TERIMA KASIH ATAS KERJASAMANYA !\n";
    cout << string(j, '-') << " S E L A M A T  B E R T U G A S " << string(j,'-') << endl;
    cout << string(n, '=') << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Silahkan input opsi berikut dalam bentuk angka." << endl;
    cout << "1. Tambahkan Daftar Kendaraan\n";    
    cout << "2. Tampilkan Daftar Kendaraan\n";    
    cout << "3. Pembayaran\n";    
    cout << "4. Keluar Program\n";    
    cout << "Masukkan opsi : ";
    cin >> opsi;
    cin.ignore();
    return opsi;
}

int main() {
    string nama, ID;
    berbagaiOpsi obj;
    berbagaiOpsi* ptr = &obj;
    int opsiMain;

    system("cls");
    tampilanAwal(nama, ID);

    do{
        system("cls");
        opsiMain = tampilanAwalOpsi(nama, ID);

        if (opsiMain == 1){
            ptr->tambahkanDaftarKehadiran();
            system("pause");
        } else if(opsiMain == 2){
            ptr->tampilkanDaftarKehadiran();
            system("pause");
        } else if(opsiMain == 3){
            ptr->pembayaran();
            system("pause");   
        } else if(opsiMain == 4){
            ptr->keluarProgram();
        } else {
            cout << "Opsi tidak valid!" << endl;
            Sleep(2000);
        }
    } while(opsiMain != 4);
}

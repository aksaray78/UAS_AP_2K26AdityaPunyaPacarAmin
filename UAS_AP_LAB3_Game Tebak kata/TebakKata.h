#ifndef TEBAK_KATA_H
#define TEBAK_KATA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;


const int JUMLAH_KATA    = 21;
const int MAX_LEADERBOARD = 5;

const string bankKata[JUMLAH_KATA] = {
    "komputer", "algoritma", "variabel", "fungsi", "rekursi",
    "pointer", "struktur", "jaringan", "database", "enkripsi",
    "compiler", "iterator", "matriks", "bilangan", "operasi",
    "pemrograman", "looping", "kondisi", "antarmuka", "memori",
    "perangkat"
};

struct KataGame {
    string kataAsli;         
    string statusTebakan;     
    int    sisaNyawa;      
};

struct EntriLeaderboard {
    string nama;
    int    skor;
    string kesulitan;
};

EntriLeaderboard leaderboard[MAX_LEADERBOARD];
int jumlahEntri = 0;          

void inisialisasiGame(KataGame* game, const string& kata, int maxKesalahan) {
    game->kataAsli      = kata;
    game->sisaNyawa     = maxKesalahan;
    game->statusTebakan = string(kata.length(), '_');
}


void tampilHeader() {
    cout << "+==========================================+\n";
    cout << "|        GAME TEBAK KATA - by Nisa         |\n";
    cout << "+==========================================+\n\n";
}


void tampilStatus(const KataGame* game,
                  const char tebakanSalah[], int jumlahSalah) {
    // status tebakan dengan spasi antar karakter
    cout << "  Kata  : ";
    for (char c : game->statusTebakan) cout << c << ' ';
    cout << "\n";

    // nyawa ditampilkan sebagai angka
    cout << "  Nyawa : " << game->sisaNyawa << "\n";

    // huruf salah
    cout << "  Salah : ";
    if (jumlahSalah == 0) {
        cout << "(belum ada)";
    } else {
        for (int i = 0; i < jumlahSalah; i++) cout << tebakanSalah[i] << ' ';
    }
    cout << "\n\n";
}


int pilihKesulitan(string& namaTingkat) {
    int pilihan;
    cout << "  Pilih Tingkat Kesulitan:\n";
    cout << "  [1] Easy   (8 kesalahan)\n";
    cout << "  [2] Medium (6 kesalahan)\n";
    cout << "  [3] Hard   (4 kesalahan)\n";
    cout << "  Pilihan: ";
    cin  >> pilihan;

    switch (pilihan) {
        case 1: namaTingkat = "Easy";   return 8;
        case 2: namaTingkat = "Medium"; return 6;
        case 3: namaTingkat = "Hard";   return 4;
        default:
            cout << "  Input tidak valid, default ke Medium.\n";
            namaTingkat = "Medium";
            return 6;
    }
}


bool sudahDitebak(char huruf,
                  const KataGame* game,
                  const char tebakanSalah[], int jumlahSalah) {
    // cek di status tebakan (huruf benar)
    for (char c : game->statusTebakan)
        if (tolower(c) == huruf) return true;
    // cek di array salah
    for (int i = 0; i < jumlahSalah; i++)
        if (tebakanSalah[i] == huruf) return true;
    return false;
}


bool prosesTebakan(KataGame* game,
                   char huruf,
                   char tebakanSalah[], int* jumlahSalah) {
    bool benar = false;
    for (int i = 0; i < (int)game->kataAsli.length(); i++) {
        if (tolower(game->kataAsli[i]) == huruf) {
            game->statusTebakan[i] = game->kataAsli[i];
            benar = true;
        }
    }
    if (!benar) {
        tebakanSalah[*jumlahSalah] = huruf;
        (*jumlahSalah)++;
        game->sisaNyawa--;          
    }
    return benar;
}


bool kataTerbuka(const KataGame* game) {
    for (char c : game->statusTebakan)
        if (c == '_') return false;
    return true;
}


int hitungSkor(const KataGame* game, const string& namaTingkat) {
    int bonus = 0;
    if      (namaTingkat == "Easy")   bonus = 100;
    else if (namaTingkat == "Medium") bonus = 200;
    else                              bonus = 350;   
    return bonus + game->sisaNyawa * 50;
}


void simpanLeaderboard(const string& nama, int skor, const string& kesulitan) {
    if (jumlahEntri < MAX_LEADERBOARD) {
        leaderboard[jumlahEntri] = {nama, skor, kesulitan};
        jumlahEntri++;
    } else {
        // cari skor terendah
        int idxMin = 0;
        for (int i = 1; i < MAX_LEADERBOARD; i++)
            if (leaderboard[i].skor < leaderboard[idxMin].skor)
                idxMin = i;
        if (skor > leaderboard[idxMin].skor)
            leaderboard[idxMin] = {nama, skor, kesulitan};
    }

    // urutkan descending (bubble sort sederhana)
    for (int i = 0; i < jumlahEntri - 1; i++)
        for (int j = 0; j < jumlahEntri - 1 - i; j++)
            if (leaderboard[j].skor < leaderboard[j+1].skor)
                swap(leaderboard[j], leaderboard[j+1]);
}

// ---------- tampil leaderboard ----------
void tampilLeaderboard() {
    cout << "\n+==========================================+\n";
    cout << "|           *** LEADERBOARD ***            |\n";
    cout << "+------+---------------+-------+----------+\n";
    cout << "| No   |     Nama      |  Skor | Kesulitan|\n";
    cout << "+------+---------------+-------+----------+\n";
    if (jumlahEntri == 0) {
        cout << "|          (Belum ada data)               |\n";
    } else {
        for (int i = 0; i < jumlahEntri; i++) {
            printf("| %-4d | %-13s | %-5d | %-8s |\n",
                   i + 1,
                   leaderboard[i].nama.c_str(),
                   leaderboard[i].skor,
                   leaderboard[i].kesulitan.c_str());
        }
    }
    cout << "+------+---------------+-------+----------+\n\n";
}


void gunakanHint(KataGame* game) {
    if (game->sisaNyawa <= 1) {
        cout << "  [!] Nyawa terlalu sedikit untuk menggunakan hint!\n\n";
        return;
    }
    // buka huruf pertama yang masih underscore
    for (int i = 0; i < (int)game->kataAsli.length(); i++) {
        if (game->statusTebakan[i] == '_') {
            game->statusTebakan[i] = game->kataAsli[i];
            game->sisaNyawa--;
            cout << "  [HINT] Huruf ke-" << i + 1
                 << " adalah '" << game->kataAsli[i] << "' (-1 nyawa)\n\n";
            return;
        }
    }
    cout << "  Tidak ada huruf yang bisa dibuka lagi.\n\n";
}

#endif 


#include "TebakKata.h"   

int main() {
    srand((unsigned)time(nullptr));   

    char ulangLagi = 'Y';

    system("cls");
    tampilHeader();
    cout << "  Selamat datang di Game Tebak Kata!\n";
    cout << "  Ketik huruf untuk menebak.\n";
    cout << "  Ketik '?' untuk menggunakan HINT (-1 nyawa).\n\n";


    string namaPemain;
    cout << "  Masukkan nama Anda: ";
    cin  >> namaPemain;

    //  LOOP UTAMA GAME
    while (toupper(ulangLagi) == 'Y') {


        system("cls");
        tampilHeader();
        string namaTingkat;
        int maxKesalahan = pilihKesulitan(namaTingkat);

        // --- ambil kata acak ---
        int idxKata = rand() % JUMLAH_KATA;
        string kataRahasia = bankKata[idxKata];

        // --- inisialisasi state game ---
        KataGame game;
        inisialisasiGame(&game, kataRahasia, maxKesalahan);

        char tebakanSalah[26] = {};
        int  jumlahSalah      = 0;

        while (true) {

            system("cls");
            tampilHeader();
            cout << "  Tingkat: " << namaTingkat << "\n\n";
            tampilStatus(&game, tebakanSalah, jumlahSalah);

            if (kataTerbuka(&game)) {
                cout << "  [MENANG] SELAMAT! Kamu berhasil menebak kata: \""
                     << game.kataAsli << "\"\n\n";

                int skor = hitungSkor(&game, namaTingkat);
                cout << "  Skor kamu: " << skor << " poin\n\n";

                simpanLeaderboard(namaPemain, skor, namaTingkat);
                tampilLeaderboard();
                break;
            }

            if (game.sisaNyawa <= 0) {
                cout << "  [KALAH] GAME OVER! Nyawa habis.\n";
                cout << "  Kata rahasia adalah: \"" << game.kataAsli << "\"\n\n";
                tampilLeaderboard();
                break;
            }

            cout << "  Tebak huruf (atau '?' untuk hint): ";
            char input;
            cin >> input;
            input = tolower(input);

            if (input == '?') {
                gunakanHint(&game);
                continue;
            }

            if (!isalpha(input)) {
                cout << "  [!] Masukkan hanya satu huruf alfabet!\n";
                system("pause");
                continue;
            }

            if (sudahDitebak(input, &game, tebakanSalah, jumlahSalah)) {
                cout << "  [!] Huruf '" << input
                     << "' sudah pernah ditebak. Coba huruf lain!\n";
                system("pause");
                continue;
            }

            bool benar = prosesTebakan(&game, input,
                                       tebakanSalah, &jumlahSalah);
            if (benar) {
                cout << "  [OK] Benar! Huruf '" << input << "' ada dalam kata.\n";
            } else {
                cout << "  [X] Salah! Huruf '" << input << "' tidak ada. "
                     << "Sisa nyawa: " << game.sisaNyawa << "\n";
            }
            system("pause");

        }   

        cout << "  Apakah Anda ingin bermain lagi? (Y/N): ";
        cin  >> ulangLagi;

    }  

    system("cls");
    tampilHeader();
    cout << "  Terima kasih sudah bermain, " << namaPemain << "!\n";
    cout << "  Sampai jumpa lagi!\n\n";
    tampilLeaderboard();

    return 0;
}

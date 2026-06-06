#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int MAX_SIZE = 10;
static const int MIN_SIZE = 4;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class Minesweeper {
private:
    int board[MAX_SIZE][MAX_SIZE];
    bool revealed[MAX_SIZE][MAX_SIZE];
    bool flagged[MAX_SIZE][MAX_SIZE];

    int size;
    int totalBombs;
    int flagsLeft;
    bool gameOver;
    bool playerWon;
    bool bombsPlaced;

    time_t startTime;

    void initArrays() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                board[r][c] = 0;
                revealed[r][c] = false;
                flagged[r][c] = false;
            }
        }
    }

    void placeBombs(int safeR, int safeC) {
        int placed = 0;
        while (placed < totalBombs) {
            int r = rand() % size;
            int c = rand() % size;
            if ((r == safeR && c == safeC) || board[r][c] == -1) continue;
            board[r][c] = -1;
            placed++;
        }
    }

    void calculateNumbers() {
        int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
        int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (board[r][c] == -1) continue;
                int count = 0;
                for (int d = 0; d < 8; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr >= 0 && nr < size && nc >= 0 && nc < size && board[nr][nc] == -1) {
                        count++;
                    }
                }
                board[r][c] = count;
            }
        }
    }

    void floodFill(int r, int c) {
        if (r < 0 || r >= size || c < 0 || c >= size) return;
        if (revealed[r][c] || flagged[r][c]) return;
        if (board[r][c] == -1) return;

        revealed[r][c] = true;
        if (board[r][c] == 0) {
            int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
            int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};
            for (int d = 0; d < 8; d++) {
                floodFill(r + dr[d], c + dc[d]);
            }
        }
    }

    bool checkWin() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (board[r][c] == -1 && !flagged[r][c]) return false;
                if (board[r][c] != -1 && flagged[r][c]) return false;
            }
        }
        return true;
    }

    void revealAllBombs() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (board[r][c] == -1) revealed[r][c] = true;
            }
        }
    }

    int elapsedSeconds() const {
        return (int)(time(nullptr) - startTime);
    }

    void displayBoard() {
        clearScreen();
        cout << "\n";
        cout << "  +-----------------------------------------+\n";
        cout << "  |         MINESWEEPER++  [ " << size << "x" << size << " ]";
        if (size < 10) cout << "          |\n";
        else cout << "         |\n";
        cout << "  +-----------------------------------------+\n";

        int elapsed = bombsPlaced ? elapsedSeconds() : 0;
        int mm = elapsed / 60;
        int ss = elapsed % 60;
        cout << "  | Bom tersisa: " << flagsLeft << "   Waktu: ";
        if (mm < 10) cout << '0';
        cout << mm << ':';
        if (ss < 10) cout << '0';
        cout << ss << "                  |\n";
        cout << "  +-----------------------------------------+\n\n";

        cout << "     ";
        for (int c = 1; c <= size; c++) {
            cout << ' ' << c;
            if (c < 10) cout << ' ';
        }
        cout << "\n";

        cout << "     ";
        for (int c = 0; c < size; c++) cout << "---";
        cout << "-\n";

        for (int r = 0; r < size; r++) {
            if (r + 1 < 10) cout << "  " << (r + 1) << " |";
            else cout << " " << (r + 1) << " |";

            for (int c = 0; c < size; c++) {
                char cell;
                if (flagged[r][c] && !revealed[r][c]) {
                    cell = 'F';
                } else if (!revealed[r][c]) {
                    cell = '#';
                } else if (board[r][c] == -1) {
                    cell = '*';
                } else if (board[r][c] == 0) {
                    cell = '.';
                } else {
                    cell = (char)('0' + board[r][c]);
                }
                cout << ' ' << cell << ' ';
            }
            cout << "|\n";
        }

        cout << "     ";
        for (int c = 0; c < size; c++) cout << "---";
        cout << "-\n\n";

        cout << "  Legenda: # = tertutup | F = flag/tanda bom\n";
        cout << "            . = kosong  | * = bom (game over)\n";
        cout << "  Aksi: O = buka kotak  | T = tandai/hapus tanda\n\n";
    }

    bool isInBounds(int r, int c) {
        return (r >= 1 && r <= size && c >= 1 && c <= size);
    }

    bool processTurn() {
        char action;
        int row, col;

        cout << "  Masukkan aksi (O/T), baris, kolom\n";
        cout << "  Contoh: O 3 5  atau  T 2 4\n";
        cout << "  > ";

        cin >> action >> row >> col;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Format salah. Masukkan: O 3 5  atau  T 2 4\n\n";
            return false;
        }

        if (action >= 'a' && action <= 'z') action = (char)(action - ('a' - 'A'));

        if (action != 'O' && action != 'T') {
            cout << "  [!] Aksi tidak valid. Gunakan O (buka) atau T (tandai).\n\n";
            return false;
        }

        if (!isInBounds(row, col)) {
            cout << "  [!] Koordinat di luar papan. Baris & kolom harus 1-" << size << ".\n\n";
            return false;
        }

        int r = row - 1;
        int c = col - 1;

        if (!bombsPlaced) {
            placeBombs(r, c);
            calculateNumbers();
            bombsPlaced = true;
        }

        if (action == 'O') {
            if (revealed[r][c]) {
                cout << "  [!] Kotak (" << row << "," << col << ") sudah dibuka.\n\n";
                return false;
            }
            if (flagged[r][c]) {
                cout << "  [!] Kotak (" << row << "," << col << ") sedang ditandai. Hapus tanda dulu (T).\n\n";
                return false;
            }

            if (board[r][c] == -1) {
                revealed[r][c] = true;
                revealAllBombs();
                gameOver = true;
                playerWon = false;
            } else {
                floodFill(r, c);
                if (checkWin()) {
                    gameOver = true;
                    playerWon = true;
                }
            }
        } else {
            if (revealed[r][c]) {
                cout << "  [!] Kotak (" << row << "," << col << ") sudah dibuka, tidak bisa ditandai.\n\n";
                return false;
            }
            if (!flagged[r][c]) {
                flagged[r][c] = true;
                flagsLeft--;
            } else {
                flagged[r][c] = false;
                flagsLeft++;
            }

            if (checkWin()) {
                gameOver = true;
                playerWon = true;
            }
        }

        cin.ignore(1000, '\n');
        return true;
    }

public:
    Minesweeper() {
        size = 0;
        totalBombs = 0;
        flagsLeft = 0;
        gameOver = false;
        playerWon = false;
        bombsPlaced = false;
        startTime = 0;
    }

    bool setup() {
        clearScreen();
        cout << "\n  ============================================\n";
        cout << "          MINESWEEPER++ - Pengaturan\n";
        cout << "  ============================================\n\n";

        cout << "  Masukkan ukuran papan N x N (" << MIN_SIZE << " - " << MAX_SIZE << "): ";
        cin >> size;
        if (cin.fail() || size < MIN_SIZE || size > MAX_SIZE) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Ukuran tidak valid!\n";
            return false;
        }

        int maxBombs = (size * size * 35) / 100;
        if (maxBombs < 1) maxBombs = 1;
        cout << "  Masukkan jumlah bom (1 - " << maxBombs << "): ";
        cin >> totalBombs;
        if (cin.fail() || totalBombs < 1 || totalBombs > maxBombs) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Jumlah bom tidak valid!\n";
            return false;
        }

        flagsLeft = totalBombs;
        gameOver = false;
        playerWon = false;
        bombsPlaced = false;
        startTime = 0;
        initArrays();
        cin.ignore(1000, '\n');
        return true;
    }

    void play() {
        startTime = time(nullptr);

        while (!gameOver) {
            displayBoard();
            bool valid = false;
            while (!valid) {
                valid = processTurn();
            }
        }

        displayBoard();

        int elapsed = elapsedSeconds();
        int mm = elapsed / 60;
        int ss = elapsed % 60;

        if (playerWon) {
            cout << "  ==========================================\n";
            cout << "   *** SELAMAT! Anda menang! ***\n";
            cout << "   Semua bom berhasil ditemukan!\n";
            cout << "   Waktu bermain: ";
            if (mm < 10) cout << '0';
            cout << mm << ':';
            if (ss < 10) cout << '0';
            cout << ss << "\n";
            cout << "  ==========================================\n\n";
        } else {
            cout << "  ==========================================\n";
            cout << "   *** AKU NAK MELETOP, DUAR! ***\n";
            cout << "   Waktu bermain: ";
            if (mm < 10) cout << '0';
            cout << mm << ':';
            if (ss < 10) cout << '0';
            cout << ss << "\n";
            cout << "  ==========================================\n\n";
        }

        cout << "  Tekan Enter untuk kembali ke menu...";
        cin.get();
    }
};

void printBanner() {
    cout << "\n";
    cout << "  ==========================================\n";
    cout << "  ||                                      ||\n";
    cout << "  ||        M I N E S W E E P E R         ||\n";
    cout << "  ||                 + +                  ||\n";
    cout << "  ||        Jangan sampai meletop!!!      ||\n";
    cout << "  ||                                      ||\n";
    cout << "  ==========================================\n\n";
}

void printMenu() {
    cout << "  +--------------------------+\n";
    cout << "  |       MENU UTAMA         |\n";
    cout << "  +--------------------------+\n";
    cout << "  | 1. Mulai Permainan Baru  |\n";
    cout << "  | 2. Cara Bermain          |\n";
    cout << "  | 3. Keluar                |\n";
    cout << "  +--------------------------+\n";
    cout << "  Pilihan: ";
}

void printHelp() {
    clearScreen();
    cout << "\n";
    cout << "  ============================================\n";
    cout << "               CARA BERMAIN\n";
    cout << "  ============================================\n\n";
    cout << "  Tujuan:\n";
    cout << "    Tandai semua kotak yang berisi bom dengan\n";
    cout << "    benar tanpa membuka satu pun bom.\n\n";
    cout << "  Aturan:\n";
    cout << "    - Papan berukuran N x N (pilih 4 - 10).\n";
    cout << "    - Angka pada kotak = jumlah bom di sekitar.\n";
    cout << "    - Kotak kosong (.) tidak ada bom di dekatnya.\n\n";
    cout << "  Aksi:\n";
    cout << "    O baris kolom  -> Buka kotak (contoh: O 3 5)\n";
    cout << "    T baris kolom  -> Pasang/hapus tanda F pada\n";
    cout << "                      kotak yang dicurigai bom\n\n";
    cout << "  Kondisi Menang:\n";
    cout << "    Semua bom berhasil ditandai dengan flag (F),\n";
    cout << "    dan tidak ada flag yang salah tempat.\n\n";
    cout << "  Kondisi Kalah:\n";
    cout << "    Membuka kotak yang berisi bom (*)\n\n";
    cout << "  Tips:\n";
    cout << "    - Bom pertama aman - tidak akan ada bom di\n";
    cout << "      kotak pertama yang Anda buka.\n";
    cout << "    - Kotak kosong (.) akan membuka area sekitar\n";
    cout << "      secara otomatis.\n";
    cout << "  ============================================\n\n";
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.get();
}

int main() {
    srand((unsigned int)time(nullptr));
    clearScreen();
    printBanner();

    bool running = true;
    while (running) {
        printMenu();

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Pilihan tidak valid.\n\n";
            continue;
        }
        cin.ignore(1000, '\n');

        switch (choice) {
            case 1: {
                Minesweeper game;
                bool ok = game.setup();
                if (ok) {
                    game.play();
                } else {
                    cout << "  [!] Pengaturan gagal. Kembali ke menu.\n\n";
                }
                clearScreen();
                printBanner();
                break;
            }
            case 2:
                printHelp();
                clearScreen();
                printBanner();
                break;
            case 3:
                clearScreen();
                cout << "\n  Terima kasih sudah bermain! Sampai jumpa!\n\n";
                running = false;
                break;
            default:
                cout << "  [!] Pilihan tidak valid. Masukkan 1, 2, atau 3.\n\n";
                break;
        }
    }

    return 0;
}

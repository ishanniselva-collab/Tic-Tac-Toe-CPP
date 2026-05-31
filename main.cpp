#include <iostream>
#include <array>
using namespace std;

// ─── Board ───────────────────────────────────────────────────────────────────

array<char, 9> board;

void initBoard() {
    for (int i = 0; i < 9; i++) board[i] = '1' + i;
}

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << board[i];
        if ((i + 1) % 3 == 0) {
            cout << "\n";
            if (i < 8) cout << "---+---+---\n";
        } else {
            cout << " |";
        }
    }
    cout << "\n";
}

// ─── Win / Draw Detection ─────────────────────────────────────────────────────

const int WIN_COMBOS[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},  // rows
    {0,3,6}, {1,4,7}, {2,5,8},  // cols
    {0,4,8}, {2,4,6}             // diagonals
};

bool checkWin(char mark) {
    for (auto& combo : WIN_COMBOS) {
        if (board[combo[0]] == mark &&
            board[combo[1]] == mark &&
            board[combo[2]] == mark)
            return true;
    }
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 9; i++)
        if (board[i] != 'X' && board[i] != 'O')
            return false;
    return true;
}

// ─── Move Input ───────────────────────────────────────────────────────────────

int getMove(char mark) {
    int pos;
    while (true) {
        cout << "Player " << mark << ", enter position (1-9): ";
        cin >> pos;
        pos--;  // convert to 0-indexed
        if (pos >= 0 && pos < 9 && board[pos] != 'X' && board[pos] != 'O') {
            return pos;
        }
        cout << "  Invalid move. Try again.\n";
    }
}

// ─── Score Tracking ───────────────────────────────────────────────────────────

struct Scores { int x = 0, o = 0, draws = 0; };

void showScores(const Scores& s) {
    cout << "\n--- Scoreboard ---\n";
    cout << "  X: " << s.x << "  |  O: " << s.o << "  |  Draws: " << s.draws << "\n";
    cout << "------------------\n\n";
}

// ─── Main Game Loop ───────────────────────────────────────────────────────────

int main() {
    Scores scores;
    char replay = 'y';

    cout << "=========================\n";
    cout << "     TIC TAC TOE\n";
    cout << "=========================\n";
    cout << "Positions are numbered 1-9:\n";
    cout << " 1 | 2 | 3\n---+---+---\n 4 | 5 | 6\n---+---+---\n 7 | 8 | 9\n\n";

    while (replay == 'y' || replay == 'Y') {
        initBoard();
        char currentPlayer = 'X';
        bool gameOver = false;

        cout << "New round!\n";

        while (!gameOver) {
            displayBoard();
            int pos = getMove(currentPlayer);
            board[pos] = currentPlayer;

            if (checkWin(currentPlayer)) {
                displayBoard();
                cout << "*** Player " << currentPlayer << " wins! ***\n";
                (currentPlayer == 'X' ? scores.x : scores.o)++;
                gameOver = true;
            } else if (checkDraw()) {
                displayBoard();
                cout << "*** It's a draw! ***\n";
                scores.draws++;
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        showScores(scores);
        cout << "Play again? (y/n): ";
        cin >> replay;
        cout << "\n";
    }

    cout << "Thanks for playing!\n";
    showScores(scores);
    return 0;
}

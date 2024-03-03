#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "Asset.cpp"
#include "Leaderboard.cpp"

using namespace std;

int title_screen();
int playground();
int leaderboard();

// Get key from keyboard
char getcommand() {
    return toupper(getch());
}

void close() {
    cout << "Invalid command.\n";
    Sleep(1500);
}

int title_screen() {
    while (true) {
        system("cls");
        title();
        menu();
        char key = getcommand();
        switch (key) {
            case 'E':
                return 0;
            case 'A':
                playground();
                break;
            case 'B':
                leaderboard();
                break;
            default:
                close();
                break;
        }
    }
}

int leaderboard() {
    while (true) {
        system("cls");
        l_board();
        cout << "\n( Return to menu: E )";
        char key = getcommand();
        if (key == 'E') return 0;
        else close();
    }
}

int playground() {
    while (true) {
        system("cls");
        cout << "\n( Return to menu: E )";
        char key = getcommand();
        if (key == 'E') return 0;
        else close();
    }
}

int main() {
    srand(time(0));
    title_screen();
    return 0;
}

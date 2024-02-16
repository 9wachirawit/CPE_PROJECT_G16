#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
using namespace std;

const int width = 150, height = 35;
int screen[width][width] = {};

void drawBlock(int x, int y, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    COORD pos = {x * 2, y};
    SetConsoleCursorPosition(hConsole, pos);
    cout << "�";
}

int drawField(string a) {
	
    system("cls");
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (screen[x][y] == 0)
                cout <<a;
            else
                drawBlock(x, y, screen[x][y]);
        }
        cout << endl;
    }
}


/* inprogress
int findhistory(string tag){
	ifstream tagfinder;
	tagfinder.open("save\\saveid.txt"); 
	ofstream tagEdit("save\\saveid.txt",ios::app);
	string tagcheck;
	int i = 0;
	while (getline(tagfinder, tagcheck))
	{
		if(tag == tagcheck){
			return i;
		}
		i += 1 ;
	}
	return -1;
}
*/


int main(void) {
	//ios_base::sync_with_stdio(false); speed  up
	string a = ".";
	int j = 0;
	while (j == 0) { 

        drawField(a);
        Sleep(1000); // Delay 500 milliseconds
    	if (_kbhit()) {
            char key = _getch();
            if (key == 'A' || key == 'a') {
                if(a == "-"){
                	a = ".";
				}
				else{
					a = "-";
				}
            }

    }

    }

    return 0;
}

#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
using namespace std;

const int width = 100, height = 26;
int screen[height][width] = {};
string A = "o";

//Zaoshang hao zhongguó xiànzài wo you bingqílín wo hen xihuan bingqílín
void buildscene(int (&x)[height][width], int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if (((i==1) and (j >= 25) and (j <= 74) and (j != 37) and (j != 38) and (j != 51) and (j != 52)) or ((i==22) and (j >= 25) and (j <= 74) and (j != 37) and (j != 38) and (j != 51) and (j != 52)) or ((i==24) and (j >= 25) and (j <= 74)) or ((j==25) and (i >= 1) and (i <= 22)) or ((j==74) and (i >= 1) and (i <= 22)) or ((j==36) and (i >= 1) and (i <= 22)) or ((j==39) and (i >= 1) and (i <= 22)) or ((j==50) and (i >= 1) and (i <= 22)) or ((j==53) and (i >= 1) and (i <= 22))) {
                x[i][j] = 1;
            } else {
                x[i][j] = 0;
            }
        }
    }
}

//kaizer job
/*void monsterspawn(int (&x)[height][width], int width, int height){
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
    
        }
    }
}*/

//read_and_show_scene inprogress 
int drawField(int (&screen)[height][width], int width, int height) {
	buildscene(screen, width, height);
	system("cls");
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
                if(screen[y][x] == 0){
                	cout << " ";
				} else {
                	cout << A;
				}
        }
        cout << endl;
    
    }
}


//keyboard system inprogress 
int keyboard(char key,string &A){
	if (key == 'A' || key == 'a') {
                A = "<";
            }
        else if(key == 'D' || key == 'd'){
        	A = "O";
				}
			else if(key == 'W' || key == 'w'){
			A = "^";
					}
				else if(key == 'S' || key == 's'){
			A = "o";
						}
	}
            
            
//filesystem_inprogress kaizer job
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



int main() {

    ios_base::sync_with_stdio(false);
    while (true) {
        drawField(screen, width, height);
        Sleep(50);
        if (_kbhit()) {
            char key = _getch();
            keyboard(key,A);
    					}
    }
    return 0;
}

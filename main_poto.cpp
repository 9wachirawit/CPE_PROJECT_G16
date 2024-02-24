#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
using namespace std;

//score save;
	vector<string> names;
    vector<int> scores;


//sceen saving
const int width = 100, height = 26;
int screen[height][width] = {};
string A = "o";
/*
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
}*/

//kaizer j
/*void monsterspawn(int (&x)[height][width], int width, int height){
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
    
        }
    }
}*/

//read_and_show_scene inprogress 
/*
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
}*/


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
            
//bomb 
int readscore(){
		ifstream dest;
	dest.open("score.txt"); 
	string text0;
	while (getline(dest,text0))
	{
		const char * text1 = text0.c_str();
		char format[] = "%[^:]: %d";
		char name[100];
		int score;
		sscanf(text1,format,name,&score);
			names.push_back(name);
			scores.push_back(score);
			//cout << name <<" "<<score<<endl;
	}
	dest.close();
}


int findscore_edit(string myname,int myscore){
    names.push_back(myname);
	scores.push_back(myscore);
	readscore();
	for (int i = 0; i < 10 - 1; ++i) {
        for (int j = 0; j < 10 - i - 1; ++j) {
            if (scores[j] < scores[j + 1]) {
                int temp = scores[j];
                string temps = names[j];
                
                names[j] = names[j + 1];
                names[j + 1] = temps;
                
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
    ofstream textEdit("score.txt");
    for (int i = 0; i < 10;i++){
    //	cout << names[i] << " " <<scores[i]<<endl;
    	textEdit << names[i]<<":"<<scores[i]<<"\n";
	}
	textEdit.close();
	names.clear();
	scores.clear();
}

//bomb 


int main() {

    ios_base::sync_with_stdio(false);
    while (true) {
        //drawField(screen, width, height);
        Sleep(50);
        if (_kbhit()) {
            char key = _getch();
            keyboard(key,A);
    					}
    }
    return 0;
}

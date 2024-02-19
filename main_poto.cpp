#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
using namespace std;

const int width = 100, height = 26;
int screen[height][width] = {0};


//buildscene_inprogress pedophathora job
void buildscene(int (&x)[height][width], int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            x[i][j] = (int)0;
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
    system("cls");
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
                if(screen[y][x] == 0){
                	cout << 0;
				}
        }
        cout << endl;
    }
}


//keyboard system inprogress 
int keyboard(char key,string & A){
	if (key == 'A' || key == 'a') {
                A = "<";
            }
        else if(key == 'D' || key == 'd'){
        	A = ">";
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
	buildscene(screen, width, height);
	ios_base::sync_with_stdio(false);
	int j = 0;
	while (j == 0) { 
       drawField(screen, width, height);
      
        Sleep(50); // Delay
    	/* if (_kbhit()) {
            char key = _getch();
            keyboard(key,a);
    					}*/
    
    return 0;
}
}

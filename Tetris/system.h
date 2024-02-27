#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

// score save;
vector<string> names;
vector<int> scores;

void buildscene(char (&x)[height][width], int width, int height, int posX, int posY, int currentBlock) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
        {
            if ((((i == 1) or (i == 22)) and (j >= 25)) and ((j != 37) and (j != 38) and (j != 51) and (j != 52) and (j <= 94)) or (((i >= 2) and (i <= 21)) and ((j == 25) or (j == 36) or (j == 39) or (j == 50) or (j == 53) or (j == 94))))
            {
                x[i][j] = '#';
            }
            else
            {
                x[i][j] = ' ';
            }
        }
    }
}

int drawField(char (&screen)[height][width], int width, int height)
{
    system("cls");
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
    printf("                         HP :");
}

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

void monsterspawn(char (&x)[height][width], int width, int height){
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
    
        }
    }
}

#endif

#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <ctime> 
using namespace std;


int Block = rand() % 7;	//(I = 0 ,N = 1,2 ,L = 3,4 ,W = 5 ,O = 6) rand() % 7
int rotate = 0; // 0 90 180 270 : 0 1 2 3
int posX = 41 + (rand() % 8);	// current x position 39 - 48 :: 40 - 47
int posY = 4;	// current y position
int Mmax;		// max move x
int Mmin;		// min move -x
int cd = 0;	    // block can drop? 0 1
int cr,cmr,cml;			// block can move right or left and rotate  0 1
int score,counter;
bool over; //game over 

// sceen ::
const int width = 100, height = 24;
char screen[height][width] = {};

void buildscene(char (&x)[24][100])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((((i == 1) and (j >= 53) or (i == 22)) and (j >= 39)) and ((j != 37) and (j != 38) and (j != 51) and (j != 52) and (j <= 94)) or (((i >= 2) and (i <= 21)) and ((j == 39) or (j == 50) or (j == 53) or (j == 94))))
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

void drawField(char (&screen)[24][100])
{
	system("cls");
	for (int y = 0; y < 24; ++y)
	{
		for (int x = 0; x < 100; ++x)
		{
		fflush(stdout);
		printf("%c",screen[y][x]);
		}
	printf("\n");
	}
 printf("%d %d", rotate, Block);
}

// tetris ::
void getscore(char (&x)[24][100]){
	for(int i = 21;i>=2;i--){
		if(x[i][40] == '@' && x[i][41] == '@' &&x[i][42] == '@' && x[i][43] == '@' && x[i][44] == '@' && x[i][45] == '@' && x[i][46] == '@' && x[i][47] == '@'&&x[i][48] == '@' && x[i][49] == '@'){
		x[i][40] = ' ' ;
		x[i][41] = ' ' ;
		x[i][42] = ' ' ;
		x[i][43] = ' ' ;
		x[i][44] = ' ' ;
		x[i][45] = ' ' ;
		x[i][46] = ' ' ;
		x[i][47] = ' ' ;
		x[i][48] = ' ' ;
		x[i][49] = ' ' ;
		score += 100;
		 for(int i = 21;i>=2;i--){
		////
		 }
		}
	}
}


void newBlock()
{ 
	if(cd == 0){
	 Block = rand() %7;	//(I = 0 ,N = 1,2 ,L = 3,4 ,W = 5 ,O = 6)rand() %7
	 rotate = rand() %4; // 0 90 180 270 : 0 1 2 3
	 posX = 45;	// current x position 39 - 48 :: 40 - 47
	 posY = 3;	// current y position
	 cd = 1;

	}
}

void drop(int &posY,int cd)
{
	if (cd == 1)
	{
		posY += 1;
	}
}

void rotation()
{
	if (rotate >= 0 && rotate < 3)
	{
		rotate += 1;
	}
	else
	{
		rotate = 0;
	}
}
void move(int x, char s[24][100], int Mmax, int Mmin)
{
	
	if (x == -1&& cml == 1)
	{
		posX -= 1;
	}
	else if (x == 1 && cmr == 1)
	{
		posX += 1;
	}
	
}

void Tetris(char (&x)[24][100], int posX, int posY, int currentBlock, int rotate)
{	
	for (int i = 0; i <= 21; i++)
	{
		for (int j = 0; j <= 10; j++)
		{
			if (x[i + 1][j + 40] == 'O')
			{
				x[i + 1][j + 40] = ' ';
			}
		}
	}

	switch (currentBlock)
	{
	case 0: // ::I
		switch (rotate)
		{
		case 0:
			x[posY][posX] =     'O';
			x[posY - 1][posX] = 'O';
			x[posY - 2][posX] = 'O';
			x[posY + 1][posX] = 'O';
			
			if (x[posY][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY - 1][posX + 1] == ' ' && x[posY - 2][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' ' && x[posY - 2][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
			x[posY - 1][posX] = '@';
			x[posY - 2][posX] = '@';
			x[posY + 1][posX] = '@';
			}
			
			break;
		case 1:

			x[posY][posX] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY][posX + 2] = 'O';
			x[posY][posX - 1] = 'O';
			
			if (x[posY][posX + 3] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX + 2] == ' ' && x[posY + 1][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
			x[posY][posX] = '@';
			x[posY][posX + 1] = '@';
			x[posY][posX + 2] = '@';
			x[posY][posX - 1] = '@';
			}
			break;
		case 2:

			x[posY][posX] = 'O';
			x[posY - 1][posX] = 'O';
			x[posY - 2][posX] = 'O';
			x[posY + 1][posX] = 'O';
			
			if (x[posY][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY - 1][posX + 1] == ' ' && x[posY - 2][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' ' && x[posY - 2][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
				x[posY - 1][posX] = '@';
				x[posY - 2][posX] = '@';
				x[posY + 1][posX] = '@';
			}
			break;
		case 3:

			x[posY][posX] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY][posX + 2] = 'O';
			x[posY][posX - 1] = 'O';
			
			if (x[posY][posX + 3] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX + 2] == ' ' && x[posY + 1][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
			x[posY][posX] = '@';
			x[posY][posX + 1] = '@';
			x[posY][posX + 2] = '@';
			x[posY][posX - 1] = '@';
			}
			break;
		}
		break;

	case 1:
		switch (rotate)
		{
		case 0:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY - 1][posX - 1] = 'O';
			
			if (x[posY - 1][posX + 1] == ' ' && x[posY][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY - 1][posX - 2] == ' ' && x[posY][posX - 1] == ' '){
				cml = 1;
			}else{ 	
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX - 1] == ' ' && x[posY])
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX] = '@';
				x[posY][posX + 1] = '@';
				x[posY - 1][posX - 1] = '@';
			}
			break;
		case 1:
			x[posY][posX] = 'O';
			x[posY - 1][posX + 1] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY + 1][posX] = 'O';
			
			if (x[posY + 1 ][posX + 1] == ' ' && x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' && x[posY - 1][posX] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
				x[posY - 1][posX + 1] = '@';
				x[posY][posX + 1] = '@';
				x[posY + 1][posX] = '@';
			}
			break;
		case 2:
			x[posY][posX] = 'O';
			x[posY][posX - 1] = 'O';
			x[posY + 1][posX] = 'O';
			x[posY + 1][posX + 1] = 'O';
		
			if (x[posY + 1][posX + 2] == ' ' && x[posY][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 2][posX + 1] == ' ' && x[posY + 1][posX - 1])
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
				x[posY][posX - 1] = '@';
				x[posY + 1][posX] = '@';
				x[posY + 1][posX + 1] = '@';
			}
			break;
		case 3:
			x[posY][posX] = 'O';
			x[posY - 1][posX] = 'O';
			x[posY][posX - 1] = 'O';
			x[posY + 1][posX - 1] = 'O';
			
			if (x[posY + 1 ][posX] == ' ' && x[posY][posX + 1] == ' ' && x[posY - 1][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 2] == ' ' && x[posY][posX - 2] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 2][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
				x[posY - 1][posX] = '@';
				x[posY][posX - 1] = '@';
				x[posY + 1][posX - 1] = '@';
			}
			break;
		}
		break;

	case 2:
		switch (rotate)
		{
		case 0:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY - 1][posX + 1] = 'O';
			x[posY][posX - 1] = 'O';

			if (x[posY - 1][posX + 2] == ' ' && x[posY][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY - 1][posX - 1] == ' ' && x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX] = '@';
				x[posY - 1][posX + 1] = '@';
				x[posY][posX - 1] = '@';
			}
			break;
		case 1:
			x[posY][posX] = 'O';
			x[posY - 1][posX] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY + 1][posX + 1] = 'O';
			
			if (x[posY + 1 ][posX + 2] == ' ' && x[posY][posX + 2] == ' ' && x[posY - 1][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 2][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
				x[posY - 1][posX] = '@';
				x[posY][posX + 1] = '@';
				x[posY + 1][posX + 1] = '@';
			}
			break;
		case 2:
			x[posY][posX] = 'O';
			x[posY + 1][posX] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY + 1][posX - 1] = 'O';
			
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 2] == ' ' && x[posY][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 2][posX - 1] == ' ' && x[posY + 1][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
				x[posY + 1][posX] = '@';
				x[posY][posX + 1] = '@';
				x[posY + 1][posX - 1] = '@';
			}
			break;
		case 3:
			x[posY][posX] = 'O';
			x[posY - 1][posX - 1] = 'O';
			x[posY][posX - 1] = 'O';
			x[posY + 1][posX] = 'O';
			
			if (x[posY + 1 ][posX + 1] == ' ' && x[posY][posX + 1] == ' ' && x[posY - 1][posX] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 2] == ' ' && x[posY - 1][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@';
				x[posY - 1][posX - 1] = '@';
				x[posY][posX - 1] = '@';
				x[posY + 1][posX] = '@';
			}
			break;
		}
		break;
	case 3: // L
		switch (rotate)
		{
		case 0:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX - 1] = 'O';
			x[posY][posX - 1] = 'O';
			x[posY][posX + 1] = 'O';
			
			if (x[posY][posX + 2] == ' ' && x[posY - 1][posX] == ' ' ){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 2] == ' ' && x[posY - 1][posX - 2] == ' ' ){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX - 1] = '@';
				x[posY][posX - 1] = '@';
				x[posY][posX + 1] = '@';
			}
			break;
		case 1:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX + 1] = 'O';
			x[posY - 1][posX] = 'O';
			x[posY + 1][posX] = 'O';
		
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' && x[posY - 1][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX + 1] = '@';
				x[posY - 1][posX] = '@';
				x[posY + 1][posX] = '@';
			}
			break;
		case 2:
			x[posY][posX] = 'O'; // center
			x[posY][posX - 1] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY + 1][posX + 1] = 'O';
			
			if (x[posY + 1][posX + 2] == ' ' && x[posY][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY][posX - 1] = '@';
				x[posY][posX + 1] = '@';
				x[posY + 1][posX + 1] = '@';
			}
			break;
		case 3:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY + 1][posX] = 'O';
			x[posY + 1][posX - 1] = 'O';
			
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' && x[posY - 1][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 2] == ' ' && x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 2][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX] = '@';
				x[posY + 1][posX] = '@';
				x[posY + 1][posX - 1] = '@';
			}
			break;
		}
		break;

	case 4: // L2
		switch (rotate)
		{
		case 0:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX + 1] = 'O';
			x[posY][posX - 1] = 'O';
			x[posY][posX + 1] = 'O';
			
			if (x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 2] == ' ' && x[posY - 1][posX] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX + 1] = '@';
				x[posY][posX - 1] = '@';
				x[posY][posX + 1] = '@';
			}
			break;
		case 1:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY + 1][posX] = 'O';
			x[posY - 1][posX - 1] = 'O';
			
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' && x[posY - 1][posX +1]){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' && x[posY - 1][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX] = '@';
				x[posY + 1][posX] = '@';
				x[posY - 1][posX - 1] = '@';
			}
			break;
		case 2:
			x[posY][posX] = 'O'; // center
			x[posY][posX - 1] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY + 1][posX - 1] = 'O';
			
			if (x[posY + 1][posX] == ' ' && x[posY][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 2] == ' ' && x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 2][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY][posX - 1] = '@';
				x[posY][posX + 1] = '@';
				x[posY + 1][posX - 1] = '@';
			}
			break;
		case 3:

			x[posY][posX] = 'O'; // center
			x[posY + 1][posX + 1] = 'O';
			x[posY - 1][posX] = 'O';
			x[posY + 1][posX] = 'O';
			
			if (x[posY + 1][posX + 2] == ' ' && x[posY][posX + 1] == ' ' && x[posY - 1][posX +1]){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 2][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY + 1][posX + 1] = '@';
				x[posY - 1][posX] = '@';
				x[posY + 1][posX] = '@';
			}
			break;
		}
		break;
	case 5: // W
		switch (rotate)
		{
		case 0:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY][posX - 1] = 'O';
			x[posY][posX + 1] = 'O';
			
			if (x[posY][posX + 2] == ' ' && x[posY - 1][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 2] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX] = '@';
				x[posY][posX - 1] = '@';
				x[posY][posX + 1] = '@';
			}
			break;
		case 1:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY + 1][posX] = 'O';
			
			if(x[posY + 1][posX + 1] == ' ' && x[posY][posX + 2] == ' ' && x[posY - 1][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if(x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX] = '@';
				x[posY][posX + 1] = '@';
				x[posY + 1][posX] = '@';
			}
			break;
		case 2:
			x[posY][posX] = 'O'; // center
			x[posY][posX + 1] = 'O';
			x[posY][posX - 1] = 'O';
			x[posY + 1][posX] = 'O';
			
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY][posX + 1] = '@';
				x[posY][posX - 1] = '@';
				x[posY + 1][posX] = '@';
			}
			break;
		case 3:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY + 1][posX] = 'O';
			x[posY][posX - 1] = 'O';
			
			if(x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' && x[posY - 1][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if(x[posY + 1][posX - 1] == ' ' && x[posY][posX - 2] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX - 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY - 1][posX] = '@';
				x[posY + 1][posX] = '@';
				x[posY][posX - 1] = '@';
			}
			break;
		}
		break;
	case 6: // O
		switch (rotate)
		{
		default:
			x[posY][posX] = 'O'; // center
			x[posY][posX + 1] = 'O';
			x[posY - 1][posX + 1] = 'O';
			x[posY - 1][posX] = 'O';
			
			if (x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ')
			{
				cd = 1;
			}
			else
			{
				cd = 0;
			}
			if (cd == 0)
			{
				x[posY][posX] = '@'; // center
				x[posY][posX + 1] = '@';
				x[posY - 1][posX + 1] = '@';
				x[posY - 1][posX] = '@';
			}
		}
		break;

		break;
	}
	}


int main()
{
	// game setup ::
	srand(time(0));
	buildscene(screen);
	bool R = 1;

	while (R)
	{   
		if(over != 1){
		newBlock();
		Tetris(screen, posX, posY, Block, rotate);	
		}
		drawField(screen);
		getscore(screen);
		drop(posY, cd);
		Sleep(300);
		if (_kbhit())
		{
			char key = _getch();
			if (key == 'W' || key == 'w')
			{
				rotation();
			}
			else if (key == 'A' || key == 'a')
			{
				move(-1, screen, Mmax, Mmin);
			}
			else if (key == 'D' || key == 'd')
			{
				move(1, screen, Mmax, Mmin);
			}
			else if (key == 'S' || key == 's')
			{
				Block -= 1;
			}
			
			if(Block <0) Block = 6;
		}
		
	}
}

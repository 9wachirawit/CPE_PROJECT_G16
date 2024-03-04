#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <ctime> 
#include <string>   
using namespace std;


int Block;				//(I = 0 ,N = 1,2 ,L = 3,4 ,W = 5 ,O = 6) rand() % 7.
int rotate = 0; 					// 0 90 180 270 : 0 1 2 3.
int posX = 41 + (rand() % 8);		// current x position 39 - 48 :: 40 - 47.
int posY = 4;						// current y position.
int cd = 0;	  				        // block can drop? 0 1.
int cr,cmr,cml;			            // block can move right / left and rotate?  0 1.
double scoredb = 0.00000; 			// score.
string scoretoshow;				    // score to show on array.
bool over = 0;                      // GAME OVER CHEACK.


// CREATE ARRAY SCREEN.
const int width = 100, height = 25; 
char screen[height][width] = {};


//setup array screen game build -BORDER -SCORE & HP PLAYER , ENEMY TEXT. *One time use.
void buildscene(char (&x)[25][100])
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
	
	x[3][27] = 'S';
	x[3][28] = 'C';
	x[3][29] = 'O';
	x[3][30] = 'R';
	x[3][31] = 'E';
	x[3][32] = ':';
	
	x[24][41] = 'H';x[24][42] = 'P'; // PLAYER.
	x[24][71] = 'H';x[24][72] = 'P'; // ENEMY.
	
}

//SHOW ARRAY AND CLEAR SCREEN.
void drawField(char (&screen)[25][100])
{
	system("cls");
	for (int y = 0; y < 25; ++y)
	{
		for (int x = 0; x < 100; ++x)
		{
		cout << (char)screen[y][x];
		}
	cout << endl;
	}
}

// TETRIS.
void overcheck(char (&x)[25][100]){
	if(x[2][40] == '@' || x[2][41] == '@' || x[2][42] == '@' || x[2][43] == '@' || x[2][44] == '@' || x[2][45] == '@' ||x[2][46] == '@' || x[2][47] == '@' || x[2][48] == '@' || x[2][49] == '@'  ){
		over = 1;
	}
}
// If the block is at the top of the top == OVER.

void scoreshow(char (&x)[25][100]){
 	string scoretoshow = to_string(scoredb);
	x[3][33] = scoretoshow[2]; 	x[3][34] = scoretoshow[3]; 	x[3][35] = scoretoshow[4]; 	x[3][36] = scoretoshow[5];x[3][37] = scoretoshow[6];
}

void getscore(char (&x)[25][100]){
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
		scoredb += 0.00250;
		 for(int j = i;j>=2;j--){
		x[j][40] = 	x[j-1][40];
		x[j][41] = 	x[j-1][41];
		x[j][42] = 	x[j-1][42];
		x[j][43] = 	x[j-1][43];
		x[j][44] =	x[j-1][44];
		x[j][45] = 	x[j-1][45];
		x[j][46] = 	x[j-1][46];
		x[j][47] = 	x[j-1][47];
		x[j][48] = 	x[j-1][48];
		x[j][49] = 	x[j-1][49];
		 }
		}
	}
}
// delete line and move. +score


void newBlock() 
{ 
	if(cd == 0){
	 Block = 3;	//(I = 0 ,N = 1,2 ,L = 3,4 ,W = 5 ,O = 6)rand() %7
	 rotate = 3; // 0 90 180 270 : 0 1 2 3
	 posX = 41 + rand()%7;	// current x position 39 - 48 :: 40 - 47
	 posY = 3;	// current y position
	 cd = 1;
	 scoredb += 0.00025;
	}
}
// RESET variable to start new block.

void drop(int &posY,int cd)
{
	if (cd == 1)
	{
		posY += 1;
	}
}
// DROP block.

void rotation()
{
	if (cr == 1){
	
	if (rotate >= 0 && rotate < 3)
	{
		rotate += 1;
	}
	else
	{
		rotate = 0;
	}
	
	}
}
// ROTATION block.
void move(int x, char s[25][100])
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
// MOVE block.

// MAIN::TATRIS LOGIC.  *7 block and 4 rotate case.
void Tetris(char (&x)[25][100], int posX, int posY, int currentBlock, int rotate)
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
			
			if (x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY - 1][posX + 1] == ' ' && x[posY - 2][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY - 1][posX - 1] == ' ' && x[posY - 2][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY][posX + 2] == ' ' && x[posY][posX + 1] == ' ' && x[posY][posX - 1] == ' '){ // can rotate
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY + 1][posX] == ' ' && x[posY - 1][posX] == ' ' && x[posY - 2][posX] == ' ' ){ // can rotate
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY][posX + 2] == ' ' && x[posY][posX + 1] == ' ' && x[posY][posX - 1] == ' ' ){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY + 1][posX] == ' ' && x[posY - 1][posX] == ' ' && x[posY - 2][posX] == ' '){ // can rotate
				cr = 1;
			}else{
				cr = 0;
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

	case 1: // mark
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
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' || x[posY][posX + 1] == 'O'  ){
				cr = 1;
			}else{
				cr = 0;
			}
			if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX - 1] == ' ')
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
			if (x[posY + 2][posX + 2] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
		
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX - 1] == ' ' && x[posY][posX] == ' ' || x[posY][posX] == 'O'  ){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY][posX - 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX] == ' ' || x[posY][posX] == 'O'   ){
				cr = 1;
			}else{
				cr = 0;
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

	case 2: // mark
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
			if (x[posY + 1][posX + 1] == ' ' &&  x[posY + 2 ][posX + 1] == ' ' && x[posY][posX] == ' ' || x[posY][posX] == 'O'  ){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY + 2][posX - 1] == ' ' &&  x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ' || x[posY][posX] == 'O'   ){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY][posX - 1] == ' ' &&  x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX] == ' ') {
				cr = 1;
			}else{
				cr = 0;
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
		case 3: // mark
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
			if (x[posY][posX + 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY][posX] == ' ' || x[posY][posX + 1] == 'O'){
				cr = 1;
			}else{
				cr = 0;
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
			
			if (x[posY + 1][posX + 2] == ' ' && x[posY][posX] == ' ' ){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 2] == ' ' && x[posY][posX - 2] == ' ' ){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' &&  x[posY - 1 ][posX + 1] == ' ' && x[posY - 1][posX] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
		
			if (x[posY + 2][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX + 1] == ' ' &&  x[posY][posX + 1] == ' ' && x[posY][posX - 1] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
			
			if (x[posY + 2][posX + 2] == ' ' && x[posY + 1][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' &&  x[posY + 1][posX - 1] == ' ' && x[posY - 1][posX] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
			
			if (x[posY + 2][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			//--*************************************************************//
			if (x[posY + 2][posX - 2] == ' ' && x[posY + 1][posX - 2] == ' ' ){
				cml = 1;
			}else{ 
				cml = 0;
			}
			
			if (x[posY][posX + 1] == ' ' &&  x[posY - 1 ][posX - 1] == ' ' && x[posY][posX - 1] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
			
			if (x[posY + 1][posX + 2] == ' ' && x[posY ][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 2] == ' ' && x[posY ][posX] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' &&  x[posY - 1 ][posX] == ' ' && x[posY - 1][posX - 1] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
			
			if (x[posY + 2][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY ][posX +1]){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX - 1] == ' ' && x[posY +1][posX - 1] == ' ' && x[posY ][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' &&  x[posY][posX + 1] == ' ' && x[posY][posX - 1] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
			
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX + 2] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX - 2] == ' ' && x[posY + 1][posX - 2] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX + 1] == ' ' &&  x[posY + 1][posX] == ' ' && x[posY - 1][posX] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
			
			if (x[posY + 2][posX + 2] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX +1]){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY][posX + 1] == ' ' &&  x[posY - 1 ][posX + 1] == ' ' && x[posY ][posX - 1] == ' '){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY + 1][posX] == ' ' &&  x[posY - 1 ][posX] == 'O' && x[posY][posX + 1] == 'O' ||  x[posY - 1 ][posX] == 'O' || x[posY][posX + 1] == 'O'){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY][posX - 1] == ' ' &&  x[posY][posX + 1] == 'O' && x[posY + 1][posX] == 'O'){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY - 1][posX] == ' ' &&  x[posY + 1][posX] == 'O' && x[posY][posX - 1] == 'O'){
				cr = 1;
			}else{
				cr = 0;
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
			if (x[posY][posX + 1] == ' ' &&  x[posY - 1 ][posX] == 'O' && x[posY][posX - 1] == 'O'){
				cr = 1;
			}else{
				cr = 0;
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
	
void startgame(){
	
}
	
void fighting(){
	//if(mons == 0){
		//create 
	//}
	
}


int main()
{
	// game setup ::
	srand(time(0));
	buildscene(screen);
	bool R = 1;
	while (R)
	{   
		drawField(screen);
		if(over != 1){
		ios_base::sync_with_stdio(false);
		newBlock();
		Tetris(screen, posX, posY, Block, rotate);	
		getscore(screen);
		drop(posY, cd);
		scoreshow(screen);
		overcheck(screen);
		}
		
		Sleep(250);
		if (_kbhit())
		{
			char key = _getch();
			if (key == 'W' || key == 'w')
			{
				rotation();
			}
			else if (key == 'A' || key == 'a')
			{
				move(-1, screen);
			}
			else if (key == 'D' || key == 'd')
			{
				move(1, screen);
			}
			else if (key == 'S' || key == 's')
			{
			
			}
			
		}
		
	}
}

//	if(Block <0) Block = 6; TEST COMMAND.

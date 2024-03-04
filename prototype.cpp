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

//Jao9's Code
 char key;
int Block;							//(I = 0 ,N = 1,2 ,L = 3,4 ,W = 5 ,O = 6) rand() % 7.
int rotate = 0; 					// 0 90 180 270 : 0 1 2 3.
int posX = 41 + (rand() % 8);		// current x position 39 - 48 :: 40 - 47.
int posY = 4;						// current y position.
int cd = 1;	  				        // block can drop? 0 1.
int cr,cmr,cml;			            // block can move right / left and rotate?  0 1.
double scoredb = 0.00000; 			// score.
int scoreint;
string scoretoshow;				    // score to show on array.
bool over = 0;                      // GAME OVER CHEACK.
bool START = 0;						// START TETRIS
const int h = 20;
const int w = 40;
string name;
double score;
vector<string> names;
vector<int> scores;
bool game = 1;



double hp_player;
string show_hp_player;

double hp_monster ;
string show_hp_monster;
int atktime;

int monnumber;


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
	x[24][41] = 'H';x[24][42] = 'P'; 
	x[24][71] = 'H';x[24][72] = 'P';
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
	if((x[2][40] == '@' || x[2][41] == '@' || x[2][42] == '@' || x[2][43] == '@' || x[2][44] == '@' || x[2][45] == '@' ||x[2][46] == '@' || x[2][47] == '@' || x[2][48] == '@' || x[2][49] == '@') || hp_player * 100 <= 0  ){
		scoreint = (int)(scoredb * 100000);
		over = 1;
	}
}
// If the block is at the top of the top == OVER.

void shown(char (&x)[25][100]){
 	string scoretoshow = to_string(scoredb);
	x[3][33] = scoretoshow[2]; 	x[3][34] = scoretoshow[3]; 	x[3][35] = scoretoshow[4]; 	x[3][36] = scoretoshow[5];x[3][37] = scoretoshow[6];
	
	string show_hp_player = to_string(hp_player);
	string show_hp_monster = to_string(hp_monster);
	
	x[24][44] = show_hp_player[2];x[24][45] = show_hp_player[3];
	x[24][74] = show_hp_monster[2]; x[24][75] = show_hp_monster[3];// ENEMY.
}

void attack(int x){
	hp_monster -= (0.05) * x;
}
void getscore(char (&x)[25][100]){
	int powerup = 0;
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
		powerup += 1;
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
	
	attack(powerup);
}
// delete line and move. +score
	
void newBlock() 
{ 
	if(cd == 0){
	 Block = rand() %7;	//(I = 0 ,N = 1,2 ,L = 3,4 ,W = 5 ,O = 6)rand() %7
	 rotate = rand() %4; // 0 90 180 270 : 0 1 2 3
	 posX = 41 + rand()%7;	// current x position 39 - 48 :: 40 - 47
	 posY = 3;	// current y position
	 cd = 1;
	 scoredb += 0.00025;
	 atktime++;
	}
}
// RESET variable to start new block.

void drop(int &posY,int cd)
{
	if(cd == 1){
		posY += 1;
	}
}
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
	case 0: // :: I :: /clear
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

	case 1: 
		switch (rotate)
		{
		case 0:
			x[posY][posX] = 'O'; // center
			x[posY - 1][posX] = 'O';
			x[posY][posX + 1] = 'O';
			x[posY - 1][posX - 1] = 'O';
			
			if ((x[posY+1][posX+2] == ' ' || x[posY][posX + 2 ] == ' ')  && x[posY-1][posX+1] == ' ' ){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 2] == ' '|| x[posY - 1][posX - 2] == ' '){
				cml = 1;
			}else{ 	
				cml = 0;
			}
			if (x[posY ][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' || x[posY][posX + 1] == 'O'  ){
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
			
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 2] == ' ' &&  x[posY - 1][posX + 2] == ' ' && x[posY + 2][posX +1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY - 1][posX] == ' ' && ( x[posY][posX - 1] == ' ' || x[posY + 2][posX - 1] == ' ' )){
				cml = 1;
			}else{ 
				cml = 0;
			}
				if (x[posY + 2][posX + 1] == ' ' && x[posY + 2][posX] == ' ' && x[posY + 1][posX - 1]){  ///sdsasdad
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
		
			if ( (x[posY + 2][posX + 2] == ' ' || x[posY +1][posX + 2] == ' ' ) && x[posY + 2][posX + 1] == ' ' && x[posY + 2][posX] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 2][posX - 1] == ' ' && ( x[posY + 1][posX - 2] == ' ' || x[posY][posX - 2] == ' ') && x[posY + 1 ][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
				if (x[posY + 2][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' '){
					cr = 1;
				}else{
					cr = 0;
				}
			if (x[posY + 2][posX] == ' ' && x[posY + 2][posX + 1] == ' ' && x[posY + 1][posX - 1] == ' ')
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
			
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' && x[posY +1][posX] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if ((x[posY + 2][posX - 2] == ' ' || x[posY][posX - 2] == ' ') && x[posY + 1][posX - 2] == ' ' && x[posY - 1][posX - 1] == ' ' ){
				cml = 1;
			}else{ 
				cml = 0;
			}
				if (x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' '){
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

			if ((x[posY - 1][posX + 2] == ' ' || x[posY][posX + 2] == ' ') && x[posY][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY - 1][posX -1] == ' ' && (x[posY + 1][posX - 2] == ' ' || x[posY][posX - 2] == ' ')){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX + 1] == ' ' &&  x[posY + 1 ][posX + 1] == ' ' && x[posY + 1][posX] == ' '){
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
			
			if ((x[posY + 2 ][posX + 2] == ' '|| x[posY][posX + 2] == ' ') && x[posY + 1][posX + 2] == ' ' && x[posY - 1][posX + 1] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY - 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' && x[posY + 1][posX] == ' ' && x[posY + 2][posX] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY + 1][posX] == ' '){
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
			
			if ((x[posY][posX + 2] == ' ' || x[posY + 1][posX + 2] == ' ') && x[posY + 1][posX + 1] == ' ' && x[posY + 2][posX + 1] == ' ' && x[posY + 2][posX] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY][posX - 1] == ' ' && x[posY + 2][posX - 1] == ' ' && (x[posY + 1][posX - 2] == ' ' || x[posY + 2][posX - 2] == ' ')){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY][posX - 1] == ' ' &&  x[posY + 2][posX] == ' ' ) {
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
			
			if ((x[posY + 2 ][posX + 1] == ' '|| x[posY][posX + 1] == ' ') && x[posY + 1][posX + 1] == ' ' && x[posY - 1][posX] == ' '){
				cmr = 1;
			}else{ 
				cmr = 0;
			}
			if (x[posY - 1][posX - 2] == ' ' && x[posY][posX - 2] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX - 1] == ' '){
				cml = 1;
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX - 1] == ' ' && x[posY][posX + 1] == ' ' ){
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
			
			if ((x[posY + 1][posX + 2] == ' ' || x[posY][posX + 2] == ' ') && x[posY + 1][posX + 1] == ' '  && x[posY +1][posX] == ' ' && x[posY - 1][posX] == ' '){
				if(x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if ((x[posY + 1][posX - 2] == ' ' || x[posY - 1][posX - 2] == ' ') && x[posY][posX - 2] == ' ' && x[posY + 1][posX-1] == ' ' && x[posY + 1][posX ] == ' '){
				if(x[posY][posX - 2] == ' ' && x[posY - 1][posX - 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' &&  x[posY + 2][posX] == ' ' ){
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
		
			if (x[posY + 2][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' && (x[posY][posX + 2] == ' ' || x[posY - 1][posX + 2] == ' ')){
				if(x[posY - 1][posX + 2] == ' ' && x[posY - 2][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if ((x[posY + 2][posX - 1] == ' ' || x[posY - 1][posX - 1] == ' ' )&& x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' '){
				if(x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX + 1] == ' ' &&  x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX - 1] == ' '){
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
			
			if ((x[posY + 2][posX + 2] == ' ' || x[posY][posX + 2] == ' ') && x[posY + 1][posX + 2] == ' ' && x[posY + 1][posX] == ' ' ){
				if(x[posY + 1][posX + 2] == ' ' && x[posY][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX] == ' ' && x[posY + 1][posX - 1] == ' ' && (x[posY + 1][posX - 2] == ' ' || x[posY][posX - 2] == ' ')){
				if(x[posY][posX - 2] == ' ' && x[posY - 1][posX - 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' &&  x[posY + 2][posX - 1] == ' ' && x[posY + 1][posX] == ' '){
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
			
			if ((x[posY + 2][posX + 1] == ' ' || x[posY - 1][posX + 1] == ' ') && x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' '){
				if(x[posY][posX + 1] == ' ' && x[posY - 1][posX + 1] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			//--*************************************************************//
			if (x[posY + 2][posX - 1] == ' ' && (x[posY + 2][posX - 2] == ' ' || x[posY + 1][posX - 2] == ' ') && (x[posY][posX - 1] == ' ' || x[posY - 1][posX - 1] == ' ')){
				if(x[posY + 1][posX - 2] == ' ' && x[posY][posX - 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			
			if (x[posY + 2 ][posX + 1] == ' ' &&  x[posY + 2 ][posX - 1] == ' ' && x[posY + 2][posX] == ' '){
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
			
			if (x[posY][posX + 2] == ' ' && (x[posY + 1][posX + 2] == ' ' || x[posY - 1 ][posX + 2] == ' ') && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX] == ' '){
				if(x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2 ] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if ((x[posY + 1][posX - 2] == ' ' || x[posY][posX - 2] == ' ') && x[posY + 1][posX - 1] == ' ' && x[posY + 1][posX] == ' ' || x[posY - 1][posX] == ' ' ){
				if(x[posY][posX - 2] == ' ' && x[posY - 1][posX - 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX] == ' ' &&  x[posY + 2 ][posX] == ' ' && x[posY + 2][posX + 1] == ' '){
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
			
			if (x[posY + 2][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY][posX +1]){
				if(x[posY + 1][posX + 2] == ' ' && x[posY][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' && ( x[posY][posX - 2] == ' ' || x[posY - 1][posX - 2] == ' ' )){
				if(x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX - 1] == ' ' &&  x[posY + 1][posX - 1] == ' '){
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
			
			if (x[posY + 2][posX] == ' ' && (x[posY + 1][posX + 2] == ' ' || x[posY][posX + 2] == ' ' ) && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX] == ' '){
				if(x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if ((x[posY + 2][posX - 2] == ' ' || x[posY][posX - 2] == ' ') && x[posY + 1][posX - 2] == ' ' && x[posY + 1][posX] == ' '){
				if(x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' &&  x[posY + 1][posX] == ' ' ){
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

			if ((x[posY - 1][posX + 1] == ' ' || x[posY - 1][posX + 1] == ' ') && x[posY + 2][posX + 1] == ' ' && (x[posY + 2][posX + 2] == ' ' || x[posY + 1][posX + 2])){
				if(x[posY][posX + 1 ] == ' ' && x[posY - 1][posX + 1] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 2][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1]){
				if(x[posY - 1][posX - 2] == ' ' && x[posY - 2][posX - 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY][posX + 1] == ' ' &&  x[posY + 1 ][posX + 1] == ' ' && x[posY + 1 ][posX - 1] == ' '){
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
			
			if (x[posY + 1][posX + 2] == ' ' && x[posY - 1][posX + 1] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX] == ' '){
				if(x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if ( x[posY + 1][posX - 2] == ' ' && x[posY - 1][posX - 1] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY + 1][posX] == ' ' ){
				if(x[posY][posX - 2] == ' ' && x[posY - 1][posX - 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX] == ' ' && x[posY + 1][posX + 1] == ' '){
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
			
			if(x[posY - 1][posX + 1] == ' ' && x[posY + 1][posX + 2] == ' '  && x[posY + 1][posX + 1] == ' ' && x[posY + 2][posX + 1] == ' '){
				if(x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if(x[posY + 1][posX - 1] == ' ' && x[posY][posX - 1] == ' ' &&  x[posY + 2][posX - 1] == ' '){
				if(x[posY][posX - 1] == ' ' && x[posY - 1][posX - 1] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX - 1] == ' '){
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
			
			if (x[posY + 1][posX + 2] == ' ' && x[posY + 1][posX + 1] == ' ' && x[posY + 2][posX + 1] == ' '){
				if(x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if ( x[posY + 1][posX - 2] == ' ' && x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX - 1] == ' '){
				if(x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 2][posX] == ' ' && x[posY + 1][posX - 1] == ' '){
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
			
			if (x[posY + 1][posX + 1] == ' ' && x[posY][posX + 1] == ' ' &&  x[posY + 2][posX + 1] == ' '){
				if(x[posY][posX + 1] == ' ' && x[posY - 1][posX + 1] == '@'){
					cmr = 0;
				}else{
					cmr = 1;
				}
			}else{ 
				cmr = 0;
			}
			if (x[posY - 1][posX - 1] == ' ' && x[posY + 1][posX - 2] == ' '  && x[posY + 1][posX - 1] == ' ' && x[posY + 2][posX - 1] == ' '){
				if(x[posY][posX - 2] == ' ' && x[posY - 1][posX - 2] == '@'){
					cml = 0;
				}else{
					cml = 1;
				}
			}else{ 
				cml = 0;
			}
			if (x[posY + 1][posX + 1] == ' ' && x[posY + 1][posX - 1] == ' '){
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
			
			
			if (x[posY][posX + 2] == ' ' && x[posY - 1][posX + 2] == ' ' ){
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
	
//	if(Block <0) Block = 6; TEST COMMAND.
void readscore(){
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

void show_score(){
	readscore();
	for(int i=0;i<10;i++){
		cout << names[i] << " " << scores[i] << endl;
	}
}
void findscore_edit(string myname,int myscore){
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
        //cout << names[i] << " " <<scores[i]<<endl;
    	textEdit << names[i]<<":"<<scores[i]<<"\n";
	}
	textEdit.close();
	names.clear();
	scores.clear();
}
//Asset Code
void title() {
    const int sizeY = 20; 
    const int sizeX = 101;
		
	
	char title[sizeY][sizeX] = {
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},	
  	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','8','o'},
  	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','_','_','_','_','_',' ',' ',' ',' ','_','_','_',' ',' ','_','_','_',' ',' ','_','_','_','_','_','_',' ',' ','_','_','_',' ',' ',' ','_','_','_','_',' ','_','_','_','_','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','|',' ',' ','/',' ',' ','_',']','|',' ',' ',' ','\\','|',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ','\\',' ','|',' ',' ',' ',' ','/',' ','_','_','_','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','|',' ','/',' ',' ','[','_',' ','|',' ','D',' ',' ', ')',' ',' ',' ',' ',' ',' ','|','|',' ','D',' ',' ', ')',' ','|',' ',' ','(',' ',' ',' ','\\','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','_','|',' ',' ','|','_','|','|',' ',' ',' ',' ','_',']','|',' ',' ',' ','/' ,'|','_','|',' ',' ','|','_','|','|',' ',' ',' ','/',' ', ' ','|',' ',' ','|','\\','_',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ','|',' ',' ',' ','[','_',' ','|',' ',' ',' ','\\',' ',' ','|',' ',' ','|',' ',' ','|',' ',' ',' ','\\',' ',' ','|',' ',' ','|','/',' ','\\',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ','|','|',' ',' ','.',' ','\\',' ','|',' ',' ','|',' ',' ','|',' ',' ','.',' ','\\',' ','|',' ',' ','|','\\',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','_','_','|',' ',' ','|','_','_','_','_','_','|','|','_','_','|','\\','_','|','|','_','_','|',' ',' ','|','_','_','|','\\','_','|','_','_','_','_','|','\\','_','_','_','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','_','_','_','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','\\',' ','.','-','-','.','-','-','.','.','-','-','-','-','-','.','.','-','-','-','-','-','.','.','-','-','-','-','-','.','.','-','-','-','-','-','.','.','-','-','-','-','-','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','-','-',' ',' ','|', '|',' ',' ','|',' ',' ','|','|',' ',' ',' ',' ',' ','|','|',' ',' ','_',' ',' ','|','|',' ',' ','-','_','_','|','|',' ',' ','_',' ',' ','|','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','_','_','_','_','_','/',' ', '|','_','_','_','_','_','|','|','_','_','|','_','_','|','|','_','_','_',' ',' ','|','|','_','_','_','_','_','|','|','_','_','_','_','_','|','|','_','_','|','_','_','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' ,'|','_','_','_','_','_','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B','y',' ','P','u','e','n','M','a','i','K','(','r',')','o','b',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' ,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','8','o'}
                                                                 
};

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
                cout << title[y][x];
            }
        cout <<"\n";
        }
    cout <<"\n";
}

// menu() contains the on-screen display for the main menu options
void menu(){
    const int sizeY = 5; 
    const int sizeX = 101;

    char menu[sizeY][sizeX] = {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','=','8','o',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','=','=','8','o',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','8','o',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ','P','L','A','Y',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','L','E','A','D','E','R','B','O','A','R','D',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','E','X','I','T',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','[','p','r','e','s','s','"','A','"',']',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','[','p','r','e','s','s',' ','"','B','"',']',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','[','p','r','e','s','s','"','E','"',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','=','8','o',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','=','=','8','o',' ',' ',' ',' ',' ',' ',' ','o','8','=','=','=','=','=','=','=','=','=','=','=','8','o',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
                cout << menu[y][x];
            }
        cout <<"\n";
        }
    cout <<"\n";
}
void gameover(){
    string name;
    const int sizeY = 27; 
    const int sizeX = 90;

    char gameover[sizeY][sizeX] = {
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ','_','_','_','_','_',' ','_','_','_','_','_',' ','_','_','_','_','_',' ','_','_','_','_','_',' ','_','_','_','_','_',' ', '_','_','_','_','_',' ','_','_','_','_','_',' ','_','_','_','_','_',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','[',' ',' ','|',' ',' ',' ','_','_','|',' ',' ','_',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ','_','_','|',' ',' ',' ',' ',' ','|', ' ',' ','|',' ',' ','|',' ',' ',' ','_','_','|',' ','_','_',' ',' ','|',' ',' ',']',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ','|',' ','|',' ','|',' ','|',' ',' ',' ','_','_','|',' ',' ','|',' ',' ','|', ' ',' ','|',' ',' ','|',' ',' ',' ','_','_','|',' ',' ',' ',' ','-','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|','_','_','_','_','_','|','_','_','|','_','_','|','_','|','_','|','_','|','_','_','_','_','_','|','_','_','_','_','_','|','\\','_','_','_','/','|','_','_','_','_','_','|','_','_','|','_','_','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',':',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',':',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','(','(','T','E','L','L',' ','M','E',' ','Y','O','U','R',' ','N','A','M','E',')',')',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','_','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ','\\','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/','\\',' ','|',' ','.',' ','.',' ','\\','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/','/','/','/','\\','|',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/','/','/','/',' ',' ','\\','\\',' ','_','_','_','/','/','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/','/','/',' ',' ',' ',' ',' ','\\','\\',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/','/','/',' ',' ',' ',' ',' ',' ','|','\\','\\',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/','/',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','\\','\\',' ',' ','\\',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','\\','\\',' ',' ','\\',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','\\','\\',' ','/',' ',' ',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ','\\','/',' ',' ',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','\\','\\','/','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',':',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','\\','\\','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',':',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','\\','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','[',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.','.','.','.','|','_','_','_','_','_','_','_','_','_','\\','.','.','.','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',']',' ',' ',' ',' ',' ',' ',' ',' ',' '},        
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\\','.','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','.','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},           
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}        

    };
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
                cout << gameover[y][x];
            }
        cout <<"\n";
        }
    cout << "                              Input your name : ";
    getline(cin,name);
    findscore_edit(name,scoreint);
    show_score();
}

char mons[3][20][40] = {{
                
							{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\\',' ',' ','/','\\',' ',' ','/','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','\\','/',' ',' ','\\','/',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','=','=','=','=','=','=','=','=','=','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','=','-','-','-','-','-','-','-','-','-','-','=','=','_','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','=','_',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ',' ',' ','_','_','_','_','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',')',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','(',' ',' ',' ',' ',' ','/',' ',' ',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ',' ','<',' ',' ','(','@',')',' ',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',')',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ','(',' ',' ',' ',' ',' ',' ','\\','_','_','_','_','_','/',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ','(',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ','(',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',')',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ','(',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',')',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','L','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','=',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
                             } , {
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','_','-','-','-','-','-','-','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','(',' ',' ','@',' ',' ',' ','@',' ',' ',' ',' ',' ',')',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ',' ','A',' ',' ',' ',' ',' ',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\\','_','_',' ',' ',' ',' ',' ',' ','_','_','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ','=','^','_',' ',' ',' ',' ',' ','L','_','L','_','L','|','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ','^','/','/','/','\\','\\',' ',' ',' ',' ','/',' ',' ',' ',' ',' ','/','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ','/','/','/','/',' ',' ','\\','\\',' ',' ','/','_',' ','_',' ','_','/',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ','/','/','/','/',' ',' ','<','_','/',' ',' ','|','I','|','I','|','I','|','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ','\\','\\','\\','_','>',' ',' ',' ',' ',' ',' ','\\','_','_','_','_','_','/',' ',' ','_','^','-','^','-','=','^','=','_',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ','\\','_','_','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','/','/','/','/',' ','/','/',' ','\\','\\',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','<','<','_','<','_','_','/','<','>','/',' ',' ',' ','\\','<','>',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                             }, {
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ','_','=','-','-','-','-','-','=','_',' ',' ',' ',' ','_','_','_',' ',' ',' ',' ',' ','|','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ','/',' ',' ','~','-','=','_',' ',' ',' ','=','_','=','J',' ',' ',' ','=','_',' ',' ',' ',')',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ','/',' ',' ',' ',' ',' ',' ',' ','\\',' ',' ',' ','_','_',' ',' ',' ',' ',' ',' ','-','_','/',' ',' ',')',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ','/','~',' ',' ',' ',' ','_','-','-','_','\\','-','=',' ',' ','-',' ',' ',' ',' ',' ',' ',' ',')',' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ','/',' ',' ','=',' ',' ','/',' ','V','V',' ','1','\\',' ',' ','_','=','-','\\',' ',' ',' ',' ',' ','<','(',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ','(',' ',' ',' ',' ','-','/','y',' ',' ',' ',' ','Z','\\','\\','/',' ',' ',' ',' ','<','(','-','=','_',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ','\\',' ',' ',' ','/','y',' ','V','V',' ',' ',' ','Z','\\','\\',' ',' ',' ','/',' ',' ','\\',' ','\\',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ','|',' ',' ','/','y',' ','y',' ',' ','Z',' ',' ',' ','Z','\\',')',' ',' ',')',' ',' ',' ','\\',' ','\\',' ',' ',' ','\\',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ','(',' ','(','>',' ','>',' ',' ',' ',' ','<',' ',' ',' ','<',')',' ','(',' ',' ',' ',' ','/','|',' ','|',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ','\\',' ','\\','7',' ','7',' ',' ','4',' ',' ',' ','4','/',' ',' ',')',' ',' ',' ',' ','\\','A','/',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ','L',' ','\\','7',' ','A','A',' ',' ',' ','4','/','A',' ','/',' ',' ',' ',' ','/','/',' ','\\',' ',' ',' ',' ','|',' ','A',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ','\\',' ','\\','7',' ',' ',' ',' ','A','/','/',' ','\\',' ',' ','A',' ',' ','|',' ',' ',' ','\\',' ',' ','A','|','/',' ','\\',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ','\\',' ','L',' ',' ',' ',' ','J',' ','A',' ',' ','\\','/',' ','\\','/',' ',' ',' ',' ',' ','\\','/',' ','\\','/',' ',' ','\\',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ','\\','_','\\','A','A','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                          {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
                             }} ;

void monsterspawn(char (&x)[25][100],int y){
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 40; j++) {
            x[2+i][54+j] = mons[y][i][j];
        }
    }
}

void startgame(){
	if(START == 1){
		hp_monster = 0.1 * (rand()%10 + 1);
		hp_player = 0.20 ;
		monnumber = rand()%3;
		scoredb = 0.00000;
		atktime = 0;
		Block = rand() % 7;   	//(I = 0 ,N = 1,2 ,L = 3,4 ,W = 5 ,O = 6)
	    rotate = rand() % 4;     // 0 90 180 270 : 0 1 2 3
	    posX = 41 + rand()%7;	// current x position 39 - 48 :: 40 - 47
	    posY = 3;	            // current y position
	    cd = 1;
		monsterspawn(screen,monnumber);
	    START = 0;
	}	
}

void EVENT_monster(){
	if(hp_monster*100 == 0){
		hp_monster = 0.1 * (rand()%10 + 1);
		hp_player += 0.05;
		monnumber = rand()%3;
		monsterspawn(screen,monnumber);
		atktime = 0;
	}else{
		if(atktime == 3){
			atktime = 0;
			hp_player -= rand()%5 * 0.01;
		}
	}
}




//Tul's Code
// Get key from keyboard
int title_screen();
int playground();
int leaderboard();

char getcommand() {
    return toupper(getch());
}

void close() {
    Sleep(250);
}

int l_board()
{
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
    }



		cout << "             o--o0o--o             " << endl;
		cout << " 8=8========LEADERBOARD========8=8 " << endl;
		cout << "  |  NAME                SCORE  |  " << endl;
		cout << "  |                             |  " << endl;

		for (int i = 0; i < 10; i++)
		{
			int temp = scores[i], tempPos=0;
				while (temp != 0)
				{
					temp = temp / 10;
					tempPos++;
				}
		

			int positionOne = 24 - ((names[i].size())+tempPos);

			cout << "  |  " << names[i];
			for (int k = 0; k <= positionOne; k++)
			{
				cout << " ";
			}
			cout << scores[i];
			cout << "  |" << endl;
		}
		
		cout << "  |                             |  " << endl;
		cout << " 8=8===========================8=8 " << endl;
		cout << "             o--o0o--o             " << endl;
		cout << endl;

    dest.close();

	return 0;
}


int title_screen() {
    while (true) {
        system("cls");
        title();
        menu();
         key = getcommand();
        switch (key) {
            case 'E':
                return 0;
            case 'A':
            	over = 0;
            	game = 1;
            	START = 1;
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
        cout << "( Return to menu: E )";
        char key = getcommand();
        if(key == 'E') break;
    }
}

	

int gameover_screen(){
	
        system("cls");
        gameover();
        game = 0;
        
	
}


int playground() {
    
	buildscene(screen);
	//ios_base::sync_with_stdio(false);
	while (game)
	{   
		startgame();
		drawField(screen);
		if(over != 1){
		EVENT_monster();
		newBlock();
		Tetris(screen, posX, posY, Block, rotate);	
		getscore(screen);
		drop(posY, cd);
		shown(screen);
		overcheck(screen);
		
		Sleep(50);
		if (_kbhit())
		{
			char M = _getch();
			if (M == 'W' || M == 'w')
			{
				rotation();
			}
			else if (M == 'A' || M == 'a')
			{
				move(-1, screen);
			}
			else if (M == 'D' || M == 'd')
			{
				move(1, screen);
			}
			else if (M == 'S' || M == 's')
			{
			
			}
			
		}
	}else{
		system("cls");
		gameover_screen();
	}
	 
	}
		
}

    


int main() {
    srand(time(0));
    title_screen();
    return 0;
}

  

#ifndef HEADER_H
#define HEADER_H

const int width = 100, height = 26;
char screen[height][width] = {};
int currentBlock = 1; //current type of tetris block (0 = Iblock, 1 = 90Iblock, 2 = Sblock)
int startX;
int startY;
int posX = 39; //current x position
int posY = 2; //current y position
int borderL = 40; //left border of tetris game
int borderR = 47; //right border of tetris game
int borderT = 1; //top border of tetris game
int borderB = 18; //bottom border of tetris game
int blockHeight, blockWidth;

//void randomBlock
	
void buildTetris(char (&x)[height][width], int width, int height, int posX, int posY, int currentBlock) {
    switch (currentBlock) {
    case 0:
    	blockHeight = 4;
    	blockWidth = 1;
    	x[posY][posX+1] = 'I';
    	x[posY+1][posX+1] = 'I';
    	x[posY+2][posX+1] = 'I';
    	x[posY+3][posX+1] = 'I';
    	break;
    
	case 1:
		blockHeight = 1;
    	blockWidth = 4;
    	x[posY+1][posX+1] = 'I';
    	x[posY+1][posX+2] = 'I';
    	x[posY+1][posX+3] = 'I';
    	x[posY+1][posX+4] = 'I';
    	break;
		
    case 2:
    	blockHeight = 3;
    	blockWidth = 2;
    	x[posY+1][posX+2] = 'S';
    	x[posY+2][posX+1] = 'S';
    	x[posY+2][posX+2] = 'S';
    	x[posY+3][posX+1] = 'S';
    	break;
	}
}

void blockDrop() {
	switch (currentBlock) {
		case 0:
		if (posY < borderB) {
   			posY++;
		}
		break;
		
		case 1:
		if (posY < borderB+2) {
   			posY++;
		}
		break;
		
		case 2:
		if (posY < borderB) {
   			posY++;
		}
		break;
	}
}

void Move(int direction) {
	if (direction == -1) {
		switch (currentBlock) {
			case 0:
			if (posX >= borderL) {
				posX += direction;
			}
			break;
			case 1:
			if (posX >= borderL) {
				posX += direction;
			}
			break;
		}	
	} else if (direction == 1) {
		switch (currentBlock) {
			case 0:
			if (posX <= borderR) {
				posX += direction;
			}
			break;
			case 1:
			if (posX <= borderR-3) {
				posX += direction;
			}
			break;
		}
	}	
}

bool checkCollision(char (&screen)[height][width], int posX, int posY, int blockWidth, int blockHeight) {
    // Check collision with borders
    if (posX < borderL || posX + blockWidth > borderR || posY < borderT || posY + blockHeight > borderB) {
        return true; // Collision with game borders
    }

    // Check collision with existing blocks on the screen
    for (int i = 0; i < blockHeight; ++i) {
        for (int j = 0; j < blockWidth; ++j) {
            if (screen[posY + i][posX + j] != ' ') {
                return true; // Collision with existing block
            }
        }
    }

    return false; // No collision detected
}

void rotateBlock() {
    switch (currentBlock) {
        case 0:
        currentBlock = 1;
        break;
        
        case 1:
        if (posY <= borderB-2) {
        	currentBlock = 0;
    	}
        break;
    }
}

#endif

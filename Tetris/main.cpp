#include "tetris.h"
#include "system.h"

int main() {
    fflush(stdout);
    while (true) {
    	buildscene(screen, width, height, posX, posY, currentBlock); //FROM SYSTEM.H
    	buildTetris(screen, width, height, posX, posY, currentBlock); //FROM TETRIS.H
        drawField(screen, width, height); //FROM SYSTEM.H
        
        Sleep(50);
        blockDrop();
        
        if (_kbhit()) {
            char key = _getch();
            if (key == 'A' || key == 'a') {
            	Move(-1);
            } else if(key == 'D' || key == 'd') {
            	Move(1);
			} else if(key == 'R' || key == 'r') {
					rotateBlock();
				}
			}
		}
    }

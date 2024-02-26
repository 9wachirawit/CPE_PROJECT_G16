#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
using namespace std; 

// make it int function to return get() to 0;
int menu();
int playground();
int score();

//toupper(key) change key form lower to upper

/*Get "key" that is char-type fromkeyboard*/
void getcommand(char &skey){
    cout << "\n\ninput command : ";
    const char key = getch();
    skey = key;
}


int main(){
    srand(time(0));
    
    menu();

 return 0;
}

// s press
int score(){

    do{
    system("cls");
    char key;
    cout << "//show all score " << " Wow " << " nice score!";
    cout << "\nplease input command : ";
    cout << "\nReturn to menu: E" << "     " << "Play : A";
    getcommand(key);
    key = toupper(key);
    // r press to return menu
    if(key == 'E'){ return menu();}
    else if(key == 'A') { return playground();}
    else{
            cout << "Invalid command.\n";
            /*delay cout for 1.5 second*/
            Sleep(1500);
            cout << "\nPress anykey to continue.";

            if(cin.get())
            /*Clear console*/
            system("cls");
        }
    }while(true);
}

// p press 
int playground(){

    do{
    system("cls");
    char key;
    cout << "nice bro " << " wanna see the score?";
    cout << "\nplease input command : ";
    cout << "\nReturn to menu: E" << "     " << "Score : B";
    getcommand(key);
    key = toupper(key);
    // r press to return to menu
    if(key == 'E'){ return menu();}
    else if(key == 'B') { return score();}
    else{
            cout << "Invalid command.\n";
            /*delay cout for 1.5 second*/
            Sleep(1500);
            cout << "\nPress anykey to continue.";

            if(cin.get())
            /*Clear console*/
            system("cls");
        }
    }while(true);
}

// menu interactive
int menu(){
    // bornot check if there are exit to be break or not
    bool bornot = true;

    do{
    system("cls");
    char key;
    cout << "Please input command\n";
    cout << "Play : A" << " " << "Scores : B" << " " << "Exit : E";
    getcommand(key);
    key = toupper(key);
    if(key == 'E') { bornot = false; }
    else if(key == 'A'){ return playground();}
    else if(key == 'B'){ return score();}
    else{
            cout << "Invalid command.\n";
            /*delay cout for 1.5 second*/
            Sleep(1500);
            cout << "\nPress anykey to continue.";

            if(cin.get())
            /*Clear console*/
            system("cls");
        }    
    }while(bornot);
    system("cls");
return 0;
}

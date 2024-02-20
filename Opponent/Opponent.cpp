#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
using namespace std;


int main(){
    srand(time(0));

    string op[3] = {{R"(       |\/\/|        
       ======        
     _=-----=_     
    /  ___    \.  
   (  (_@_)    )   
  (            )   
   L__________= )"},{R"(      _------_
     =        =
    /          \
   ( @   @    ) |
   /   A     /_/
   \_      _/
     L_L_L| _
    /_ _ _ / >
    |I|I|I|_/ )"},{R"(     ___-----_
    /___    _ |  
   T V T  (   |
   |   | |   |   A
   [_A_]=   /   //
        /  /   ||
       |  |    \ \
      A(_A_(A  A|A|A
    )"}};      

    const int height = 22;
    const int width = 22;
    int ranop = rand()%3;
    for(int ds = 0 ; ds < height ; ds++){
        for(int dl = 0 ; dl < width ; dl++){
            if(ds == 0 || ds == height-1) cout << "-" ;
            else if((ds > 0 && ds < height-1)&& (dl == 0 || dl == width-1)) cout << "|" ;
               if(ranop == 0){ 
                 
               }else if(ranop == 1){

               }else if(ranop == 2){

               }
            else cout << " ";
            if(dl == width-1) cout << "\n";
        }
    }

    cout << ranop << "\n" << op[ranop];

    if(cin.get())return 0;
}
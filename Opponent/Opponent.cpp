#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
using namespace std;
    const int height = 22;
    const int width = 22;

    int main()
    {
      char mon1[4][5] = {{
                             '1',
                             '\t',
                             ' ',
                             ' ',
                             ' ',
                         },
                         {
                             ' ',
                             '1',
                             ' ',
                             ' ',
                             ' ',
                         },
                         {
                             ' ',
                             ' ',
                             '1',
                             ' ',
                             ' ',
                         },
                         {
                             ' ',
                             ' ',
                             ' ',
                             '1',
                             ' ',
                         }};
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 5; j++)
        {
          cout << mon1[i][j];
        }
        cout << "\n";
      }
    }
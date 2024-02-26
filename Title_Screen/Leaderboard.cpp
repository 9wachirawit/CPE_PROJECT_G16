#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum playerNumber {Tul, Jao9, Uro, Keng, Bomb, TOTALPLAYERS};
int score[5] = { 0,0,0,0,0 };
string playerNames[5]{ "Tul","Jao9","Uro","Keng","Bomb" };

int main()
{
	for (int i = 0; i <= TOTALPLAYERS -1; i++)
	{
		cout << endl;
		cout << "Please enter " << playerNames[i] << " score (MAX 999):" << endl;
		cin >> score[i];
		cout << endl;

		cout << "             o--o0o--o             " << endl;
		cout << " 8=8========LEADERBOARD========8=8 " << endl;
		cout << "  |  NAME                SCORE  |  " << endl;
		cout << "  |                             |  " << endl;

		for (int j = 0; j <= 4; j++)
		{
			int temp = score[j], tempPos=0;

			if (temp <= 9)
			{
				tempPos = 1;
			}
			else
			{
				while (temp != 0)
				{
					temp = temp / 10;
					tempPos++;
				}
			}

			int positionOne = 24 - ((playerNames[j].size())+tempPos);

			cout << "  |  " << playerNames[j];
			for (int k = 0; k <= positionOne; k++)
			{
				cout << " ";
			}
			cout << score[j];
			cout << "  |" << endl;
		}
		
		cout << "  |                             |  " << endl;
		cout << " 8=8===========================8=8 " << endl;
		cout << "             o--o0o--o             " << endl;
		cout << endl;
	}

	return 0;
}
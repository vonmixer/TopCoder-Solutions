//SRM 534 Div 2 Medium
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

using namespace std;

class EllysCheckers
{
public:
	string getWinner(string board);
};

bool make_move(string& board)
{
	bool done = false;
	for(int i=0; i<board.size()-1; ++i)
	{
		if(board[i] == 'o')
		{
			if(board[i+1]=='.')
			{
				board.erase(i,2);
				board.insert(i,".o");
				done = true;
			}
			else if(i+3<board.size()-1)
			{
				if((board[i+3]=='.')&&(board[i+1]=='o')&&(board[i+2]=='o'))
				{
					board.erase(i,1);
					board.insert(i,".");
					board.erase(i+3,1);
					board.insert(i+3,"o");
					done = true;
				}
			}
		}
		if(done)
			break;
	}
	return done;
}

int get_player(int current)
{
	if(current)
		return 0;
	else
		return 1;
}

void clear_board(string& board)
{
	board.erase(board.size()-1);
	board+='.';
}

string EllysCheckers::getWinner(string board)
{
	clear_board(board);

	int current_player = 0;
	bool lose;
	do
	{
		lose = !make_move(board);
		current_player = get_player(current_player);
		clear_board(board);
	}while(!lose);
	
	if(current_player)
		return "NO";
	return "YES";
}

int main()
{
	EllysCheckers lala;
	string a0 = ".o...";
	lala.getWinner(a0);
	return 0;
}

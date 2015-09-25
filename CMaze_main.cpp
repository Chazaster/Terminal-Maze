#include <iostream>
#include "SetLimits.h"
#include "CMaze.h"
using namespace std;

int main ()
{
    SetLimits ();
    char play = 'y';
    CMaze maze;
    maze.Instructions (cout, cin);
    while (tolower (play) == 'y')
    {
	maze.Init(21, 31);
	maze.Display (cout);
	bool finished = false, quitting = false;
	while (!finished && !quitting)
	{
		char key;
		cout << endl;
		cout << "\nEnter move (a = left, w = up, d = right, s = down,\n\tq = quit, i = instructions): ";
		cin >> key;
		if (key == 'q')
			quitting = true;
		else if (key == 'i')
			maze.Instructions (cout, cin);
		else
			maze.Move(key);
		finished = maze.Done();
		maze.Display (cout);
	}
	maze.Message (finished, cout);
	cout << "Would you like to play again (y/n)? ";
	cin >> play;
	cin.clear ();;
    }
    cout << endl;
    return 0;
}

// Add Documentation here

#ifndef CMAZE_H
#define CMAZE_H

#include <iostream>
using namespace std;

enum sType {WALL, EMPTY, ME, GOAL, CRUMB};

class CMaze
{
	public:
        CMaze ();
        CMaze (const CMaze & other);
        ~CMaze ();
        CMaze & operator = (const CMaze & other);
	void Init (int R, int C);
        void Instructions (ostream & outs, istream & ins);
        void Display (ostream & outs);
        void Move (char direction);
        void Message (bool done, ostream & outs);
	void DFS(int currentRow, int currentCol);
	void Temporary();
	bool Done ();
	bool finished;
	int endCol, endRow;
	int numRows, numCols;
	int currentRow, currentCol;
    private:
	struct CMazeSquare
	{
	    CMazeSquare ();
		void Display (ostream & outs);
		sType what;
	};
	CMazeSquare ** grid;
        
};

#endif

// Title: CMaze cpp file
// File: CMaze.cpp
// Author: Chase Watson             
// Description: This file generates the maze and allows the user to play the maze 

#include "SetLimits.h"
#include <time.h>
#include <ctime>
#include "CMaze.h"
#include <stdlib.h>
CMaze::CMazeSquare::CMazeSquare ()
{
// This function will define what as wall

	what = WALL;
}

void CMaze::CMazeSquare::Display (ostream & outs)
{
// This function will use a switch to define the characters that are the graphics of the maze

		char achar;
		switch (what)
		{
			case WALL:
				achar = 'X';
				break;
			case EMPTY:
				achar = ' ';
				break;
			case ME:
				achar = 'O';
				break;
			case GOAL:
				achar = '$';
				break;
			case CRUMB:
				achar = '.';
				break;
		}
		outs << achar << ' ';
}

CMaze::CMaze ()
{
// This function will define the maze and create an empty grid

        numRows = 1;
        numCols = 1;
        grid = new CMazeSquare * [1];
        grid[0] = new CMazeSquare [1];
		finished = false;
        currentRow = 0;
        currentCol = 0;
        endRow = 0;
        endCol = 0;
}

CMaze::~CMaze ()
{
// This function will delete the grid if the initialized numRows is greater than 0

	for (int r = 0; r < numRows; r++)
		delete [] grid[r];
	delete [] grid;
}

void CMaze::Init (int R, int C)
{
// This function will call the temporary file so that the maze can generate

        numRows = R;
        numCols = C;
        grid = new CMazeSquare * [numRows];
        for (int r = 0; r < numRows; r++)
            grid[r] = new CMazeSquare [numCols];
	// Put your code for generating a maze here
        Temporary ();
	finished = false;
        currentRow = 1;
        currentCol = 1;
        grid [currentRow][currentCol].what = ME;
        endRow = numRows-2;
        endCol = numCols-2;
        grid [endRow][endCol].what = GOAL;
}

void CMaze::Instructions (ostream & outs, istream & ins)
{
// This function will print the instructions for the user

	outs << "Solve the maze! Use the a, s, d, and w keys to move\n" << endl;
}

void CMaze::Display (ostream & outs)
{
// This function will display the generate maze

		int r, c;
		for (r = 0; r < numRows; r++)
		{
			for (c = 0; c < numCols; c++)
				grid [r][c].Display (outs);
			outs << endl;
		}
}

void CMaze::Move (char direction)
{
// This function will allow the user to move using the a, w, d, and s keys using a switch

        switch (direction)
        {
			case 'a': case 'A':
			  if (grid[currentRow][currentCol - 1].what != WALL)
			    {
			      grid[currentRow][currentCol].what = CRUMB;
			      grid[currentRow][currentCol - 1].what = ME;
			      currentCol -= 1;
			      break;
			    }
			  else
			    break;
			  
			case 'w': case 'W':
			  if (grid[currentRow - 1][currentCol].what != WALL)
			    {
			      grid[currentRow][currentCol].what = CRUMB;
			      grid[currentRow - 1][currentCol].what = ME;
			      currentRow -= 1;
			      break;
			    }
			  else
			    break;

			case 'd': case 'D': 
			  if (grid[currentRow][currentCol + 1].what != WALL)
			    {
			      grid[currentRow][currentCol].what = CRUMB;
			      grid[currentRow][currentCol + 1].what = ME;
			      currentCol += 1;
			      break;
			    }
			  else
			    break;

			case 's': case 'S': 
			  if (grid[currentRow + 1][currentCol].what != WALL)
			    {
			      grid[currentRow][currentCol].what = CRUMB;
			      grid[currentRow + 1][currentCol].what = ME;
			      currentRow += 1;
			      break;
			    }
			  else
			    break;
        }
}

void CMaze::Message (bool done, ostream & outs)
{
// This function will print the end message
  if (ME != grid[endRow][endCol].what)
    outs << "Game has ended" << endl;
  else
    outs << "CONGRATULATIONS YOU WON!!!\n" << endl;
}

bool CMaze::Done () 
{
  if (ME == grid[endRow][endCol].what)
    return true;
  return false;
}


void CMaze::Temporary ()
{
// This function will randomly generate the walls inside the maze
  srand(time(NULL));
  int currentRow, currentCol;
  currentRow = 2 * (rand() % 10) + 1;
  if (currentRow % 2 == 0)
    {
      currentRow++;
    }
  if (currentRow == 20)
    {
      currentRow--;
    }
  currentCol = 2 * (rand() % 15) + 1;
  if (currentCol % 2 == 0)
    {
      currentCol++;
    }
  if (currentCol == 30)
    {
      currentCol--;
    }
  DFS(currentRow, currentCol);
    
}

void CMaze::DFS (int currentRow, int currentCol)
{
// This function will generate the spaces within the walls of the maze using the depth first search method 
  int dir = (rand() % 4);
  for (int i =0; i < 4; i++)
    {
      grid[currentRow][currentCol].what = EMPTY;
      // Left Movement
      if (dir == 0)
	{
	  if (currentCol - 2 > 0)
	    {
	      if (grid[currentRow][currentCol - 2].what != EMPTY)
		{
		  grid[currentRow][currentCol - 2].what = EMPTY;
		  grid[currentRow][currentCol - 1].what = EMPTY;
		  DFS(currentRow, currentCol - 2);
		}
	    }
	}

      // Up Movement
      else if (dir == 1)
	{
	  if (currentRow - 2 > 0)
	    {
	      if (grid[currentRow - 2][currentCol].what != EMPTY)
		{
		  grid[currentRow - 2][currentCol].what = EMPTY;
		  grid[currentRow - 1][currentCol].what = EMPTY;
		  DFS(currentRow - 2, currentCol);
		}
	    }
	}
      
      // Down Movement
      else if (dir == 2)
	{
	  if (currentRow + 2 < numRows - 1)
	    {
	      if (grid[currentRow + 2][currentCol].what != EMPTY)
		{
		  grid[currentRow + 2][currentCol].what = EMPTY;
		  grid[currentRow + 1][currentCol].what = EMPTY;
		  DFS(currentRow + 2, currentCol);
		}
	    }
	}

      // Right Movement
      else if (dir == 3)
	{
	  if (currentCol + 2 < numCols - 1)
	    {
	      if (grid[currentRow][currentCol + 2].what != EMPTY)
		{
		  grid[currentRow][currentCol + 2].what = EMPTY;
		  grid[currentRow][currentCol + 1].what = EMPTY;
		  DFS(currentRow, currentCol + 2);
		}
	    }
	}
      dir = dir == 3?0:dir+1;
    }
}  

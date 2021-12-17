#include "Before.h"

Before::Before(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			arr[i][j] = 0;
		}
	}

	/*
	//dynamic 2D array
	arr = new int*[nRows];
	for (int i = 0; i < nRows; ++i)
	{
		arr[i] = new int[nCols];

		for (int j = 0; j < nCols; j++)
			arr[i][j] = 0;
	}
	*/
}

/*
Before::~Before()
{
	for (int i = 0; i < m_rows; ++i) {
		delete[] arr[i];
	}
	delete[] arr;
}
*/

/*
The record function is to be called to notify the History object that the player was at a grid point
(in the Arena that the History object corresponds to) when the player dealt a fatal blow to a zombie.
The function returns false if row r, column c is not within bounds; otherwise, it returns true after
recording what it needs to. This function expects its parameters to be expressed in the same coordinate
system as the Arena (e.g., row 1, column 1 is the upper-left-most position).


Thought Process:
- will be called in Arena since it keeps track of Zombies and Player
- when Zombie dies, the code that runs in Arena will also run record(player's position)
- 2D array to handle the data storage


*/
//m_history.record(m_player->row(), m_player->col()); //NEW CODE FOR HISTORY!!!
bool Before::keepTrack(int r, int c)
{
	if (r > m_rows || c > m_cols)
		return false;
	arr[r - 1][c - 1] = arr[r - 1][c - 1] + 1;
	return true;
}


/*
The display function clears the screen and displays the history grid as the posted programs do. This
function does clear the screen, display the history grid, and write an empty line after the history
grid; it does not print the Press enter to continue. after the display. (Note to Xcode users: It is
acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your
program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
*/
void Before::printWhatWasBefore() const
{
	// Position (row,col) of the arena coordinate system is represented in
	// the array element grid[row-1][col-1]
	char grid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < MAXROWS; r++)
		for (c = 0; c < MAXCOLS; c++)
			grid[r][c] = '.';

	//Use the 2D array "arr" to place letters where they belong
	for (r = 0; r < MAXROWS; r++)
	{
		for (c = 0; c < MAXCOLS; c++)
		{
			if (arr[r][c] > 0)
			{
				if (arr[r][c] >= 26)
					grid[r][c] = 'Z';
				else
					grid[r][c] = 64 + arr[r][c];
			}
		}
	}


	// Draw the grid
	clearScreen();
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;

}
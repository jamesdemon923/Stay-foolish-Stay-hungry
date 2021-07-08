#ifndef PREVIOUS_H
#define PREVIOUS_H

#include "globals.h"

using namespace std;

class Previous
{
private:
	int m_rows;
	int m_cols;
	char grid[MAXROWS][MAXCOLS];
public:
	Previous(int nRows, int nCols);
	bool dropACrumb(int r, int c);
	void showPreviousMoves() const;
};

#endif // !PREVIOUS_H

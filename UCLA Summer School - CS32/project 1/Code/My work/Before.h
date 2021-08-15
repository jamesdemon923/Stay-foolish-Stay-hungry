#ifndef BEFORE_H
#define BEFORE_H

#include "globals.h"

class Before
{
public:
	Before(int nRows, int nCols);
	bool keepTrack(int r, int c);
	void printWhatWasBefore() const;
private:
	int m_rows;
	int m_cols;
	int arr[MAXROWS][MAXCOLS];
};

#endif
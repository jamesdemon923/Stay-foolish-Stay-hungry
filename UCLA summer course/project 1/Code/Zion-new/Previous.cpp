#include "Previous.h"
#include "globals.h"
#include<iostream>
using namespace std;

Previous::Previous(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 1; i <= m_rows; i++) {
		for (int j = 1; j <= m_cols; j++) {
			grid[i][j] = '.';
		}
	}
}

bool Previous::dropACrumb(int r, int c) {
	if (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols) {
		if (grid[r][c] == '.')
			grid[r][c] = 'A';
		else if (grid[r][c] == 'Z');
		else grid[r][c] = grid[r][c] + 1;
		return true;
	}
	else {
		if (grid[r][c] == '.')
			grid[r][c] = 'A';
		else if (grid[r][c] == 'Z');
		else grid[r][c] = grid[r][c] + 1;
		return false;
	}
}

void Previous::showPreviousMoves() const {
	clearScreen();
	for (int i = 1; i <= m_rows; i++) {
		for (int j = 1; j <= m_cols; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
	cout << "\"Press Enter to continue\"" << endl;
	cin.ignore(10000, '\n');
}


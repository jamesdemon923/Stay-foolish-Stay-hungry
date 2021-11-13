//
//  Previous.h
//  ZionMultiFileSoln
//

#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class Previous
{
  public:
    Previous(int nRows, int nCols);

        // Accessors
    void showPreviousMoves() const;

        // Mutators
    bool dropACrumb(int r, int c);

  private:
    int  m_grid[MAXROWS][MAXCOLS];
    int  m_rows;
    int  m_cols;
};

#endif // PAST_H

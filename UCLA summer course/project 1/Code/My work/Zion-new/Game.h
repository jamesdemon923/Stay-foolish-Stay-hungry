#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "Previous.h"
class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
    Previous* m_previous;
};

#endif

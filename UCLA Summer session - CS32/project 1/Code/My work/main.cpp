/*
#include "Game.h"
#include <cstdlib>
#include <ctime>

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
	// Initialize the random number generator.  (You don't need to
	// understand how this works.)
	srand(static_cast<unsigned int>(time(0)));

	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 3, 2);
	Game g(15, 18, 80);

	// Play the game
	g.play();
}
*/

/*
#include "Game.h"
#include "Game.h"
#include "Arena.h"
#include "Arena.h"
#include "Before.h"
#include "Before.h"
#include "Player.h"
#include "Player.h"
#include "Robot.h"
#include "Robot.h"
#include "globals.h"
#include "globals.h"
int main()
{}
*/

/*
#include "Before.h"
int main()
{
	Before bf(2, 2);
	bf.keepTrack(1, 1);
	bf.printWhatWasBefore();
}
*/

/*
#include "Robot.h"
int main()
{
	Robot r(0, 1, 1);
}
*/

/*
#include "Player.h"
int main()
{
	Player p(0, 1, 1);
}
*/

/*
#include "Arena.h"
int main()
{
	Arena a(10, 18);
	a.addPlayer(2, 2);
}
*/

/*
#include "globals.h"
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/

/*
#include "Arena.h"
#include "Player.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/

/*
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/

/*
#include "Arena.h"
#include "Player.h"
#include "Before.h"
#include "globals.h"
int main()
{
	Arena a(2, 2);
	a.addPlayer(1, 1);
	a.player()->move(RIGHT);
	a.player()->stand();
	a.player()->move(DOWN);
	a.whatWasBefore().printWhatWasBefore();
}
*/


///THESE MUST NOT BUILD SUCCESSFULLY

/*
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
	Robot r(&a, 1, 1);
}
*/

/*
#include "globals.h"
#include "Robot.h"
#include "Player.h"
int main()
{
	Arena a(10, 10);
}
*/

/*#include "Before.h"
int main()
{
	Before bf;
}
*/
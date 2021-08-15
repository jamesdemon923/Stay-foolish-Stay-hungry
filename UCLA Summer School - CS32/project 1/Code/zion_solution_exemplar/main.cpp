//main.cpp

#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/////////////////////////////////////////////////////////////////////////
//  main()
/////////////////////////////////////////////////////////////////////////

int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:
    //Game g(3, 3, 2);
    Game g(15, 18, 80);
    
    // Play the game
    g.play();
}

//#include <string>
//#include "Arena.h"
//#include "Player.h"
//#include "Past.h"
//#include "globals.h"
//#include <sstream>
//#include <iostream>
//using namespace std;
//
//class StreambufSetter
//{
//public:
//	StreambufSetter(ios& str, streambuf* sb)
//		: stream(str), oldsb(str.rdbuf(sb))
//	{}
//	~StreambufSetter() { stream.rdbuf(oldsb); }
//private:
//	ios & stream;
//	streambuf* oldsb;
//};
//
//int main()
//{
//	ostringstream oss;
//
//	StreambufSetter ssout(cout, oss.rdbuf());
//	Arena a(2, 2);
//	a.addPlayer(1, 1);
//	a.player()->move(RIGHT);
//	a.player()->stand();
//	a.player()->shoot(LEFT);
//	a.player()->move(DOWN);
//	a.thePast().printThePast();
//	string s = oss.str();
//	string::size_type p = 0;
//	p = s.find(".C\n.A\n\n", p);
//	if (p == string::npos) {
//		return 1;
//	}
//	return 0;
//}

#include "OnlineDating.h"
#include "memleak.h"
#include <iostream>
#include <cassert>

		using namespace std;

	void test()
	{
		cerr << "test A" << endl;
		OnlineDating s;
		cerr << "test B" << endl;
		s.makeMatch("J", "Xu", IntWrapper(10));
		cerr << "test C" << endl;
		s.makeMatch("C", "Jiang", IntWrapper(20));
		cerr << "test D" << endl;
		OnlineDating s2;
		cerr << "test E" << endl;
		s2.makeMatch("DL", "Wang", IntWrapper(30));
		cerr << "test F" << endl;
		s2 = s;
		cerr << "test G" << endl;
		s2.makeMatch("XR", "Xu", IntWrapper(40));
		cerr << "test H" << endl;
	}

	int main()
	{
		test();
		cerr << "DONE" << endl;
	}
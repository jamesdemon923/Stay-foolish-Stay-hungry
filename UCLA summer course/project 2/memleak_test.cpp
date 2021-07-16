#include "OnlineDating.h"
#include <iostream>
#include <cassert>

using namespace std;

		void test()
		{
			OnlineDating s;
			cerr << "test s-1" << endl;
			s.insert(IntWrapper(10));
			cerr << "test s-2" << endl;
			s.insert(IntWrapper(20));
			OnlineDating s2;
			cerr << "test s2" << endl;
			s.insert(IntWrapper(30));
			s2 = s;
			cerr << "test s2 = s" << endl;
			s.insert(IntWrapper(40));
		}

		int main()
		{
			test();
			cerr << "ALL DONE" << endl;
		}
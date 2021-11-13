/*

#include "LinkedList.h"
#include <cassert>

//putting all the tests into methods
void testInsertAndGet()
{
	LinkedList ls;
	ls.insertToFront("Steve");
	ls.insertToFront("Judy");
	ls.insertToFront("Laura");
	ls.insertToFront("Eddie");
	ls.insertToFront("Hariette");
	ls.insertToFront("Carl");
	for (int k = 0; k < ls.size(); k++)
	{
		string x;
		ls.get(k, x);
		cout << x << endl;
	}

	cout << "This should print:" << endl;
	cout << "Carl" << endl;
	cout << "Hariette" << endl;
	cout << "Eddie" << endl;
	cout << "Laura" << endl;
	cout << "Judy" << endl;
	cout << "Steve" << endl;
}

void testPrints()
{
	LinkedList ls;
	ls.insertToFront("Eric");
	ls.insertToFront("Shawn");
	ls.insertToFront("Topanga");
	ls.insertToFront("Cory");
	ls.printList();
	ls.printReverse();

	cout << "This should print:" << endl;
	cout << "Cory Topanga Shawn Eric" << endl;
	cout << "Eric Shawn Topanga Cory" << endl;
}

void testAppend()
{
	LinkedList e1;
	e1.insertToFront("bell");
	e1.insertToFront("biv");
	e1.insertToFront("devoe");
	LinkedList e2;
	e2.insertToFront("Andre");
	e2.insertToFront("Big Boi");
	e1.append(e2); // adds contents of e2 to the end of e1
	string s;
	assert(e2.size() == 2 && e2.get(1, s) && s == "Andre");
	assert(e1.size() == 5 && e1.get(3, s) && s == "Big Boi");

	cout << "append yeeted" << endl;
}

void testReverseList()
{
	LinkedList e1;
	e1.insertToFront("Sam");
	e1.insertToFront("Carla");
	e1.insertToFront("Cliff");
	e1.insertToFront("Norm");
	e1.reverseList(); // reverses the contents of e1
	string s;
	assert(e1.size() == 4 && e1.get(0, s) && s == "Sam");

	cout << "reverseList yeeted" << endl;
}

void testSwap()
{
	LinkedList e1;
	e1.insertToFront("A");
	e1.insertToFront("B");
	e1.insertToFront("C");
	e1.insertToFront("D");
	LinkedList e2;
	e2.insertToFront("X");
	e2.insertToFront("Y");
	e2.insertToFront("Z");
	e1.swap(e2); // exchange contents of e1 and e2
	string s;
	assert(e1.size() == 3 && e1.get(0, s) && s == "Z");
	assert(e2.size() == 4 && e2.get(2, s) && s == "B");

	cout << "swap yeeted" << endl;
}

int main()
{
	testInsertAndGet();
	testPrints();
	testAppend();
	testReverseList();
	testSwap();
}

*/


/*

#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <csignal>
#include <regex>
#include <type_traits>
#include <set>
#include <iostream>
#include "LinkedList.h"
using namespace std;

class streambuf_switcher
{
public:
	streambuf_switcher(ios& dest, ios& src)
		: dest_stream(dest), saved_streambuf(dest.rdbuf(src.rdbuf()))
	{}
	~streambuf_switcher()
	{
		dest_stream.rdbuf(saved_streambuf);
	}
private:
	ios & dest_stream;
	streambuf* saved_streambuf;
};

set<void*> addrs;
bool recordaddrs = false;

void* operator new(size_t n)
{
	void* p = malloc(n);
	if (recordaddrs && n == sizeof(Node))
	{
		recordaddrs = false;
		addrs.insert(p);
		recordaddrs = true;
	}
	return p;
}

void operator delete(void* p) noexcept
{
	if (recordaddrs)
	{
		recordaddrs = false;
		set<void*>::iterator it = addrs.find(p);
		if (it != addrs.end())
			addrs.erase(it);
		recordaddrs = true;
	}
	free(p);
}

void operator delete(void* p, std::size_t s) noexcept
{
	s = addrs.size();   // these two lines do nothing other than
	s += s;               // getting rid of unused var warning on g++
	if (recordaddrs)
	{
		recordaddrs = false;
		set<void*>::iterator it = addrs.find(p);
		if (it != addrs.end())
			addrs.erase(it);
		recordaddrs = true;
	}
	free(p);
}

void testone(int n)
{
	LinkedList empty;

	LinkedList l1;
	l1.insertToFront(9); l1.insertToFront(8); l1.insertToFront(7);

	LinkedList l2;
	l2.insertToFront(4); l2.insertToFront(3);

	ItemType x;
	switch (n)
	{
	default: {
		cout << "Bad argument" << endl;
	} break; case 1: {
		assert(empty.size() == 0);
	} break; case 2: {
		assert(l1.size() == 3);
	} break; case 3: {
		assert(!empty.get(0, x));
	} break; case 4: {
		assert(l1.get(0, x) && x == 7);
	} break; case 5: {
		assert(l1.get(2, x) && x == 9);
	} break; case 6: {
		assert(!l1.get(3, x));
	} break; case 7: {
		LinkedList l3(l1);
		assert(l3.size() == 3);
		assert(l1.size() == 3);
		assert(l1.get(1, x) && x == 8);
	} break; case 8: {
		LinkedList l3;
		l3 = l1;
		assert(l3.size() == 3);
		assert(l1.size() == 3);
		assert(l1.get(1, x) && x == 8);
	} break; case 9: {
		LinkedList l3(empty);
		assert(l3.size() == 0);
	} break; case 10: {
		l1.reverseList();
		assert(l1.get(0, x) && x == 9);
	} break; case 11: {
		l1.reverseList();
		assert(l1.get(2, x) && x == 7);
	} break; case 12: {
		empty.reverseList();
		assert(empty.size() == 0);
	} break; case 13: {
		ostringstream strCout;
		streambuf_switcher sso(cout, strCout);
		l1.printList();
		string str = strCout.str();
		regex e("7.*8.*9"); // 7 followed by 8 followed by 9
		assert(regex_search(str, e));
	} break; case 14: {
		ostringstream strCout;
		streambuf_switcher sso(cout, strCout);
		l1.printReverse();
		string str = strCout.str();
		regex e("9.*8.*7"); // 9 followed by 8 followed by 7
		assert(regex_search(str, e));
		// make sure they didn't take off const after printReverse
		assert((is_same<decltype(&LinkedList::printReverse), void (LinkedList::*)() const>::value));
	} break; case 15: {
		recordaddrs = true;
		{
			LinkedList l;
			int oldn = addrs.size();
			l.insertToFront(1);
			l.insertToFront(1);
			l.insertToFront(1);
			l.insertToFront(1);
			assert(addrs.size() == oldn + 4);
		}
		assert(addrs.size() == 0);
		recordaddrs = false;
	} break; case 16: {
		recordaddrs = true;
		int oldn = addrs.size();
		l1.append(l2);
		assert(addrs.size() == oldn + 2);
		assert(l1.size() == 5);
		assert(l1.get(0, x) && x == 7);
		assert(l1.get(4, x) && x == 4);
		recordaddrs = false;
	} break; case 17: {
		LinkedList l;
		recordaddrs = true;
		int oldn = addrs.size();
		l.append(l2);
		assert(l.size() == 2);
		assert(l2.size() == 2);
		assert(addrs.size() == oldn + 2);
		recordaddrs = false;
	} break; case 18: {
		l1.swap(l2);
		assert(l1.size() == 2);
		assert(l2.size() == 3);
		assert(l1.get(0, x) && x == 3);
		assert(l1.get(1, x) && x == 4);
		assert(l2.get(0, x) && x == 7);
		assert(l2.get(2, x) && x == 9);
	} break; case 19: {
		LinkedList l;
		l1.swap(l);
		assert(l.size() == 3);
		assert(l.get(0, x) && x == 7);
		assert(l1.size() == 0);
		assert(!l1.get(0, x));
	} break; case 20: {
		int oldn = 0;
		{
			LinkedList l;
			recordaddrs = true;
			oldn = addrs.size();
			l.insertToFront(1);
			assert(l.size() == 1);
			assert(addrs.size() == oldn + 1);
		}
		assert(addrs.size() == 0);
		recordaddrs = false;
	} break;
	}
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout << "Passed" << endl;
}
*/


//dummy main

int main()
{

}
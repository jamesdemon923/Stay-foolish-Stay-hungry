#include "WordTree.h"
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

void test1()
{
	cout << "------------Test 1------------" << endl;
	WordTree k;

	k.add("Kim");
	k.add("Kanye");
	k.add("Kanye");
	k.add("Kanye");
	assert(k.distinctWords() == 2);
	assert(k.totalWords() == 4);
}

void test2()
{
	cout << "------------Test 2------------" << endl;
	WordTree w;

	w.add("Harry");
	w.add("Niall");
	w.add("Niall");
	w.add("Liam");
	w.add("Louis");
	w.add("Harry");
	w.add("Niall");
	w.add("Zayn");

	cout << w;
}

void test3()
{
	cout << "------------Test 3------------" << endl;
	WordTree e;

	WordTree e2 = e;

	cout << e << endl;
	cout << e2 << endl;
	cout << "There are 2 empty lines because we created 2 empty trees" << endl;
}

int main()
{
	test1();
	test2();
	test3();

	cout << endl << "All Tests Passed." << endl;
}
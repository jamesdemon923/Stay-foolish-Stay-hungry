#include "WordTree.h"
#include <cassert>
#include <string>
#include <fstream>
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

void test4()
{
	cout << "------------Test 4------------" << endl;
	ifstream fin;
	ofstream fout;
	string filename;
	cout << "Enter name of file with text to analyze: ";
	cin >> filename;
	fin.open(filename.c_str());
	if (fin.fail())
	{
		cout << "Error opening file.\n";
		exit(1);
	}
	cout << "\nAnalyzing " << filename << ".\n";

	WordTree myTree;
	WordType v;
	while (fin >> v) 
	{ 
		myTree.add(v);
	};

	fin.close();

	fout.open("results.txt");
	cout << "\nWord counts:\n\n";
	cout << myTree;
	fout << myTree;
	cout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
	fout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
	cout << "Number of distinct words appearing in text: "
		<< myTree.distinctWords() << ".\n";
	fout << "Number of distinct words appearing in text: "
		<< myTree.distinctWords() << ".\n";
	fout.close();
}

int main()
{
	test1();
	test2();
	test3();
	test4();

	cout << endl << "All Tests Passed." << endl;
	return 0;
}
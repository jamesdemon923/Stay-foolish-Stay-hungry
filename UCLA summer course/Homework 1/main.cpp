#include "LinkedList.h"
#include<iostream>
#include<string>

using namespace std;

int main() {
	LinkedList L;
	L.insertToFront("ABC");
	L.insertToFront("DEF");
	L.insertToFront("GHI");
	LinkedList L2(L);
	LinkedList L3;
	L3 = L2;
	L2.printList();
	L3.printList();
	string ww;
	L3.get(2, ww);
	cout << "this is " << ww << endl;

	cout << "reverse this" << endl;
	L3.reverseList();
	L3.printList();

	cout << "print reverse" << endl;
	L3.printReverse();
	L3.printList();

	cout << "append test" << endl;
	LinkedList L4;
	L4.insertToFront("JKL");
	L4.insertToFront("MNO");
	L3.append(L4);
	L3.printList();

	cout << "swap test" << endl;
	L3.swap(L4);
	L3.printList();
	cout << endl;
	L4.printList();
}
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
using namespace std;

typedef string ItemType;

struct Node {
    ItemType value;
    Node *next;
};

class LinkedList {
private:
    Node *head=nullptr;
	Node * findLast() const;
	void printReverse_aux(const Node *ptr) const;
public:
	// default constructor
	LinkedList();
	// copy constructor
	LinkedList(const LinkedList& rhs);
    // assignment operator
	const LinkedList& operator=(const LinkedList& rhs);
	// destructor
	~LinkedList();

	// mutator and accessor functions
	void printList() const;
	bool get(int i, ItemType& item) const;
	void reverseList();
	void insertToFront(ItemType item);
	void printReverse() const;
	void append(const LinkedList &obj);
	void swap(LinkedList &obj);
	int size() const;
};
#endif
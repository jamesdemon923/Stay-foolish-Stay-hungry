#include "LinkedList.h"

// copy constructor
LinkedList::LinkedList(const LinkedList& rhs)
{
	//if rhs is an empty list, then there is nothing to do!
	//so, if rhs isn't a nullptr, then there IS stuff to COPY!
	if (rhs.head != nullptr)
	{
		head = nullptr; //safety I guess

		//can't think of another way around "empty lhs" 
		//for first step
		//this case is the "one-item" case
		head = new Node;
		head->value = rhs.head->value;
		head->next = rhs.head->next;

		//at this point, we have ONE item copied over
		Node* p = rhs.head; //iterator
		Node* curr = head;
		while (p->next != nullptr)
		{
			curr->next = new Node;
			curr->next->value = p->next->value;

			curr = curr->next;
			p = p->next;
		}
		//this will stop when p points to the last item, NOT null

		//make sure that the last item points to null
		curr->next = nullptr;
	}
}

// Destroys all the dynamically allocated memory
// in the list.
LinkedList::~LinkedList()
//Literally given in class!
{
	Node *p = head;
	while (p != nullptr)
	{
		Node *q = p->next;
		delete p;
		p = q;
	}
}

// assignment operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs)
// I think that this overloads the AO in the "copy constructor" case:
// "String x = s;"
// in this case: s2 = s, I think the default shallow copy will run which is what you want
{
	if (this != &rhs)
	{
		LinkedList temp(rhs);
		swap(temp);
	}

	return *this;
}

// Inserts val at the front of the list
void LinkedList::insertToFront(const ItemType &val)
//GIVEN IN CLASS
{
	Node* p = new Node;
	p->value = val;
	p->next = head;
	head = p;
}

// Prints the LinkedList
void LinkedList::printList() const
//GIVEN IN CLASS
{
	Node* p = head;
	for (; p->next != nullptr; p = p->next)
		//"should ONLY HAVE SPACES BETWEEN"
	{
		cout << p->value << " ";
	}
	//p is now the last item
	cout << p->value;
	cout << endl;
}

// Sets item to the value at position i in this
// LinkedList and return true, returns false if 
	// there is no element i
bool LinkedList::get(int i, ItemType& item) const
{
	int size = this->size();
	if (i < 0 || i >= size)
		return false;
	//GREEN LIGHT: if size is 0, this will NOT run
	Node* p = head;
	for (int indexP = 1; indexP <= i; indexP++)
		//When this loop runs, the index P will be at will be "indexP"
	{
		p = p->next;
	}
	item = p->value;
	return true;
}

// Reverses the LinkedList
void LinkedList::reverseList()
{
	revList(head);
}

// HELPER to do things recursively
void LinkedList::revList(Node* start)
{
	if (start == nullptr)
		return;
	if (start->next == nullptr)
	{
		head = start;
		return;
	}
	//at this point, start must be something that ISNT null and ISNT the last node
	revList(start->next);
	start->next->next = start;
	start->next = nullptr;
}

// Prints the LinkedList in reverse order
void LinkedList::printReverse() const
{
	printRev(head);
	cout << endl;
}

// HELPER method to do things revursively
void LinkedList::printRev(Node* start) const
{
	if (start == nullptr)
		return;
	//"should ONLY HAVE SPACES BETWEEN"
	printRev(start->next);
	if (start->next == nullptr)
		cout << start->value;
	else
		cout << " " << start->value;
}

// Appends the values of other onto the end of this
// LinkedList.
void LinkedList::append(const LinkedList &other)
{
	Node* p = head;
	if (head != nullptr)
	{
		while (p->next != nullptr)
			p = p->next;
	}
	LinkedList temp(other);
	p->next = temp.head;
	temp.head = nullptr;
}

// Exchange the contents of this LinkedList with the other
// one.
void LinkedList::swap(LinkedList &other)
{
	Node* tempPtr = this->head;
	//BIG STRATS: CAN use other.head because we are technically in LL's scope!!!
	this->head = other.head;
	other.head = tempPtr;
	tempPtr = nullptr;
}

// Returns the number of items in the Linked List.
int LinkedList::size() const
// How I'm going to do this is that when this one runs, it does do a full count
// but there will be NO PRIVATE VARIABLE FOR SIZE, IT'LL JUST RUN ONCE AT THE
// BEGINNING of a method that needs size into a local so it doesn't need to run
// a lot!
{
	int ret = 0;
	Node *p = head;
	while (p != nullptr)
	{
		ret++;
		p = p->next;
	}
	return ret;
}
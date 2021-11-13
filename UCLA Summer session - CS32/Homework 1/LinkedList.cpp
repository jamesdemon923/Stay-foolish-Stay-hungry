#include <iostream>
#include "LinkedList.h"

// default constructor
LinkedList::LinkedList() : head(nullptr) { }

// copy constructor
LinkedList::LinkedList(const LinkedList& rhs)
{
	if (rhs.head == nullptr) head = nullptr;
	else {
		head = new Node;
		head->value = rhs.head->value;
		Node *q = head;
		Node *p = rhs.head->next;
		while (p != nullptr) {
			q->next = new Node;
			q->next->value = p->value;
			q->next->next = nullptr;
			p = p->next;
			q = q->next;
		}
	}
}

// assignment operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
	if (this == &rhs) return *this;
	LinkedList temp = rhs;
	swap(temp);
	return *this;
}

void LinkedList::insertToFront(ItemType val)
{
	Node *p = new Node;
	p->value = val;
	p->next = head;
	head = p;

	return;
}

void LinkedList::printList() const
{
    for (Node *p = head; p != nullptr; p = p->next)
		cout << p->value << " ";
	cout << endl;

	return;
}

LinkedList::~LinkedList()
{
	Node *p;
	while (head != nullptr) {
		p = head;
		head = head->next;
		delete p;
	}
}

bool LinkedList::get(int i, ItemType& item) const
{
	Node *p = head;
	for(int k=0; k < i && p != nullptr; k++, p=p->next)
		;
	if (p == nullptr)
		return false;
	item = p->value;
	return true;
}

void LinkedList::reverseList()
{
	// List size 0 or 1 do nothing
	if (head == nullptr || head->next == nullptr)
		return;
	Node *back, *current, *forward;
	back = head;
	current = head->next;
	forward = head->next->next;
	head->next = nullptr;
	current->next = back;
	while (forward != nullptr) {
		back = current;
		current = forward;
		forward = forward->next;
		current->next = back;
	}
	head = current;

	return;
}

void LinkedList::printReverse_aux(const Node *ptr) const {

	if (ptr == nullptr)
		return;
	printReverse_aux(ptr->next);
	cout << ptr->value << " ";
}

void LinkedList::printReverse() const
{
	printReverse_aux(head);
	return;
}

void LinkedList::append(const LinkedList &obj)
{
	LinkedList temp = obj;
	Node *last = findLast();
	// if empty, set it
	if (last == nullptr)
		head = temp.head;
	else
		last->next = temp.head;
	temp.head=nullptr;

	return;
}

void LinkedList::swap(LinkedList &obj)
{
	Node* temp = obj.head;
	obj.head = head;
	head = temp;

	return;
}

int LinkedList::size() const
{
	int count=0;
	for (Node *p = head; p != nullptr; p = p->next)
		count++;

	return count;
}

Node* LinkedList::findLast() const
{
	// returns nullptr if list is empty
	Node *p = head;
	while (p != nullptr) {
		if (p->next == nullptr)
			return p;
		p = p->next;
	}
	return nullptr;
}

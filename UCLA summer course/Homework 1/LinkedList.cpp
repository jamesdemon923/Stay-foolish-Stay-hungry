#include "LinkedList.h"
#include<iostream>
using namespace std;

LinkedList::LinkedList() {
	head = new Node("");
}

LinkedList::LinkedList(const LinkedList& rhs) {
	head = new Node("");
	Node* p1;
	Node* p2;
	p1 = head;
	p2 = rhs.head;
	while (p2->next) {
		Node* tmp = new Node("");
		p1->next = tmp;
		(p1->next)->value = (p2->next)->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}

LinkedList::~LinkedList() {
	delete head;
}

const LinkedList& LinkedList::operator=(const LinkedList& rhs) {
	Node* p1;
	Node* p2;
	p1 = head;
	p2 = rhs.head;
	while (p2->next) {
		Node* tmp = new Node("");
		p1->next = tmp;
		(p1->next)->value = (p2->next)->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	return *this;
}

void LinkedList::insertToFront(const ItemType& val) {
	Node* p = new Node("");
	p->next = head->next;
	p->value = val;
	head->next = p;
}

void LinkedList::printList() const {
	Node* p = head->next;
	while (p) {
		cout << p->value << endl;
		p = p->next;
	}
}

bool LinkedList::get(int i, ItemType& item) const {
	Node* p = head;
	int c = this->size();
	if (i <= 0 || i > c)
		return false;
	else {
		while (i) {
			i--;
			p = p->next;
		}
		item = p->value;
		return true;
	}
}

void LinkedList::reverseList() {
	LinkedList temp(*this);
	int i = this->size();
	Node* p = head;
	while (i) {
		ItemType tmp;
		temp.get(i, tmp);
		(p->next)->value = tmp;
		p = p->next;
		i--;
	}
}

void LinkedList::printReverse()const {
	LinkedList t(*this);
	t.reverseList();
	t.printList();
}

void LinkedList::append(const LinkedList& other) {
	Node* p = head;
	while (p->next) p = p->next;
	Node* p1;
	Node* p2;
	p1 = p;
	p2 = other.head;
	while (p2->next) {
		Node* tmp = new Node("");
		p1->next = tmp;
		(p1->next)->value = (p2->next)->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}

void LinkedList::swap(LinkedList& other) {
	Node* p = other.head;
	other.head = this->head;
	this->head = p;
}

int LinkedList::size() const {
	Node* p = head;
	int i = 0;
	while (p->next) {
		i++;
		p = p->next;
	}
	return i;
}

#include "OnlineDating.h"
#include <string>
#include <iostream>

OnlineDating::OnlineDating() : head(nullptr) {}

OnlineDating::~OnlineDating()
{
	Node *p = head;
	while (p != nullptr)
	{
		Node *q = p->next;
		delete p;
		p = q;
	}
}

OnlineDating::OnlineDating(const OnlineDating& src)
{
	this->head = nullptr; 
	if (src.head != nullptr)
	{
		Node* p = src.head;
		while (p != nullptr)
		{
			this->makeMatch(p->firstName, p->lastName, p->data);
			p = p->next;
		}
	}
}

const OnlineDating& OnlineDating::operator=(const OnlineDating& rhs)
{
	if (this != &rhs)
	{
		OnlineDating temp(rhs);
		tradeMatches(temp);
	}
	return *this;
}

bool OnlineDating::noMatches() const
// Return true if the OnlineDating list is empty, otherwise false.
{
	return (head == nullptr);
}

int OnlineDating::howManyMatches() const 
// Return the number of matches on the OnlineDating list.
// just like with HW1, I will likely have this run to completion whenever I need a size AND THUS NOT have a private size variable
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

bool OnlineDating::makeMatch(const std::string& firstName, const std::string& lastName, const OnlineType& value)
// If the full name (both the first and last name) is not equal
// to any full name currently in the list then add it and return
// true. Elements should be added according to their last name.
// Elements with the same last name should be added according to
// their first names. Otherwise, make no change to the list and
// return false (indicating that the name is already in the
// list).
{
	if (head == nullptr)
	{
		head = new Node;
		head->firstName = firstName;
		head->lastName = lastName;
		head->data = value;
		head->next = nullptr;
		head->prev = nullptr;

		return true;
	}

	else
	{
		Node* p = head;
		while (p != nullptr)
		{
			if (p->lastName == lastName)
			{
				if (p->firstName == firstName)
				{
					return false;
				}

				else if (p->firstName > firstName)
				{
					Node* temp = p->prev;
					p->prev = new Node;
					p->prev->lastName = lastName;
					p->prev->firstName = firstName;
					p->prev->data = value;
					p->prev->next = p;
					p->prev->prev = temp;

					if (temp != nullptr)
						temp->next = p->prev;
					else
						head = p->prev;

					return true;
				}
				else if (p->next == nullptr)
				{
					p->next = new Node;
					p->next->lastName = lastName;
					p->next->firstName = firstName;
					p->next->data = value;
					p->next->next = nullptr;
					p->next->prev = p;
					return true;
				}
			}

			else if (p->lastName > lastName)
			{
				Node* temp = p->prev; 

				p->prev = new Node;
				p->prev->lastName = lastName;
				p->prev->firstName = firstName;
				p->prev->data = value;
				p->prev->next = p;
				p->prev->prev = temp;
				if (temp != nullptr)
					temp->next = p->prev;
				else
					head = p->prev;

				return true;
			}

			else if (p->next == nullptr)
			{
				p->next = new Node;
				p->next->lastName = lastName;
				p->next->firstName = firstName;
				p->next->data = value;
				p->next->next = nullptr;
				p->next->prev = p;
				return true;
			}

			p = p->next;
		}

		return false;
	}
}

bool OnlineDating::transformMatch(const std::string& firstName, const std::string& lastName, const OnlineType & value)
// If the full name is equal to a full name currently in the
// list, then make that full name no longer map to the value it
// currently maps to, but instead map to the value of the third
// parameter; return true in this case. Otherwise, make no
// change to the list and return false.
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->lastName == lastName)
			if (p->firstName == firstName)
			{
				p->data = value;
				return true;
			}
		p = p->next;
	}
	return false;
}

bool OnlineDating::makeOrTransform(const std::string& firstName, const std::string& lastName, const OnlineType& value)
// If full name is equal to a name currently in the list, then
// make that full name no longer map to the value it currently
// maps to, but instead map to the value of the third parameter;
// return true in this case. If the full name is not equal to
// any full name currently in the list then add it and return
// true. In fact, this function always returns true.
{
	if (someoneAmongMatches(firstName, lastName))
		return transformMatch(firstName, lastName, value);
	else
		return makeMatch(firstName, lastName, value);
}

bool OnlineDating::blockPreviousMatch(const std::string& firstName, const std::string& lastName)
// If the full name is equal to a full name currently in the
// list, remove the full name and value from the list and return
// true. Otherwise, make no change to the list and return
// false.
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->lastName == lastName)
			if (p->firstName == firstName)
			{
				if (p->prev == nullptr)
				{
					head = p->next;
					p->next->prev = nullptr;
				}
				else if (p->next == nullptr)
				{
					p->prev->next = nullptr;
				}
				else
				{
					p->prev->next = p->next;
					p->next->prev = p->prev;
				}

				delete p;

				return true;
			}
		p = p->next;
	}

	return false;
}

bool OnlineDating::someoneAmongMatches(const std::string& firstName, const std::string& lastName) const
// Return true if the full name is equal to a full name
// currently in the list, otherwise false.
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->lastName == lastName)
			if (p->firstName == firstName)
				return true;
		p = p->next;
	}
	return false;
}

bool OnlineDating::lookA5Matches(const std::string& firstName, const std::string& lastName, OnlineType& value) const
// If the full name is equal to a full name currently in the
// list, set value to the value in the list that that full name
// maps to, and return true. Otherwise, make no change to the
// value parameter of this function and return false.
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->lastName == lastName)
			if (p->firstName == firstName)
			{
				value = p->data;
				return true;
			}
		p = p->next;
	}
	return false;
}

bool OnlineDating::confirmMatch(int i, std::string& firstName, std::string& lastName, OnlineType & value) const
// If 0 <= i < size(), copy into firstName, lastName and value
// parameters the corresponding information of the element at
// position i in the list and return true. Otherwise, leave the
// parameters unchanged and return false. (See below for details
// about this function.)
{
	if (0 <= i && i < howManyMatches())
	{
		Node* p = head;

		//you need to move the pointer i times from index 0
		for (int j = 1; j <= i; j++)
		{
			p = p->next;
		}

		//p now rests on the target node
		firstName = p->firstName;
		lastName = p->lastName;
		value = p->data;

		return true;
	}
	
	return false;
}

void OnlineDating::tradeMatches(OnlineDating& other)
// Exchange the contents of this list with the other one.
{
	Node* tempPtr = head;
	head = other.head;
	other.head = tempPtr;
	tempPtr = nullptr;
}

void OnlineDating::dump() const
{
	if (head == nullptr)
		std::cerr << "empty list" << std::endl;
	else
	{
		Node* p = head;

		std::cerr << "==========" << std::endl;
		std::cerr << "Forward:" << std::endl;
		for (; p->next != nullptr; p = p->next)
		{
			std::cerr << p->firstName << " " << p->lastName << " " << p->data << std::endl;
		}
		//p rests on the last node now
		std::cerr << p->firstName << " " << p->lastName << " " << p->data << std::endl;
		std::cerr << "==========" << std::endl;

		std::cerr << "Backward:" << std::endl;
		for (; p != nullptr; p = p->prev)
		{
			std::cerr << p->firstName << " " << p->lastName << " " << p->data << std::endl;
		}
		//this one doesn't have to stop
		std::cerr << "==========" << std::endl;
	}
}


//NONMEMBER FUNCTIONS
bool mergeMatches(const OnlineDating & odOne, const OnlineDating & odTwo, OnlineDating & odJoined)
{
	///OnlineDating throwaway (odOne);
	///odJoined.tradeMatches(throwaway);

	odJoined = odOne;

	std::string firstNombre;
	std::string lastNombre;
	OnlineType val;

	bool ret = true;

	int i = 0;
	while (odTwo.confirmMatch(i, firstNombre, lastNombre, val))
	{
		if (odJoined.makeMatch(firstNombre, lastNombre, val)) { }
		else
		{
			OnlineType compMe;
			odOne.lookA5Matches(firstNombre, lastNombre, compMe);

			//A duplicate name
			if (compMe == val) { }
			else
			//A duplicate name and VALUES are NOT the same
			{
				odJoined.blockPreviousMatch(firstNombre, lastNombre);
				ret = false;
			}
		}

		i++;
	}

	return ret;
}

void authenticateMatches (const std::string& fsearch, const std::string& lsearch, const OnlineDating& odOne, OnlineDating& odResult)
{
	///OnlineDating throwaway (odOne);
	///odJoined.tradeMatches(throwaway);

	odResult = odOne;

	std::string firstNombre;
	std::string lastNombre;
	OnlineType val;

	bool ignoreFirst = (fsearch == "*");
	bool ignoreLast = (lsearch == "*");

	int i = 0;
	while (odOne.confirmMatch(i, firstNombre, lastNombre, val))
	{
		if (ignoreFirst)
		{
			if (ignoreLast)
				return;
			else if (lastNombre != lsearch) //remove if LAST NAMES are different
				odResult.blockPreviousMatch(firstNombre, lastNombre);
			else { } //the same last names
		}
		else
		{
			if (firstNombre != fsearch) //remove if YOU are NOT ignoring and THEY are different
				odResult.blockPreviousMatch(firstNombre, lastNombre);
			else 
			{
				if(ignoreLast) { } //same first, ignore last, NOT remove
				else 
				{
					if(lastNombre != lsearch)
						odResult.blockPreviousMatch(firstNombre, lastNombre);
					else { } //same first name, same last name, NOT remove
				}
			}
		}
		i++;
	}
}
#include "OnlineDating.h"

OnlineDating::OnlineDating()
{
	head = tail = nullptr;
	numMatches = 0;
}

OnlineDating::OnlineDating(const OnlineDating& p)
{
	if (p.head == nullptr) {
		head = tail = nullptr;
		numMatches = 0;
	}
	else {
		Node* iter = p.head;
		Node* curr = new Node();
		curr->firstName = iter->firstName;
		curr->lastName = iter->lastName;
		curr->info = iter->info;
		head = tail = curr;
		iter = iter->next;
		while (iter) {
			curr = new Node();
			curr->firstName = iter->firstName;
			curr->lastName = iter->lastName;
			curr->info = iter->info;
			tail->next = curr;
			curr->prev = tail;
			tail = curr;
			iter = iter->next;
		}
		head->prev = tail->next = nullptr;
		numMatches = p.numMatches;
	}
}

OnlineDating::~OnlineDating()
{
	Node* p = head;
	while (p) {
		Node* q = p->next;
		delete p;
		p = q;
	}
}

OnlineDating& OnlineDating::operator=(const OnlineDating& p)
{
	OnlineDating temp(p);
	Node* m = head;
	while (m) {
		Node* n = m->next;
		delete m;
		m = n;
	}
	if (temp.head == nullptr) {
		head = tail = nullptr;
		numMatches = 0;
	}
	else {
		Node* iter = temp.head;
		Node* curr = new Node();
		curr->firstName = iter->firstName;
		curr->lastName = iter->lastName;
		curr->info = iter->info;
		head = tail = curr;
		iter = iter->next;
		while (iter) {
			curr = new Node();
			curr->firstName = iter->firstName;
			curr->lastName = iter->lastName;
			curr->info = iter->info;
			tail->next = curr;
			curr->prev = tail;
			tail = curr;
			iter = iter->next;
		}
		head->prev = tail->next = nullptr;
		numMatches = temp.numMatches;
	}
	return *this;
}

bool OnlineDating::noMatches() const
{
	if (head)
		return false;
	else
		return true;
}

int OnlineDating::howManyMatches() const
{
	return numMatches;
}

bool OnlineDating::makeMatch(const std::string& firstName, const std::string& lastName, const OnlineType& value)
{
	Node* p = head;
	Node* targetGuest = nullptr;
	bool insertNewHead = false;
	if (p == nullptr) {
		Node* newGuest = new Node();
		newGuest->firstName = firstName;
		newGuest->lastName = lastName;
		newGuest->info = value;
		newGuest->prev = newGuest->next = nullptr;
		head = tail = newGuest;
		++numMatches;
		return true;
	}
	while (p) {
		if (p->lastName == lastName) {
			if (p->firstName == firstName)
				return false;
			else if (p->firstName > firstName) {
				if (p == head)	insertNewHead = true;
				else	targetGuest = p->prev;
				break;
			}
			else if (p->firstName < firstName) {
				if (p->next) {
					if (p->next->firstName > firstName)	{targetGuest = p; break;}
				}
				else	targetGuest = p;
			}
		}
		else if (p->lastName > lastName) {
			if (p == head)	insertNewHead = true;
			else	targetGuest = p->prev;
			break;
		}
		else if (p->lastName < lastName) {
			if (p->next) {
				if (p->next->lastName > lastName)	{targetGuest = p; break;}
			}
			else	targetGuest = p;
		}
		p = p->next;
	}

	Node* newGuest = new Node();
	newGuest->firstName = firstName;
	newGuest->lastName = lastName;
	newGuest->info = value;

	if (insertNewHead) {
		newGuest->next = p;
		newGuest->prev = nullptr;
		p->prev = newGuest;
		head = newGuest;
	}
	else {
		newGuest->next = targetGuest->next;
		newGuest->prev = targetGuest;
		if (targetGuest->next)	targetGuest->next->prev = newGuest;
		else	tail = newGuest;
		targetGuest->next = newGuest;
	}
	++numMatches;
	return true;
}

bool OnlineDating::transformMatch(const std::string &firstName, const std::string &lastName, const OnlineType& value)
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName)	{p->info = value; return true;}
		if (p->lastName > lastName || (p->lastName == lastName && p->firstName > firstName))	break;
		p = p->next;
	}
	return false;
}

bool OnlineDating::makeOrTransform(std::string firstName, std::string lastName, const OnlineType& value)
{
	bool resChange = transformMatch(firstName, lastName, value);
	if (!resChange)	makeMatch(firstName, lastName, value);
	return true;
}

bool OnlineDating::blockPreviousMatch(const std::string& firstName, const std::string& lastName)
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName) {
			if (p == head && p == tail) {
				head = tail = nullptr;
			}
			else if (p == head) {
				head = p->next;
				head->prev = nullptr;
			}
			else if (p == tail) {
				tail = p->prev;
				tail->next = nullptr;
			}
			else {
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
			delete p;
			--numMatches;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool OnlineDating::someoneAmongMatches(const std::string firstName, const std::string lastName) const
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName)	return true;
		if (p->lastName > lastName || (p->lastName == lastName && p->firstName > firstName))	break;
		p = p->next;
	}
	return false;
}

bool OnlineDating::lookAtMatches(const std::string& firstName, const std::string& lastName, OnlineType& value) const
{
	Node* p = head;
	while (p) {
		if (p->firstName == firstName && p->lastName == lastName)	{value = p->info; return true;}
		if (p->lastName > lastName || (p->lastName == lastName && p->firstName > firstName))	break;
		p = p->next;
	}
	return false;
}

bool OnlineDating::confirmMatch(int i, std::string& firstName, std::string& lastName, OnlineType& value) const
{
	if (i >= 0 && i < numMatches) {
		Node* p = head;
		while (i) {
			p = p->next;
			--i;
		}
		firstName = p->firstName;
		lastName = p->lastName;
		value = p->info;
		return true;
	}
	else	return false;
}

void OnlineDating::tradeMatches(OnlineDating& other)
{
	Node* temp = head;
	head = other.head;
	other.head = temp;

	temp = tail;
	tail = other.tail;
	other.tail = temp;

	int howManyMatches = numMatches;
	numMatches = other.numMatches;
	other.numMatches = howManyMatches;
}

bool mergeMatches(const OnlineDating& m1, const OnlineDating& m2, OnlineDating& result)
{
	OnlineDating tempResult(m2);
	bool returnValue = true;
	for (int i = 0; i < m1.howManyMatches(); ++i) {
		std::string firstName, lastName;
		OnlineType value, value_res;
		m1.confirmMatch(i, firstName, lastName, value);
		if (tempResult.lookAtMatches(firstName, lastName, value_res)) {
			if (value_res == value)	continue;
			else	{tempResult.blockPreviousMatch(firstName, lastName); returnValue = false;}
		}
		else	tempResult.makeMatch(firstName, lastName, value);
	}
	result = tempResult;
	return returnValue;
}

void authenticateMatches(const std::string& fsearch, const std::string& lsearch,
            const OnlineDating& p1, OnlineDating& result)
{
	if (fsearch == "*" && lsearch == "*")	{result = p1; return;}
	OnlineDating tempResult;
	if (fsearch == "*") {
		for (int i = 0; i < p1.howManyMatches(); ++i) {
			std::string firstName, lastName;
			OnlineType value;
			p1.confirmMatch(i, firstName, lastName, value);
			if (lastName == lsearch)	tempResult.makeMatch(firstName, lastName, value);
		}
	}
	else if (lsearch == "*") {
		for (int i = 0; i < p1.howManyMatches(); ++i) {
			std::string firstName, lastName;
			OnlineType value;
			p1.confirmMatch(i, firstName, lastName, value);
			if (firstName == fsearch)	tempResult.makeMatch(firstName, lastName, value);
		}
	}
	else {
		OnlineType value;
		if (p1.lookAtMatches(fsearch, lsearch, value))	tempResult.makeMatch(fsearch, lsearch, value);
	}
	result = tempResult;
}

Our specially instrumented class is IntWrapper.

========================== IntWrapper.h

#ifndef INTWRAPPER_INCLUDED
#define INTWRAPPER_INCLUDED

// IntWrapper simply stores and retrieves an int.  However, every
// constructor, the destructor, and the assignment operator report
// when they're called.

class IntWrapper
{
public:
	IntWrapper();
	IntWrapper(int i);
	IntWrapper(const IntWrapper& other);
	~IntWrapper();
	IntWrapper& operator=(const IntWrapper& rhs);
	int value() const;
private:
	int m_value;
};

bool operator==(const IntWrapper& lhs, const IntWrapper& rhs);
bool operator!=(const IntWrapper& lhs, const IntWrapper& rhs);
bool operator< (const IntWrapper& lhs, const IntWrapper& rhs);
bool operator<=(const IntWrapper& lhs, const IntWrapper& rhs);
bool operator> (const IntWrapper& lhs, const IntWrapper& rhs);
bool operator>=(const IntWrapper& lhs, const IntWrapper& rhs);

#endif // INTWRAPPER_INCLUDED

========================== IntWrapper.cpp

#include "IntWrapper.h"
#include <iostream>

using namespace std;

IntWrapper::IntWrapper() : m_value(0)
{
	cerr << "Created 0(" << this << ") (default)" << endl;
}

IntWrapper::IntWrapper(int i) : m_value(i)
{
	cerr << "Created " << m_value << "(" << this << ")" << endl;
}

IntWrapper::IntWrapper(const IntWrapper& other) : m_value(other.m_value)
{
	cerr << "Created " << m_value << "(" << this << ") copied from ("
		<< &other << ")" << endl;
}

IntWrapper::~IntWrapper()
{
	cerr << "Destroyed " << m_value << "(" << this << ")" << endl;
}

IntWrapper& IntWrapper::operator=(const IntWrapper& other)
{
	cerr << "Replaced " << m_value << "(" << this << ") by assigning from "
		<< other.m_value << "(" << &other << ")" << endl;
	m_value = other.m_value;
	return *this;
}

int IntWrapper::value() const
{
	return m_value;
}

bool operator==(const IntWrapper& lhs, const IntWrapper& rhs)
{
	return lhs.value() == rhs.value();
}

bool operator!=(const IntWrapper& lhs, const IntWrapper& rhs)
{
	return lhs.value() != rhs.value();
}

bool operator<(const IntWrapper& lhs, const IntWrapper& rhs)
{
	return lhs.value() < rhs.value();
}

bool operator<=(const IntWrapper& lhs, const IntWrapper& rhs)
{
	return lhs.value() <= rhs.value();
}

bool operator>(const IntWrapper& lhs, const IntWrapper& rhs)
{
	return lhs.value() > rhs.value();
}

bool operator>=(const IntWrapper& lhs, const IntWrapper& rhs)
{
	return lhs.value() >= rhs.value();
}

========================== Sequence.h

#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include "IntWrapper.h"      // TODO: remove this line after testing
typedef IntWrapper ItemType; // TODO: replace this line after testing

class Sequence
{
public:

	etc.

		========================== Sequence.cpp

#include "Sequence.h"

		etc.

		========================== testSequenceMemoryLeak.cpp

#include "Sequence.h"
#include <iostream>
#include <cassert>

		using namespace std;

	void test()
	{
		cerr << "test A" << endl;
		Sequence s;
		cerr << "test B" << endl;
		s.insert(0, IntWrapper(10));
		cerr << "test C" << endl;
		s.insert(0, IntWrapper(20));
		cerr << "test D" << endl;
		Sequence s2;
		cerr << "test E" << endl;
		s2.insert(0, IntWrapper(30));
		cerr << "test F" << endl;
		s2 = s;
		cerr << "test G" << endl;
		s2.insert(0, IntWrapper(40));
		cerr << "test H" << endl;
	}

	int main()
	{
		test();
		cerr << "DONE" << endl;
	}

	==========================

		If building this and executing it produced the output below, then since
		every address that appears in a creation message has a corresponding
		appearance in a destruction message, we know that for this test, at least,
		there were no memory leaks of list nodes.This is by no means a complete
		test, but it gives you an idea of what you can do.

		The following output has been annotated by hand.It so happens that our
		Sequence implementation uses a dummy node; yours need not.

		test A
		Created 0(00322D40) (default)		// dummy node for s's list
		test B
		Created 10(0012FEAC)	// the temporary object produced by IntWrapper(10)
		Created 0(00322DE0) (default)	// the new node created in Sequence::insert
		Replaced 0(00322DE0) by assigning from 10(0012FEAC) // stuffing Sequence::insert's
															// parameter into the new node
		Destroyed 10(0012FEAC)	// after returning from Sequence::insert, destroy the temp
		test C
		Created 20(0012FEA8)			// ditto for IntWrapper(20)
		Created 0(00322DF8) (default)
		Replaced 0(00322DF8) by assigning from 20(0012FEA8)
		Destroyed 20(0012FEA8)
		test D
		Created 0(00322E10) (default)		// dummy node for s2's list
		test E
		Created 30(0012FEA4)
		Created 0(00322E28) (default)
		Replaced 0(00322E28) by assigning from 30(0012FEA4)
		Destroyed 30(0012FEA4)
		test F		// We implemented Sequence::operator= using copy-and-swap
		Created 0(00322E40) (default)		// dummy node for temp list
		Created 0(00322E58) (default)		// copy the two nodes from s
		Replaced 0(00322E58) by assigning from 10(00322DE0)
		Created 0(00322E70) (default)
		Replaced 0(00322E70) by assigning from 20(00322DF8)
		Destroyed 30(00322E28)			// after swap, destroy old list
		Destroyed 0(00322E10)
		test G
		Created 40(0012FEA0)
		Created 0(00322E10) (default)
		Replaced 0(00322E10) by assigning from 40(0012FEA0)
		Destroyed 40(0012FEA0)
		test H
		Destroyed 10(00322E58)			// destroy the nodes in s2
		Destroyed 20(00322E70)
		Destroyed 40(00322E10)
		Destroyed 0(00322E40)
		Destroyed 10(00322DE0)			// destroy the nodes in s
		Destroyed 20(00322DF8)
		Destroyed 0(00322D40)
		DONE
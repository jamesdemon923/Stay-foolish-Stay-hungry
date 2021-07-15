#include "memleak.h"
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
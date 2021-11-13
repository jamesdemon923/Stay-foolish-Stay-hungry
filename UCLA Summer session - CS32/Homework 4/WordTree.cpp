#include "WordTree.h"
#include<string>
using namespace std;

void WordTree::create(WordType v, int number, WordNode*& ptr)
{
	ptr = new WordNode;
	ptr->count = number;
	ptr->m_data = v;
	ptr->m_left = nullptr;
	ptr->m_right = nullptr;
}

void WordTree::copyHelper(WordNode*& change, const WordNode* source)
{
	if (source == nullptr) return;
	create(source->m_data, source->count, change);
	copyHelper(change->m_left, source->m_left);
	copyHelper(change->m_right, source->m_right);
}

// copy constructor
WordTree::WordTree(const WordTree& rhs)
{
	if (rhs.root == nullptr) this->root = nullptr;
	else copyHelper(this->root, rhs.root);
}

// assignment operator
const WordTree& WordTree::operator=(const WordTree& rhs)
{
	if (this != &rhs)
	{
		WordTree temp(rhs);
		WordNode* tempPtr = root;
		root = temp.root;
		temp.root = tempPtr;
		tempPtr = nullptr;
	}
	return *this;
}

void WordTree::addHelper(WordType v, WordNode* ptr)
{
	if (v == ptr->m_data)
	{
		ptr->count++;
	}
	else if (v < ptr->m_data)
	{
		if (ptr->m_left == nullptr) create(v, 1, ptr->m_left);
		else addHelper(v, ptr->m_left);
	}
	else if (v > ptr->m_data)
	{
		if (ptr->m_right == nullptr) create(v, 1, ptr->m_right);
		else addHelper(v, ptr->m_right);
	}
	else cout << "Add something wrong" << endl;
}

// Inserts v into the WordTree
void WordTree::add(WordType v)
{
	//process v
	for (int n = 0; n < v.length(); n++)
	{
		if (v[n] >= 'A' && v[n] <= 'Z') continue;
		else if (v[n] >= 'a' && v[n] <= 'z') continue;
		else if (v[n] >= '0' && v[n] <= '9') return;
		else if (v[n] == '\'') continue;
		else if (v[n] == '-')
		{
			if (n == v.length() - 1)
			{
				add(v.substr(0, n));
			}
			else if (n == 0)
			{
				add(v.substr(n + 2, v.length() - n - 2));
			}
			else
			{
				add(v.substr(0, n));
				add(v.substr(n + 1, v.length() - n - 1));
			}
			return;
		}
		else
		{
			v = v.erase(n);
		}
	}

	for (int i = 0; i < v.length(); i++)
	{
		if (v[i] >= 'A' && v[i] <= 'Z') v[i] = v[i] + 32;
	}

	if (root == nullptr) create(v, 1, root);
	else addHelper(v, root);
}

int WordTree::dWHelper(WordNode* ptr) const
{
	if (ptr == nullptr) return 0;
	return (1 + dWHelper(ptr->m_left) + dWHelper(ptr->m_right));
}

// Returns the number of distinct words / nodes
int WordTree::distinctWords() const
{
	return dWHelper(root);
}

int WordTree::tWHelper(WordNode* ptr) const
{
	if (ptr == nullptr) return 0;
	return (ptr->count + tWHelper(ptr->m_left) + tWHelper(ptr->m_right));
}

// Returns the total number of words inserted, including
// duplicate values
int WordTree::totalWords() const
{
	return tWHelper(root);
}

void WordTree::streamHelper(ostream& output, WordNode* ptr) const
{
	if (ptr == nullptr) return;
	streamHelper(output, ptr->m_left);
	output << ptr->m_data << " " << ptr->count << endl;
	streamHelper(output, ptr->m_right);
	return;
}

// Prints the LinkedList
ostream& operator<<(ostream &out, const WordTree& rhs)
{
	rhs.streamHelper(out, rhs.root);
	return out;
}

void WordTree::clearHelper(WordNode* node)
{
	if (node == nullptr) return;
	clearHelper(node->m_left);
	clearHelper(node->m_right);
	delete node;
}

// Destroys all the dynamically allocated memory in the
// tree
WordTree::~WordTree()
{
	clearHelper(root);
}
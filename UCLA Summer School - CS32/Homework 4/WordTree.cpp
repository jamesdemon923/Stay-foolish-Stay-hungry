#include "WordTree.h"
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
		//swapWordTree(temp);
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
		ptr->count = ptr->count + 1;
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
	else cout << "Error" << endl;

}

// Inserts v into the WordTree
void WordTree::add(WordType v)
{
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
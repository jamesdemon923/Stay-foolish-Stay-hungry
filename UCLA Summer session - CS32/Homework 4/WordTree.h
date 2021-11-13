#ifndef WORDTREE_H
#define WORDTREE_H

#include <iostream>
#include <string>

typedef std::string WordType;

struct WordNode {
	WordType m_data;
	WordNode *m_left;
	WordNode *m_right;
	// You may add additional data members and member functions
	// in WordNode
	int count;
};

class WordTree {
private:
	WordNode *root;
	void create(WordType v, int number, WordNode*& ptr);
	void copyHelper(WordNode*& change, const WordNode* source);
	void addHelper(WordType v, WordNode* ptr);
	int dWHelper(WordNode* ptr) const;
	int tWHelper(WordNode* ptr) const;
	void streamHelper(std::ostream& output, WordNode* ptr) const;
	void clearHelper(WordNode* node);

public:
	// default constructor
	WordTree() : root(nullptr) { };

	// copy constructor
	WordTree(const WordTree& rhs);

	// assignment operator
	const WordTree& operator=(const WordTree& rhs);

	// Inserts v into the WordTree
	void add(WordType v);

	// Returns the number of distinct words / nodes
	int distinctWords() const;

	// Returns the total number of words inserted, including
	// duplicate values
	int totalWords() const;

	// Prints the LinkedList
	friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs);

	// Destroys all the dynamically allocated memory in the
	// tree
	~WordTree();
};

#endif
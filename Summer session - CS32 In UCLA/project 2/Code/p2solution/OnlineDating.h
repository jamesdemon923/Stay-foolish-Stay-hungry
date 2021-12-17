#ifndef ONLINEDATING_H
#define ONLINEDATING_H

#include <string>

typedef std::string OnlineType;

class OnlineDating
{
  public:
    OnlineDating();          // Create an empty In (i.e., one with no OnlineType values)

    OnlineDating(const OnlineDating& p);

    ~OnlineDating();

    OnlineDating& operator=(const OnlineDating& p);

    bool noMatches() const;    // Return true if the list is empty, otherwise false.

    int howManyMatches() const;      // Return the number of elements in the linked list.

    bool makeMatch(const std::string& firstName, const std::string& lastName, const OnlineType& value);
      // If the full name (both the first and last name) is not equal to any full name currently
      // in the list then add it and return true. Elements should be added according to
      // their last name. Elements with the same last name should be added according to
      // their first names. Otherwise, make no change to the list and return false
      // (indicating that the name is already in the list).

    bool transformMatch(const std::string &firstName, const std::string &lastName, const OnlineType& value);
      // If the full name is equal to a full name currently in the list, then make that full
      // name no longer map to the value it currently maps to, but instead map to
      // the value of the third parameter; return true in this case.
      // Otherwise, make no change to the list and return false.

    bool makeOrTransform(std::string firstName, std::string lastName, const OnlineType& value);
      // If full name is equal to a name currently in the list, then make that full name no
      // longer map to the value it currently maps to, but instead map to
      // the value of the third parameter; return true in this case.
      // If the full name is not equal to any full name currently in the list then add it
      // and return true. In fact this function always returns true.

    bool blockPreviousMatch(const std::string& firstName, const std::string& lastName);
      // If the full name is equal to a full name currently in the list, remove the
      // full name and value from the list and return true.  Otherwise, make
      // no change to the list and return false.

    bool someoneAmongMatches(const std::string firstName, const std::string lastName) const;
      // Return true if the full name is equal to a full name currently in the list, otherwise
      // false.

    bool lookAtMatches(const std::string& firstName, const std::string& lastName, OnlineType& value) const;
      // If the full name is equal to a full name currently in the list, set value to the
      // value in the list that that full name maps to, and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.

    bool confirmMatch(int i, std::string& firstName, std::string& lastName, OnlineType& value) const;
      // If 0 <= i < size(), copy into firstName, lastName and value parameters the
      // corresponding information of the element at position i in the list and return
      // true.  Otherwise, leave the parameters unchanged and return false.
      // (See below for details about this function.)

    void tradeMatches(OnlineDating& other);
      // Exchange the contents of this list with the other one.

  private:
    struct Node {
      std::string firstName;
      std::string lastName;
      OnlineType info;
      Node* prev;
      Node* next;
    };
    Node* head;
    Node* tail;
    int numMatches;
};

bool mergeMatches(const OnlineDating& m1, const OnlineDating& m2, OnlineDating& result);

void authenticateMatches(const std::string& fsearch, const std::string& lsearch,
                 const OnlineDating& p1, OnlineDating& result);

#endif // ONLINEDATING_H
# Project 2 - Doubly-Linked OnlineDating

**Project Description**

OnlineDating is a doubly-linked list without a tail pointer. It was implemented as a *doubly*-linked list in order to fulfill the requirements, but technically it seems that there is no reason for previous nodes because we never make use of backwards traversal; the only time this was useful was for printing the list backwards for debugging in order to check to see that the previous pointers were working correctly.

A linked list was the best implementation for a data due to the fact that there would be a lot of insertions and deletions of elements. And the primary focus of a “OnlineDating” is to keep track of *changes*.

Of note, my list does not make use of a dummy node. Each data node contains: a data of type SomeType, a firstName string, a lastName string, and pointers to the next and previous Nodes in the list.

**Difficulties Encountered**

I tend to tackle projects holistically, so I like to think of all possible routes and think of an all-in-one solution that handles it everything. So, for methods like makeMatch() and blockPreviousMatch(), this proved to be an issue because adding to the front and adding to the back (same for removal) presents cases that specifically need to be accounted for uniquely, not conforming to the ideal “base case” code.

makeMatch() gave me the most trouble, since I ran into a lot of pointer issues. As mentioned before, anything that had to do with adding to the front or back would conflict with the main loop that I tried to use to handle all cases. Especially with a doubly-linked list, the empty case is also interesting since both previous and next need to be set to nullptr with NO traversal. The alphabetization mixed with edge cases presented issues as seen in my galore of if-else complexes, since reaching the end doesn’t necessarily mean that it will be added there, as I learned the hard way.

**Nontrivial Algorithm Pseudocode**

1. makeMatch()

Description: If the full name (both the first and last name) is not equal to any full name currently in the list then add it and return true. Elements should be added according to their last name. Elements with the same last name should be added according to their first names. Otherwise, make no change to the list and return false (indicating that the name is already in the list).

Approach:

    Loop through list until you hit a) {equal-to}... b) {current-is-greater than}... c) {end of the list} based on LASTNAME

        a) if you find an identical lastname, then check firstname
            if
                i) BOTH LAST AND FIRSTNAME ARE THE SAME --> RETURN FALSE
                ii) Same lastname, different firstname, where the "current" node is AFTER your to-add
                        - add new PRECEDING current
                iii) seemse we cannot escape from checking for the end!!!
        b) if your current node is greater than your toAdd, then add it PRECEDING CURRENT
        c) if you reach end of the list, then add it to the end

    Note that since this is being done "previous-node-based", there needs to be a check for the specific case of "previous" being nullptr: adding to the front!

2. blockPreviousMatch()

Description: If the full name is equal to a full name currently in the list, remove the full name and value from the list and return true. Otherwise, make no change to the list and return false.

Approach:

    3 cases for removal:
    1) front:
            - head points to p->next
            - p->next->prev = nullptr;
            - delete p
    2) middle:
            - p->prev->next = p->next;
            - p->next->prev = p->prev;
            - delete p
    3) end:
            - p->prev->next = nullptr;
            - delete p

3. mergeMatches()

Approach:

    1) Somehow destruct the other list
        IDEA: 
            a) create a new list, which will be empty
            b) swap it with odJoined
            c) your odJoined is now empty, and since the scope of the new list is
                inside this bracket, it'll get destroyed on exit!
    2) copy-construct the first list 
    NEW BIG IDEA: copy construct the first list, swap, then it'll destroy the second list when it's done
    2) cleaner BIG IDEA: just use assignment operator to deal with aliasing!!!
    3) start running through each node in the second list
    3)	- if you cannot add it to odJoined, which is a copy of odOne, then this means
        that there is a duplicate name 
    4)		-- if there is a duplicate name, then further check the data
    4)			--- if they are equal, then do nothing and move on
    4)			--- if they are not equal, call delete on that name!
    *** The idea is that the methods already work so that by the time everything is added it will already be alphabetical

    Weird shenanigans
    - both One and Two are the same list
        -- odJoined will be a simple copy
    - joined is either One or Two
        -- seems to work fine with current methodology
            -- perhaps not though... once you swap odJoined with throwaway, throwaway now has a head pointing to od1 itself which will be deleted!
    - all three arguments are the same
        -- seems to work fine

**Testing Methodology**

This is one of the few labs in which I took veteran advice to write test cases before writing code. This allowed me to have edge and exception cases at the back of my mind and most importantly, written down to be eventually satisfied. The function myTests() in main.cpp was self-written and called as a part of main() along with the other spec-noted test cases. It thoroughly addressed all possible cases I could think of, including but not limited to: adding to the front, adding between nodes, adding based on first vs. last name priority, checking dates based on wildcards with different first and last name combos, and operating on nodes that did and did not exist.

Since this lab dependly heavily on creation and destruction of nodes, I also made sure to run a couple basic test cases using the "memleak" files. This was provided as part of the project specification, but few students chose to utilize it since it was not completely obvious what it accomplished. Rather than simply reveal whether the code exhibited memork leaks, the "memleak" code defined an object that printed a message in the constructor(s) and destructor. So, if each construction message had a corresponding destruction message (same ID), then the code would be memleak-free. Tedious to integrate and subsequently analyze, but worth it!

**Description of Files**

Onlinedating.h

Onlinedating.cpp

- My solution code to implement a doubly-linked list to keep track of of a Online date.

main.cpp

- Driver code to thoroughly test my solution, including both self-created and spec-defined test cases.

memleak.h

memleak.cpp

memleak_test.cpp

- Code as mentioned in *Testing Methodology* to test for memory leaks.
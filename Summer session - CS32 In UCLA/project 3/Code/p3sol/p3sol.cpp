//
//  main.cpp
//  AnagramRecursion
//
//  Created by Edwin Ambrosio on 7/27/20.
//  Copyright (c) 2020 Edwin Ambrosio. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


// Functions for reading in dictionary
int makeDictionary(istream &dictfile, string dict[]);

int makeDictionary_aux(istream &dictfile, string dict[], int i);


// Functions for finding permutations
int shuffleChars(string word, const string dict[], int a, string results[]);

void RecFor(const string dict[], const int dictSize, string pre, string post,  int i, int size, string results[], int& nwords);

void shuffleChars_aux(const string dict[], const int dictSize, string pre, string post,  string results[], int& numResults);

// Functions for printing results
void revealOutcomes(const string results[], int);

void revealOutcomes_aux(const string results[], int, int);


int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = makeDictionary(dictfile, dict);

    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = shuffleChars(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        revealOutcomes(results, numMatches);

    return 0;
}

int makeDictionary(istream &dictfile, string dict[]) {

    return makeDictionary_aux(dictfile, dict, 0);
}

int makeDictionary_aux(istream &dictfile, string dict[], int i) {

    if (i >= MAXDICTWORDS)
        return i;
    if (dictfile >> dict[i])
        return makeDictionary_aux(dictfile, dict, i+1);
    return i;
}

void revealOutcomes(const string results[], int numMatches) {
    revealOutcomes_aux(results, numMatches, 0);
}

void revealOutcomes_aux(const string results[], int numMatches, int i) {

    if (i >= MAXRESULTS || i >= numMatches)
        return;
    cout << results[i] << endl;
    revealOutcomes_aux(results, numMatches, i+1);
}


int shuffleChars(string word, const string dict[], int dictSize,
                     string results[]) {

    int nwords=0;  // not necessary but makes counting found permutations easier
    shuffleChars_aux(dict, dictSize, string(""), word, results, nwords);
    return nwords;
}

// Places the string s into results, returns the newly placed string's position
// Returns -1 if it's already in the array or if array is full
int insertloop (string results[], string s, int i) {

    if (i == MAXRESULTS)
        return -1;
    if (results[i] == "") {
        results[i] = s;
        return i;
    }
    if (results[i] == s)
        return -1;
    return insertloop(results, s, i+1);
}

// returns true if word is in dict
bool isInDictionary(const string dict[], int size, string word, int i) {

    if (i >= size)
        return false;
    if (dict[i] == word)
        return true;
    return isInDictionary(dict, size, word, i+1);
}

void shuffleChars_aux(const string dict[], const int dictSize, string pre, string post,  string results[], int& nwords)
{
    if (post == "") {       // if post is empty pre is a permutation
        string permutation = pre;
        if (!isInDictionary(dict, dictSize, permutation, 0))
            return;
        int lastInsertPos = insertloop(results, permutation, 0); // insert permutation in dictionary
        if (lastInsertPos == -1) {
            return;
        }
        nwords = lastInsertPos+1;
        return;
    }
    // loop through characters in post, in otherwords, iterates post.size() number of times
    RecFor(dict, dictSize, pre, post, 0, (int) post.size(), results, nwords);
}

void RecFor(const string dict[], const int dictSize, string pre, string post, int i, int size, string results[], int& nwords) {
    if (i == size) {
        return;
    }
    // Example:
    //    if i = 3, pre is "" and post is "example" before call to shuffleChars_aux
    //    below, then the following would be made to generate all the permutations that
    //    start with the letter m.
    //
    //    shuffleChars_aux (dict, dictSize, "m", "exaple", results, nwords);

    shuffleChars_aux(dict, dictSize, pre + post[i], post.substr(0,i) + post.substr(i+1),  results, nwords);
    RecFor(dict, dictSize, pre, post, i+1, size, results, nwords);
}
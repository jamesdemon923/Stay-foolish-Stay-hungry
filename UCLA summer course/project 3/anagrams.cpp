#include <iostream>
#include <fstream>
#include <istream>
#include <string>

using namespace std;

const int MAXRESULTS = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


int mD(istream& dictfile, string dict[], int& ret)
{
	// if "ret", which is the recurse-count, is equal to the maxsize, then don't proceed!
	if (ret >= MAXDICTWORDS)
		return ret;
	// if we reach the end of the file/stream
	if ((dictfile >> dict[0]).eof())
	{
		///cerr << "mD " << dict[0] << endl;
		return (++ret);	//this actually stops one before the end so this passing means that you've added something					
	}
	//recurse with incremented return value!
	///cerr << "mD " << dict[0] << endl;
	return mD(dictfile, dict + 1, ++ret);
}

int makeDictionary(istream &dictfile, string dict[])
//Puts each string in dictfile into the array dict.  
//Returns the number of words read into dict.  
//This number should not be larger than MAXDICTWORDS since that is the size of the array
{
	int returnMe = 0;
	return mD(dictfile, dict, returnMe);
}


//-------------------------------------------------------------------------------------

//This area of code handles summing the ascii values of a string, recursively

bool doesNotContainWord(const string res[], const int& size, const string& dictWord)
{
	if (size == 0)
		return true;
	if (dictWord == res[0])
		return false;
	return doesNotContainWord(res + 1, size - 1, dictWord);
}

//-------------------------------------------------------------------------------------

//This area of code handles summing the ascii values of a string, recursively

//UPDATE: MIGHT be axed because it is superceded by a better method below!

int ascii(const string& sumMe)
{
	if (sumMe.size() == 1)
		return sumMe.at(0);
	return (sumMe.at(0) + ascii(sumMe.substr(1)) );
}

//-------------------------------------------------------------------------------------

//This area of code handles the secondary letter-checking

bool isAnagram(const string& word, string dictionaryWord, const int& index)
{
	if (index == word.size())
		return true;
	if (dictionaryWord.find(word.at(index)) != string::npos)
		return isAnagram(word, dictionaryWord.erase(dictionaryWord.find(word.at(index)), 1), index + 1);
	else
		return false;
}

//-------------------------------------------------------------------------------------

//This area of code handles going through the dictionary

// tracker MUST BE RESET TO FALSE EVERY NEW DICTIONARY INDEX

int sC(const string& word, const string dict[], const int& size, string results[], int& ret)
{
	///cerr << "sC " << dict[0] << endl;
	//return the number of added elements if:
	//- ret equals or exceeds the MAX array size
	//- size is equal to or less than 0: the dictionary has depleted!
	if ( ( ret >= MAXRESULTS ) || ( size <= 0 ) )
		return ret;
	// KEY TO OPTIMIZATION:
	//ONLY do the big-boi recursive check if:
	//- the lengths are the same (first check)
	//- a secondary check that is aimed at longer words is checking to see
	//every letter in word appears at least once in dict[0]
	//- the ascii sum of the chars is the same (VERY good contender)
	//-- POSSIBLY axe because the secondary check handles this much better!
	//- last check to make sure the word isn't already in results!
	if ( ( dict[0].size() == word.size() ) && ( ascii(word) == ascii(dict[0]) )  && ( doesNotContainWord(results, ret, dict[0]) ) && ( isAnagram(word, dict[0], 0) ) )
	{
		///cerr << "sC " << dict[0] << endl;
		results[ret++] = dict[0];
	}
	//adding to results and changing ret is delegated to pH!!!
	//ALL we must do here is recursively go through the dictionary
	return sC(word, dict + 1, size - 1, results, ret);
}

//------------------------------------------------------------------------------------

//This area of code is just really the public interface... If I figured out how to
//find the size of the passed array's, then perhaps there is a way to put everything
//from sC into shuffleChars, but otherwise you have to abstract it over into the other
//method as I have already done, just like with makeDictionary!!!

int shuffleChars(string word, const string dict[], int size, string results[])
//Puts all the possibilities of word which are found in dict into results. 
//Returns the number of matched words found. This number should not be larger than 
//MAXRESULTS since that is the size of the array. 
//The size is the number of words inside the dict array.
{
	int returnMe = 0;
	return sC(word, dict, size, results, returnMe);
}


//------------------------------------------------------------------------------------

void revealOutcomes(const string results[], int size)
//Displays size number of strings from results. The results can be printed in any order.
{
	///safety checks
	//if size is <= 0 ???
	//DO WE NEED A TRIGGER WHERE SIZE IS > RESULTS'S ACTUAL SIZE???
	
	if (size <= 0)
		return;
	else
	{
		cout << results[0] << endl;
		revealOutcomes(results + 1, size - 1);
	}
}




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
	///cerr << nwords << endl;

	cout << "Please enter a string for an anagram: ";
	cin >> word;

	int numMatches = shuffleChars(word, dict, nwords, results);
	///cerr << numMatches << endl;

	///cerr << "[DEBUG] " << dict[0] << endl;
	///cerr << "[DEBUG] " << ( dict[0].compare("10th") == 0 ) << endl;

	if (!numMatches)
		cout << "No matches found" << endl;
	else
		revealOutcomes(results, numMatches);
}
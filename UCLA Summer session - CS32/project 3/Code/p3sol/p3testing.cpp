#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

void testone(int n)
{
    string dictionary[MAXDICTWORDS];
    string results[MAXRESULTS]

    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case 1: {
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = makeDictionary(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 9 && dictionary[0] == "act" && dictionary[1] == "art");
        } break; case 2: {
            // File is empty, checks that file is empty and makeDictionary returns 0.
            istringstream iss("");
            int numResults = makeDictionary(iss, dictionary);
            assert(numResults == 0 && dictionary[0] == "");
        } break; case 3: {
            // Dictionary has been read properly
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = makeDictionary(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 9 && dictionary[0] == "act" && dictionary[numResults-1] == "tar");
        } break; case 4: {
            // Input file is larger than the dictionary size
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\ntoo\nmany\nwords");
            int numResults = makeDictionary(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 10 && dictionary[MAXDICTWORDS-1] == "too");
        } break; case 5: {
            // If a certain word with repeated letter is shown in results more than once - still accept.
            string dictionary[] = { "one", "oone", "ne", "e", "too" };
            int numResults = shuffleChars("oto", dictionary, 5, results);
            assert((numResults == 1 || numResults == 2) && results[0] == "too");
        } break; case 6: {
            // Doesn't check numResults nor duplicates.
            string dictionary[] = { "one", "oone", "ne", "e", "too" };
            shuffleChars("oto", dictionary, 5, results);
            assert(results[0] == "too");
        } break; case 7: {
            // If word wasn't found, numResults = 0 and results array is empty.
            string dictionary[] = { "one", "oone", "ne", "e" };
            int numResults = shuffleChars("look", dictionary, 4, results);
            assert(numResults == 0 && results[0] == "" && results[1] == "");
        } break; case 8: {
            // No fraction of a permutation is being searched in dictionary
            string dictionary[] = { "one", "oone", "non", "oon" };
            int numResults = shuffleChars("on", dictionary, 4, results);
            assert(numResults == 0 && results[0] == "" && results[1] == "");
        } break; case 9: {
            // No fraction of a permutation is being searched in dictionary
            string dictionary[] = { "one", "oone", "ne", "e", "neoo", "oneo" };
            int numResults = shuffleChars("neo", dictionary, 6, results);
            assert(numResults == 1 && results[0] == "one" && results[1] == "");
        } break; case 10: {
            // Checking that no error occurs if more than MAXRESULTS are found.
            string dictionary[] = { "true",  "treu", "teru", "teur", "ture",
		"tuer", "rtue", "rteu", "retu","reut", "ruet", "rute", "utre",
		"uter", "uetr", "uert", "urte", "uret", "etru", "etur", "ertu",
		"erut", "eurt", "eutr" };
            // All 24 permutations
            int numResults = shuffleChars("true", dictionary, 24, results);
            assert(numResults == MAXRESULTS);
        } break; case 11: {
            // Checking one word was found, no duplicates.
            string dictionary[] = { "ppp" };
            int numResults = shuffleChars("ppp", dictionary, 1, results);
            assert(numResults == 1 && results[0] == "ppp" && results[1] == "");
        } break; case 12: {
            string dictionary[] = { "run", "dodge", "break", "urn", "defeat" };
            int numResults = shuffleChars("nru", dictionary, 5, results);
            sort(results, results + numResults);
            assert(numResults == 2 && results[0] == "run" && results[1] == "urn");
        } break; case 13: {
            streambuf* oldCoutStreamBuf = cout.rdbuf();
            ostringstream strCout;
            cout.rdbuf(strCout.rdbuf());
            string results[] = { "cat", "act"};
            revealOutcomes(results, 2);
            cout.rdbuf(oldCoutStreamBuf);
            string temp = strCout.str();
            bool match1 = temp.find("act") != string::npos;
            bool match2 = temp.find("cat") != string::npos;
            assert(match1 && match2);
        } break; case 14: {
            istringstream iss ("tier\nrite\nbate\ntire\nttir");
            int numWords = makeDictionary(iss, dictionary);
            sort(dictionary, dictionary + numWords);
            assert(numWords == 5 && dictionary[0] == "bate");
            int numResults = shuffleChars("tier", dictionary, numWords, results);
            assert(numResults == 3 && (results[2] == "tire" || results[2] == "tier" || results[2] == "rite"));
        } break; case 15: {
            string example[] = { "kool", "moe", "dee" };
            int numResults = shuffleChars("look", example, 3, results);
            assert(numResults == 1 && results[0] == "kool");
        } break;
    }
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout << "Passed" << endl;
}

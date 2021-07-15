#include "OnlineDating.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void myTests()
{
	OnlineDating a;

	//Check empty status
	assert(a.noMatches() == true);
	assert(a.howManyMatches() == 0);
	assert(a.someoneAmongMatches("James", "Xu") == false);
	string placeholder = "-1";
	string s1 = "Hi";
	string s2 = "Hello";
	assert(a.lookA5Matches("James", "Xu", placeholder) == false);
	assert(a.confirmMatch(-1, s1, s2, placeholder) == false);
	assert(s1 == "Hi");
	assert(s2 == "Hello");

	//the next 4 test sets focus on adding by last name
	
	//adding one person named "AAA BBB" with value "2"
	assert(a.makeOrTransform("AAA", "BBB", "2") == true);
	assert(a.noMatches() == false);
	assert(a.howManyMatches() == 1);
	assert(a.someoneAmongMatches("AAA", "BBB") == true);

	//adding a second person named "BBB AAA" with value "1"
	//this specifically tests for "adding at front"
	assert(a.makeOrTransform("BBB", "AAA", "1") == true);
	assert(a.noMatches() == false);
	assert(a.howManyMatches() == 2);
	assert(a.someoneAmongMatches("BBB", "AAA") == true);

	//adding a third person named "AAA DDD" with value "4"
	//this specifically tests for "adding at rear"
	assert(a.makeOrTransform("AAA", "DDD", "4") == true);
	assert(a.noMatches() == false);
	assert(a.howManyMatches() == 3);
	assert(a.someoneAmongMatches("AAA", "DDD") == true);

	//adding a fourth person named "BBB CCC" with value "3"
	//this specifically tests for "adding between two established nodes"
	assert(a.makeOrTransform("BBB", "CCC", "3") == true);
	assert(a.noMatches() == false);
	assert(a.howManyMatches() == 4);
	assert(a.someoneAmongMatches("BBB", "CCC") == true);

	a.dump();

	// need to run same last-name tests

	//adding a fifth person named "AAA AAA" with value "0"
	//this specifically tests for "adding at start based on FIRST name
	assert(a.makeOrTransform("AAA", "AAA", "0") == true);
	assert(a.noMatches() == false);
	assert(a.howManyMatches() == 5);
	assert(a.someoneAmongMatches("AAA", "AAA") == true);

	//adding a sixth person named "CCC AAA" with value "11"
	//this specifically tests for "adding at start based on FIRST name
	assert(a.makeOrTransform("CCC", "AAA", "11") == true);
	assert(a.noMatches() == false);
	assert(a.howManyMatches() == 6);
	assert(a.someoneAmongMatches("CCC", "AAA") == true);

	//adding a seventh person named "AAA CCC" with value "33"
	//this specifically tests for "adding at start based on FIRST name
	assert(a.makeOrTransform("AAA", "CCC", "33") == true);
	assert(a.noMatches() == false);
	assert(a.howManyMatches() == 7);
	assert(a.someoneAmongMatches("AAA", "CCC") == true);
	
	a.dump();
	

	string setMe = "-1";

	// lookA5Matches

	assert(a.lookA5Matches("James", "Xu", setMe) == false);
	assert(setMe == "-1");
	assert(a.lookA5Matches("AAA", "AAA", setMe) == true);
	assert(setMe == "0");
	assert(a.lookA5Matches("CCC", "AAA", setMe) == true);
	assert(setMe == "11");
	assert(a.lookA5Matches("AAA", "DDD", setMe) == true);
	assert(setMe == "4");


	// confirmMatch
	string s3 = "Hep";
	string s4 = "Me";
	assert(a.confirmMatch(-1, s3, s4, setMe) == false);
	assert(s3 == "Hep");
	assert(s4 == "Me");
    assert(setMe == "4"); //4 = last value from last test set
	assert(a.confirmMatch(0, s3, s4, setMe) == true);
	assert(s3 == "AAA");
	assert(s4 == "AAA");
	assert(setMe == "0");
	assert(a.confirmMatch(5, s3, s4, setMe) == true);
	assert(s3 == "BBB");
	assert(s4 == "CCC");
	assert(setMe == "3");
	assert(a.confirmMatch(6, s3, s4, setMe) == true);
	assert(s3 == "AAA");
	assert(s4 == "DDD");
	assert(setMe == "4");
	assert(a.confirmMatch(7, s3, s4, setMe) == false);
	assert(s3 == "AAA");
	assert(s4 == "DDD");
	assert(setMe == "4");


	//transformMatch

	assert(a.transformMatch("James", "Xu", "5") == false);
	assert(a.transformMatch("AAA", "AAA", "100") == true);
	assert(a.lookA5Matches("AAA", "AAA", setMe) == true);
	assert(setMe == "100");
	assert(a.transformMatch("AAA", "CCC", "200") == true);
	assert(a.lookA5Matches("AAA", "CCC", setMe) == true);
	assert(setMe == "200");
	assert(a.transformMatch("AAA", "DDD", "300") == true);
	assert(a.lookA5Matches("AAA", "DDD", setMe) == true);
	assert(setMe == "300");


	//makeOrTransform

	//making case
	assert(a.makeOrTransform("DDD", "DDD", "999") == true);
	assert(a.howManyMatches() == 8);

	//Transforming case

	assert(a.makeOrTransform("DDD", "DDD", "99") == true);
	assert(a.howManyMatches() == 8);

	a.dump();

	
	//blockPreviousMatch

	assert(a.blockPreviousMatch("James", "Xu") == false);
	assert(a.blockPreviousMatch("AAA", "AAA") == true);
	assert(a.someoneAmongMatches("AAA", "AAA") == false);
	assert(a.howManyMatches() == 7);
	assert(a.blockPreviousMatch("AAA", "CCC") == true);
	assert(a.someoneAmongMatches("AAA", "CCC") == false);
	assert(a.howManyMatches() == 6);
	assert(a.blockPreviousMatch("DDD", "DDD") == true);
	assert(a.someoneAmongMatches("DDD", "DDD") == false);
	assert(a.howManyMatches() == 5);

	a.dump();


	//copy constructor test
	cerr << "Now for a COPY to be made and printed!" << endl;
	OnlineDating b(a);
	b.dump();

	//authenticateMatches

	OnlineDating exactName;
	OnlineDating starLast;
	OnlineDating firstStar;
	OnlineDating starStar;

	authenticateMatches("BBB", "AAA", b, exactName);
	cerr << "authenticateMatches for an exact match" << endl;
	exactName.dump();
	cerr << "This should read:" << endl;
	cerr << "BBB AAA 1" << endl;

	authenticateMatches("*", "AAA", b, starLast);
	cerr << "authenticateMatches for a star, then a last name" << endl;
	starLast.dump();
	cerr << "This should read:" << endl;
	cerr << "BBB AAA 1" << endl;
	cerr << "BBB CCC 11" << endl;

	authenticateMatches("AAA", "*", b, firstStar);
	cerr << "authenticateMatches for first name, then a star" << endl;
	firstStar.dump();
	cerr << "This should read:" << endl;
	cerr << "AAA BBB 2" << endl;
	cerr << "AAA DDD 300" << endl;

	authenticateMatches("*", "*", b, starStar);
	cerr << "authenticateMatches for both stars" << endl;
	starStar.dump();
	cerr << "This should read:" << endl;
	cerr << "BBB AAA 1" << endl;
	cerr << "CCC AAA 11" << endl;
	cerr << "AAA BBB 2" << endl;
	cerr << "BBB CCC 3" << endl;
	cerr << "AAA DDD 300" << endl;


	//mergeMatches
	///moved to another tet case

	cerr << endl << endl;
}

void test1()
{
	OnlineDating lakers;
	lakers.makeMatch("LeBron", "James", "6");
	lakers.makeMatch("Anthony", "Davis", "3");
	lakers.makeMatch("Kyle", "Kuzma", "0");
	lakers.makeMatch("Boogie", "Cousins", "15");
	lakers.makeMatch("Rajon", "Rondo", "8");
	for (int n = 0; n < lakers.howManyMatches(); n++)
	{
		string first;
		string last;
		string val;
		lakers.confirmMatch(n, first, last, val);
		cerr << first << " " << last << " " << val << endl;
	}

	cerr << endl << "This should read:" << endl;
	cerr << "Boogie Cousins 15" << endl;
	cerr << "Anthony Davis 3" << endl;
	cerr << "LeBron James 6" << endl;
	cerr << "Kyle Kuzma 0" << endl;
	cerr << "Rajon Rondo 8" << endl;

	cerr << endl << "Test 1 complete" << endl << endl;
}

void test2()
{
	OnlineDating clippers;

	clippers.makeMatch("Tyrone", "Wallace", "-1");
	assert(!clippers.someoneAmongMatches("", ""));
	clippers.makeMatch("Kawhi", "Leonard", "-1");
	clippers.makeMatch("", "", "-1");
	clippers.makeMatch("Paul", "George", "-1");
	assert(clippers.someoneAmongMatches("", ""));
	clippers.blockPreviousMatch("Tyrone", "Wallace");
	assert(clippers.howManyMatches() == 3 && clippers.someoneAmongMatches("Kawhi", "Leonard") && clippers.someoneAmongMatches("Paul", "George") && clippers.someoneAmongMatches("", ""));

	cerr << endl << "Test 2 complete" << endl << endl;
}

void test3()
{
	OnlineDating x;
	
	assert(x.makeMatch("Kevin", "Durant", "7"));
	assert(x.makeMatch("Kyrie", "Irving", "11"));
	assert(x.makeMatch("DeAndre", "Jordan", "6"));

	OnlineDating y;

	assert(y.makeMatch("Spencer", "Dinwiddie", "8"));
	assert(y.makeMatch("Kevin", "Durant", "7"));

	OnlineDating z;

	assert(mergeMatches(x, y, z) == true);
	z.dump();
	cerr << "This should read:" << endl;
	cerr << "Spencer Dinwiddie 8" << endl;
	cerr << "Kevin Durant 7" << endl;
	cerr << "Kyrie Irving 11" << endl;
	cerr << "DeAndre Jordan 6" << endl << endl;


	OnlineDating r;

	assert(r.makeMatch("Spencer", "Dinwiddie", "8"));
	assert(r.makeMatch("Kevin", "Durant", "35"));

	assert(mergeMatches(x, r, z) == false);
	z.dump();
	cerr << "This should read:" << endl;
	cerr << "Spencer Dinwiddie 8" << endl;
	cerr << "Kyrie Irving 11" << endl;
	cerr << "DeAndre Jordan 6" << endl << endl;


	cerr << endl << "mergeMatches complete" << endl << endl;
}


int main()
{
	myTests(); //memleak is its own file because of fileType
	test1();
	test2();
	test3();

	//test same-list cases
	///gonna assume this works since he basically gave the answer of using assignment operator

	cerr << "Remove DEBUGGING CODE. And input your CODE" << endl << endl;
}

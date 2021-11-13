#include <cassert>
#include <iostream> 
#include <string>
using namespace std;

// Returns the product of two non-negative integers, m and n,
// using only repeated addition.
int mTimesN(unsigned int m, unsigned int n)
{
	if (n == 0)
		return 0;
	return m + mTimesN(m, n - 1);
}


// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
// tallyTheDigits(18838, 8) => 3
// tallyTheDigits(55555, 3) => 0
// tallyTheDigits(0, 0) => 0 or 1 (either if fine)
//
int tallyTheDigits(int num, int digit)
{
	if (num == 0)
		return 0;
	else if (num % 10 == digit)
		return 1 + tallyTheDigits(num / 10, digit);
	else
		return tallyTheDigits(num / 10, digit);
}


// Returns a string where the same characters next each other in
// string n are separated by "44" (you can assume the input 
// string will not have 4¡¯s)
//
// Pseudocode Example:
// foursUp("goodbye") => "go44odbye"
// foursUp("yyuu") => "y44yu44u"
// foursUp("aaaa") => "a44a44a44a"
//
string foursUp(string n)
//Approach:
//process the string starting from the front:
//if the front letter is the same as the "next" letter, then recurse but also appent "44".
//the base case is when you react the end, with size == 1, which then you return because it's impossible to check a next!
//BOTH the 0 and 1 cases are end cases;
//	- with a passed empty string, should just return the empty string
//	- with a passed 1+ string, return the char
{
	if (n.size() == 0 || n.size() == 1)
		return n;
	//if you even get to this point, this means there are AT LEAST 2 chars in the string
	else if (n.substr(0, 1) == n.substr(1, 1))
		return (n.substr(0, 1) + "44" + foursUp(n.substr(1, n.size() - 1)));
	//so, this means that the first and second letters aren't the same, just return the first letter and keep processing the string!
	else return (n.substr(0, 1) + foursUp(n.substr(1, n.size() - 1)));
}


// str contains a single pair of parentheses, return a new
// string made of only the parentheses and whatever those
// parentheses contain
//
// Pseudocode Example:
// parentheticallySpeaking("abc(ghj)789") => "(ghj)"
// parentheticallySpeaking("(x)7") => "(x)"
// parentheticallySpeaking("4agh(y)") => "(y)"
// parentheticallySpeaking("4agh()") => "()"
//
string parentheticallySpeaking(string str)
//Approach:
//same logic as last time: process the string one by one char
//str has to AT LEAST HAVE TWO CHARS: "()"... 
{
	if (str.substr(0, 1) == "(")
	{
		if (str.substr(str.size() - 1, 1) == ")")
			return str;
		else
			return parentheticallySpeaking(str.substr(0, str.size() - 1));
	}
	else return parentheticallySpeaking(str.substr(1, str.size() - 1));
}


// Return true if the total of any combination of elements in
// the array a equals the value of the target.
//
// Pseudocode Example:
// totalEclipseOfTheHeart([2, 4, 8], 3, 10) => true
// totalEclipseOfTheHeart([2, 4, 8], 3, 6) => true
// totalEclipseOfTheHeart([2, 4, 8], 3, 11) => false
// totalEclipseOfTheHeart([2, 4, 8], 3, 0) => true
// totalEclipseOfTheHeart([], 0, 0) => true
//
bool totalEclipseOfTheHeart(const int a[], int size, int target)
{
	if (target == 0)
		return true; // the only way you return true is if the target is 0
	if (size == 0)
		return false; // if you deplete the array, then it's not gonna work
	return (totalEclipseOfTheHeart(a + 1, size - 1, target - a[0]) || totalEclipseOfTheHeart(a + 1, size - 1, target));
}


//The maze function
void mazeSolver(string maze[], int sr, int sc, int er, int ec, bool& ret)
{
	//"curr" = end, then it's possible!
	if (sr == er && sc == ec)
	{
		ret = true;
		return;
	}
	//drop crumb so we don't recheck where we've been!
	maze[sr][sc] = '#'; //guess it needs to be specifically a char if you want to isolate a index!
	if (maze[sr - 1][sc] == '.')
		mazeSolver(maze, sr - 1, sc, er, ec, ret);
	if (maze[sr + 1][sc] == '.')
		mazeSolver(maze, sr + 1, sc, er, ec, ret);
	if (maze[sr][sc - 1] == '.')
		mazeSolver(maze, sr, sc - 1, er, ec, ret);
	if (maze[sr][sc + 1] == '.')
		mazeSolver(maze, sr, sc + 1, er, ec, ret);
	//if we literally have run through all the recursive calls and nothing returns true,
	//then we've reached a dead end and should go back up a level... in the "last" case,
	//the maze is impossible and thus, we won't have changed ret!!!
	return;
}
// Return true if there is a path from (sr, sc) to (er, ec) through the maze; return false otherwise
// 
// Pseudocode:
// If the start location is equal to the ending location, then we've solved the maze, so return true.
//		mark the "current" (sr, sc) as visited.
//		For each of the four directions,
//			if the location one step in that direction is unvisited and a path (.)
//				then call seasonFinale starting from that location with the same (er, ec)
//					if that returns true, then return true.
//			if you exhaust all the possibilities, return false.
//
// seems that based on the assumptions about the inputs and the way the code is written, 
// we cannot physically end up on an @ or on an X: going OOB is impossible!
bool seasonFinale(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	bool ret = false;
	mazeSolver(maze, sr, sc, er, ec, ret);
	return ret;
}


int main()
{
	//mTimesN
	assert(mTimesN(4, 3) == 12);
	assert(mTimesN(4, 0) == 0);
	assert(mTimesN(0, 4) == 0);
	assert(mTimesN(0, 0) == 0);
	assert(mTimesN(1, 4) == 4);
	assert(mTimesN(4, 1) == 4);


	//tallyTheDigits
	assert(tallyTheDigits(18838, 8) == 3);
	assert(tallyTheDigits(55555, 3) == 0);
	assert(tallyTheDigits(55555, 5) == 5);
	assert(tallyTheDigits(00000, 0) == 0 || tallyTheDigits(00000, 0) == 1);
	assert(tallyTheDigits(0, 0) == 0 || tallyTheDigits(0, 0) == 1);
	assert(tallyTheDigits(18838, 1) == 1);
	assert(tallyTheDigits(13331, 1) == 2);
	assert(tallyTheDigits(0001, 0) == 0);
	assert(tallyTheDigits(0001, 1) == 1);


	//foursUp
	assert(foursUp("goodbye") == "go44odbye");
	assert(foursUp("yyuu") == "y44yu44u");
	assert(foursUp("aaaa") == "a44a44a44a");
	assert(foursUp("godbye") == "godbye");
	assert(foursUp("g") == "g");
	assert(foursUp("gg") == "g44g");


	//parentheticallySpeaking
	assert(parentheticallySpeaking("abc(ghj)789") == "(ghj)");
	assert(parentheticallySpeaking("(x)7") == "(x)");
	assert(parentheticallySpeaking("4agh(y)") == "(y)");
	assert(parentheticallySpeaking("4agh()") == "()");
	assert(parentheticallySpeaking("()") == "()");
	assert(parentheticallySpeaking("()as") == "()");
	assert(parentheticallySpeaking("(NASDAQ)") == "(NASDAQ)");
	assert(parentheticallySpeaking("a(as)") == "(as)");
	assert(parentheticallySpeaking("(as)a") == "(as)");
	assert(parentheticallySpeaking("a(as)a") == "(as)");


	//totalEclipseOfTheHeart
	int arr1[3] = { 2, 4, 8 };

	int arr2[2] = { 2, 4 };

	int arr3[1] = { 2 };

	int zero[1] = { -999 }; // when we pass this, we pass size 0 to clarify that this is replicating an empty array!

	int bigArr[6] = { 1,2,3,4,5,6 };

	assert(totalEclipseOfTheHeart(arr1, 3, 10) == true);
	assert(totalEclipseOfTheHeart(arr1, 3, 6) == true);
	assert(totalEclipseOfTheHeart(arr1, 3, 11) == false);
	assert(totalEclipseOfTheHeart(arr1, 3, 0) == true);
	assert(totalEclipseOfTheHeart(arr1, 3, 12) == true);

	assert(totalEclipseOfTheHeart(arr2, 2, 6) == true);
	assert(totalEclipseOfTheHeart(arr2, 2, 2) == true);
	assert(totalEclipseOfTheHeart(arr2, 2, 4) == true);
	assert(totalEclipseOfTheHeart(arr2, 2, 0) == true);
	assert(totalEclipseOfTheHeart(arr2, 2, 3) == false);

	assert(totalEclipseOfTheHeart(arr3, 1, 2) == true);
	assert(totalEclipseOfTheHeart(arr3, 1, 0) == true);
	assert(totalEclipseOfTheHeart(arr3, 1, 4) == false);
	assert(totalEclipseOfTheHeart(arr3, 1, 3) == false);

	assert(totalEclipseOfTheHeart(zero, 0, 0) == true);
	assert(totalEclipseOfTheHeart(zero, 0, 3) == false);

	assert(totalEclipseOfTheHeart(bigArr, 6, 12) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 1) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 2) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 3) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 4) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 5) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 6) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 14) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 8) == true);
	assert(totalEclipseOfTheHeart(bigArr, 6, 100) == false);


	//seasonFinale
	string m1a[5] = { //r = 5, c = 7
					 "XXXXXXX",
					 "X...X@X",
					 "XXX.X.X",
					 "X@....X",
					 "XXXXXXX" };
	string m1b[5] = { //r = 5, c = 7
					 "XXXXXXX",
					 "X...X@X",
					 "XXX.X.X",
					 "X@....X",
					 "XXXXXXX" };
	string m1c[5] = { //r = 5, c = 7
					 "XXXXXXX",
					 "X...X@X",
					 "XXX.X.X",
					 "X@....X",
					 "XXXXXXX" };
	string m1d[5] = { //r = 5, c = 7
					 "XXXXXXX",
					 "X...X@X",
					 "XXX.X.X",
					 "X@....X",
					 "XXXXXXX" };
	string m1e[5] = { //r = 5, c = 7
					 "XXXXXXX",
					 "X...X@X",
					 "XXX.X.X",
					 "X@....X",
					 "XXXXXXX" };

	string m2a[10] = { //r = 10, c = 10
						"XXXXXXXXXX",
						"X.......@X",
						"XX@X@@.XXX",
						"X..X.X...X",
						"X..X...@.X",
						"X....XXX.X",
						"X@X....XXX",
						"X..XX.XX.X",
						"X...X....X",
						"XXXXXXXXXX" };
	string m2b[10] = { //r = 10, c = 10
						"XXXXXXXXXX",
						"X.......@X",
						"XX@X@@.XXX",
						"X..X.X...X",
						"X..X...@.X",
						"X....XXX.X",
						"X@X....XXX",
						"X..XX.XX.X",
						"X...X....X",
						"XXXXXXXXXX" };
	string m2c[10] = { //r = 10, c = 10
						"XXXXXXXXXX",
						"X.......@X",
						"XX@X@@.XXX",
						"X..X.X...X",
						"X..X...@.X",
						"X....XXX.X",
						"X@X....XXX",
						"X..XX.XX.X",
						"X...X....X",
						"XXXXXXXXXX" };
	string m2d[10] = { //r = 10, c = 10
						"XXXXXXXXXX",
						"X.......@X",
						"XX@X@@.XXX",
						"X..X.X...X",
						"X..X...@.X",
						"X....XXX.X",
						"X@X....XXX",
						"X..XX.XX.X",
						"X...X....X",
						"XXXXXXXXXX" };
	string m2e[10] = { //r = 10, c = 10
						"XXXXXXXXXX",
						"X.......@X",
						"XX@X@@.XXX",
						"X..X.X...X",
						"X..X...@.X",
						"X....XXX.X",
						"X@X....XXX",
						"X..XX.XX.X",
						"X...X....X",
						"XXXXXXXXXX" };
	string m2f[10] = { //r = 10, c = 10
						"XXXXXXXXXX",
						"X.......@X",
						"XX@X@@.XXX",
						"X..X.X...X",
						"X..X...@.X",
						"X....XXX.X",
						"X@X....XXX",
						"X..XX.XX.X",
						"X...X....X",
						"XXXXXXXXXX" };

	string m3a[4] = { //r = 4, c = 4
						"XXXX",
						"X.@X",
						"X@.X",
						"XXXX" };
	string m3b[4] = { //r = 4, c = 4
						"XXXX",
						"X.@X",
						"X@.X",
						"XXXX" };

	assert(seasonFinale(m1a, 5, 7, 1, 1, 3, 5) == true);
	cout << "m1a" << endl;
	assert(seasonFinale(m1b, 5, 7, 1, 1, 1, 2) == true);
	cout << "m1b" << endl;
	assert(seasonFinale(m1c, 5, 7, 1, 1, 2, 3) == true);
	cout << "m1c" << endl;
	assert(seasonFinale(m1d, 5, 7, 1, 1, 2, 5) == true);
	cout << "m1d" << endl;
	assert(seasonFinale(m1e, 5, 7, 1, 1, 3, 2) == true);
	cout << "m1e" << endl;

	assert(seasonFinale(m2a, 10, 10, 1, 1, 8, 8) == true);
	cout << "m2a" << endl;
	assert(seasonFinale(m2b, 10, 10, 1, 1, 5, 8) == true);
	cout << "m2b" << endl;
	assert(seasonFinale(m2c, 10, 10, 1, 1, 8, 1) == false);
	cout << "m2c" << endl;
	assert(seasonFinale(m2d, 10, 10, 1, 1, 7, 8) == true);
	cout << "m2d" << endl;
	assert(seasonFinale(m2e, 10, 10, 6, 4, 1, 1) == true);
	cout << "m2e" << endl;
	assert(seasonFinale(m2f, 10, 10, 1, 1, 6, 4) == true);
	cout << "m2f" << endl;

	assert(seasonFinale(m3a, 4, 4, 1, 1, 2, 2) == false);
	cout << "m3a" << endl;
	assert(seasonFinale(m3b, 4, 4, 1, 1, 1, 1) == true);
	cout << "m3b" << endl;


	cout << "REMOVE DEBUGGING CODE!!!" << endl;
}
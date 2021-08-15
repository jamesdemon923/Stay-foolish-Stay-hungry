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
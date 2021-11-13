#include <cassert> //REMOVE!!!
#include <iostream> //REMOVE!!!

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
//返回bool类型的仿函数为谓词
//括号中一个参数为一元谓词
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

//1、一元谓词
class GreaterFive
{
public:
	bool operator()(int val) 
    {
		return val > 5;
	}
};

void test01() 
{

	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

    //GreatFive() 匿名函数对象
    //根据底层可知返回迭代器的位置
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it == v.end()) 
    {
		cout << "没找到!" << endl;
	}
	else 
    {
		cout << "找到:" << *it << endl;
	}

}

//2、二元谓词
class MyCompare
{
public:
	bool operator()(int num1, int num2)
	{
		return num1 > num2;
	}
};

void test02()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(20);
	v.push_back(30);
	v.push_back(50);

	//默认从小到大
	sort(v.begin(), v.end());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << "----------------------------" << endl;

	//使用函数对象改变算法策略，排序从大到小
	sort(v.begin(), v.end(), MyCompare());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main() 
{

	//test01();
    test02();

	system("pause");

	return 0;
}
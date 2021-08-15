#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
#include <functional>

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10 ; i++) 
    {
		v1.push_back(i);
	}
    for (int j = 0; j < 10; j++)
    {
        v2.push_back(j + 1);
    }

    vector<int> v3;
	vector<int> v4;
	for (int i = 10; i > 0 ; i--) 
    {
		v3.push_back(i);
	}
    for (int j = 10; j > 0; j--)
    {
        v4.push_back(j - 1);
    }
    

	vector<int> vtarget;
	//Ŀ��������Ҫ��ǰ���ٿռ�
	vtarget.resize(v1.size() + v2.size());
	//�ϲ�  ��Ҫ������������
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vtarget.begin());
    for_each(vtarget.begin(), vtarget.end(), myPrint());
    cout << endl;

    vector<int> vtarget2;
	vtarget2.resize(v3.size() + v4.size());
    //�ϲ� ������������
    merge(v3.begin(), v3.end(), v4.begin(), v4.end(), vtarget2.begin(), greater<int>());
	for_each(vtarget2.begin(), vtarget2.end(), myPrint());
	cout << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
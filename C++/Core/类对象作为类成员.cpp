#include<iostream>
#include<string>
using namespace std;

//类对象作为类成员

//手机类
class Phone
{
public:

    Phone(string name)
    {
        cout << "Phone的构造函数调用" << endl;
        m_PName = name;
    }

    ~Phone()
    {
        cout << "Phone的析构函数调用" << endl;
    }

    string m_PName;
};

//人类
class Person
{

public:

    Person(string name, string pname):m_Name(name), m_Phone(pname)
    {
        cout << "Person的构造函数调用" << endl;
    }

    ~Person()
    {
        cout << "Person的析构函数调用" << endl;
    } 


    string m_Name;

    Phone m_Phone;

};

//当其他类对象作为本类成员，先构造其他类对象，再构造自身，析构顺序与构造顺序相反
void test01()
{
    Person p("James", "HUAWEI"); // Phone m_Phone = pName; 隐式转换法

    cout << p.m_Name << " takes " << p.m_Phone.m_PName << endl;
}

int main()
{
    test01();

    system("pause");
    return 0;
}
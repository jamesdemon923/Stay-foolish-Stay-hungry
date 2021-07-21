#include<iostream>

using namespace std;


//situations for copy constructor

class Person
{
public:
    Person()
    {
        cout << "Person默认构造函数调用" << endl;
    }

    Person(int age)
    {
        cout << "Person有参构造函数调用" << endl;
        m_Age = age;
    }

    Person(const Person& p)
    {
        cout << "Person拷贝构造函数调用" << endl;
        m_Age = p.m_Age;
    }

    ~Person()
    {
        cout << "Person析构函数调用" << endl;
    }

    int m_Age;
};

//使用一个已经创建完毕的对象来初始化一个新对象
void test01()
{
    Person p1(20);
    Person p2(p1);

    cout << "P2的年龄为:" << p2.m_Age << endl;
}

//值传递的方式给函数参数传值
void doWork(Person p)
{

}

void test02()
{
    Person p;
    doWork(p);

}

//值方式返回局部对象
Person doWork2()
{
    Person p1;
    cout << (int*)&p1 << endl;
    return p1;
}

void test03()
{
    Person p = doWork2();
    cout << (int*)&p << endl;
}

int main()
{
    //test01();
    //test02();
    test03();//没有调用拷贝构造函数，可能是因为返回值优化的原因
    system("pause");
    return 0;
}
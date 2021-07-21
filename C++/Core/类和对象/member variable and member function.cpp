#include<iostream>

using namespace std;

class Person
{
    public:
    int m_A; //非静态成员变量，属于类的对象上
    static int m_B;//静态成员变量，不属于类对象上，所以不影响p的字节仍为4
    void func()//非静态成员函数分开储存，不属于类对象上，所以不影响p的字节仍为4
    {

    }

    static void func2()//静态成员函数，不属于类对象上，所以不影响p的字节仍为4
    {

    }

};
int Person::m_B;

void test01()
{
    Person p;
    //C++编译器会给每个空对象分配一个字节空间，是为了区分空对象占内存的位置
    //每个空对象也应该有一个独一无二的内存地址
    cout << "size of p = " << sizeof(p) << endl;
}

void test02()
{
    Person p;
    cout << "size of p = " << sizeof(p) << endl;
}

int main()
{
    test02();
    system("pause");
    return 0;
}
#include<iostream>

using namespace std;

//静态成员函数
//所有对象共享同一个函数
//静态成员函数只能访问静态成员变量

class Person
{
public:
    static void func()
    {
        m_A = 100;//静态成员函数 可以访问静态成员变量
        
        //error: invalid use of member 'Person::m_B' in static member function
        //m_B = 200;//静态成员函数 不可以访问非静态成员变量，因为该数据属于特定对象，而函数无法区分
        cout << "static void func调用" << endl;
    }

    static int m_A;//静态成员变量
    int m_B;//非静态成员变量


private:
    //静态成员函数也是有访问权限的
    static void func2()
    {
        cout << "static void func2调用" << endl;
    }
};

int Person::m_A = 0;

void test01()
{
    //通过对象访问
    Person p;
    p.func();
    //通过类名访问
    Person::func();

    //Person::func2(); 因为在private作用域下
}


int main()
{
    test01();
    system("pause");
    return 0;
}
#include<iostream>

using namespace std;

class Base
{
    public:

    static int m_A;

    static void func()
    {
        cout << "Base static void func" << endl;
    }

};
int Base::m_A = 100;

class Son:public Base
{
    public:

    static int m_A;

    static void func()
    {
        cout << "Son static void func" << endl;
    }
};
int Son::m_A = 200;

//静态成员
void test01()
{
    //通过对象访问
    Son s;
    cout << "通过对象访问" << endl;
    cout << "Son m_A = " << s.m_A << endl;
    cout << "Base m_A = " << s.Base::m_A << endl;
    //通过类名访问
    cout << "通过类名访问" << endl;
    cout << "Son m_A = " << Son::m_A << endl;
    //第一::代表通过类名方式访问，第二个::代表访问父亲作用域下
    cout << "Base m_A = " << Son::Base::m_A << endl;
}

//静态成员函数
void test02()
{
    Son s;
    cout << "通过对象访问" << endl;
    s.func();
    s.Base::func();

    cout << "通过类名访问" << endl;
    Son::func();
    Son::Base::func();

}

int main()
{
    test02();
    system("pause");
    return 0;
}
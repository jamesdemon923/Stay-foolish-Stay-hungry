#include<iostream>
using namespace std;

class Base
{
    public:
    Base()
    {
        m_A = 100;
    }

    void func()
    {
        cout << "父类中的function" << endl;
    }

    void func(int a)
    {
        cout << "父类中的有参function" << endl;
    }

    int m_A;

};

class Son:public Base
{
    public:
    Son()
    {
        m_A = 200;
    }

    void func()
    {
        cout << "子类中的function" << endl;
    }

    int m_A;
};

//同名属性处理方式
void test01()
{
    Son s;
    cout << "m_A = " << s.m_A << endl;//直接调自身数据，即Son的
    //如果通过子类对象 访问到父类中同名成员，需要加作用域
    cout << "m_A = " << s.Base::m_A << endl;
}

//同名函数处理方式
void test02()
{
    Son s;
    s.func();//直接调子类中的函数
    //如果通过子类对象 访问到父类中同名函数，也需要加作用域
    s.Base::func();
    //子类出现同名函数，会隐藏父类所有同名函数，如果要访问，需要加作用域
    s.Base::func(100);

}

int main()
{
    test02();
    system("pause");
    return 0;
}
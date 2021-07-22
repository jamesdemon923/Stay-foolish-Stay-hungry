#include<iostream>

using namespace std;

class Base
{
    public:
    //只要有一个纯虚函数，类变为 抽象类
    //抽象类特点
    //1、无法实例化对象
    //2、抽象类的子类 必须重写父类中的纯虚函数，否则也属于抽象类
    virtual void func() = 0;//虚函数 改为 纯虚函数


};

class Son:public Base
{
    public:
    virtual void func() 
    {
        cout << "func函数调用" << endl;
    }
};

void test01()
{
    Base * base = new Son;
    base->func();
}

int main()
{
    test01();
    system("pause");
    return 0;
}
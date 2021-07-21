#include<iostream>

using namespace std;

class Base
{
public:
    int m_A;

    Base()
    {
        cout << "Base构造函数" << endl;
    }

    ~Base()
    {
        cout << "Base构析构函数" << endl;
    }

protected:
    int m_B;
private:
    int m_C;
    
};

class Son:public Base
{
public:

    int m_D;

    Son()
    {
        cout << "Son构造函数" << endl;
    }

    ~Son()
    {
        cout << "Son构析构函数" << endl;
    }
};

void test01()
{
    //父类中非静态成员属性都会被子类继承下去
    //父类中私有成员属性 被编译器隐藏了，因此访问不到 但都会被继承
    //cout << "size of Son = " << sizeof(Son) << endl;

    //Base b;

    //构造：先有父类，再有子类；析构顺序与构造相反
    Son s;
}

int main()
{
    test01();
    system("pause");
    return 0;
}
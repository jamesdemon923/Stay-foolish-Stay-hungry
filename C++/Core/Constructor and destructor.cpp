#include<iostream>

using namespace std;

//Constructor: class(){}
//Destructor: ~class(){}
class Person
{
public:
    //Constructor
    //没有返回值，不用写void
    //函数名 与类名相同
    //构造函数可以有参数，可以发生重载
    //创建对象的时候，构造函数会自动调用，而且只调用一次
    Person()
    {
        cout << "Person 构造函数的调用" << endl;
    }

    //Destructor
    //析构函数不能有参数，不会发生重载
    //释放对象的时候，析构函数才会调用，只调用一次
    ~Person()
    {
        cout << "Person 析构函数的调用" << endl;
    }
};

//构造和析构是必须有的实验，如果我们自己不提供，编译器会提供一个空实现的构造和析构
void test01()
{
    Person p; //栈上数据(局部变量)，test01执行完毕后，释放这个对象
}

int main()
{
    test01();

    //Person p; //变量此刻并不会释放，要等到main结束才会释放，也只能到那个时候才会调用析构函数

    system("pause");
    return 0;
}

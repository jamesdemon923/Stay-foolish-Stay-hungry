#include<iostream>
using namespace std;

class Person
{
public:
    //无参构造(默认构造)
    Person()
    {
        cout << "Person的无参构造函数调用" << endl;
    }
    //有参构造
    Person(int a)
    {
        age = a;
        cout << "Person的有参构造函数调用" << endl;
    }
    //拷贝构造函数
    Person(const Person& p)
    {
        //将传入的对象身上的所有属性，拷贝到新的对象身上
        age = p.age;
        cout << "Person的拷贝构造函数调用" << endl;
    }
    //析构函数
    ~Person()
    {
        cout << "Person的析构函数调用" << endl;
    }

    int age;

};

//函数测试调用
void test01()
{
    //*****括号法
    //Person p1;//默认构造函数调用
    //Person p2(10);//有参构造函数调用
    //Person p3(p2);//拷贝构造函数调用

    //cout << "p2's age is " << p2.age << endl;
    //cout << "p3's age is " << p3.age << endl;

    //注意事项1
    //使用默认构造函数时候，不要加()
    //下面这行代码不创建对象，因为compiler会认为这是一个函数声明。
    //Person p1();

    //显示法
    Person p1;
    Person p2 = Person(10); //调用有参构造
    //Person p3 = Person(p2); //调用拷贝构造
    Person p3 = p2; //调用拷贝构造的另一种写法

    //Person(10); //*****匿名对象 特点：当此行执行结束后，系统会立即回收掉匿名对象
    //cout << "test 匿名对象" << endl;

    //注意事项2 
    //不要利用拷贝构造函数 初始化匿名对象，因为编译器会认为是对象声明
    //Person(p3);//编译器会认为 Person(p3) = Person p3;

    //隐式转换法
    Person p4 = 10;//相当于Person p4 = Person(10);
    Person p5 = p4;//相当于Person p5 = Person(p4);
}

int main()
{
    test01();
    system("pause");
    return 0;
}
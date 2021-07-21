#include<iostream>
using namespace std;

class Person
{
    public:
    Person()
    {
        cout << "Person的默认虚构函数调用" << endl;
    }

    Person(int age, int height)
    {
        m_Age = age;
        m_Height = new int(height);//new 给数据创造堆区空间，返回地址，这个地址储存了height的数值，具体内容见“内存四区”
        cout << "Person的有参虚构函数调用" << endl;
    }

    //自己实现拷贝构造函数 解决浅拷贝带来的问题
    Person (const Person&p)
    {
        cout << "Person的拷贝构造函数调用" << endl;
        m_Age = p.m_Age;
        //m_Height = p.m_Height; 编译器默认实现为此行
        m_Height = new int(*p.m_Height);//*****深拷贝，利用new创建新的堆区
    }

    ~Person()
    {
        //析构函数，将堆区开辟数据做释放操作
        if(m_Height != NULL)
        {
            delete m_Height;//delete释放，对应new的创造
            m_Height = NULL;//防止野指针出现
        }
        //会有断点产生，因为用编译器提供的拷贝构造函数，会做浅拷贝操作
        //浅拷贝会带来堆区的重复释放，从而导致程序崩溃
        //*****解决方法:利用深拷贝(创造新的堆区，数据相同，地址不同)进行解决
        cout << "Person的析构函数调用" << endl;
    }



    int m_Age;

    int *m_Height;
};

void test01()
{

    Person p1(18,160);

    cout << "p1's age is " << p1.m_Age << "\tp1's height is " << *p1.m_Height << endl;

    Person p2(p1);

    cout << "p2's age is " << p2.m_Age << "\tp2's height is " << *p2.m_Height << endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}
#include<iostream>

using namespace std;

class Person
{
    public:

    Person(int age)
    {
        m_Age = new int(age);
    }

    ~Person()
    {
        if (m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
    }

    //重载 赋值运算符
    Person& operator=(Person &p)
    {
        //编译器提供浅拷贝
        //m_Age = p.m_Age;

        //应该先判断是否有属性在堆区，如果有先释放干净，然后再深拷贝
        if(m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
        //深拷贝
        m_Age = new int (*p.m_Age);

        return *this;
    }
    int *m_Age;
};

void test01()
{
    Person p1(18);

    Person p2(20);

    Person p3(30);

    p3 = p2 = p1;//赋值运算，浅拷贝，会导致堆区内存重复释放

    cout << "p1's age " << *p1.m_Age << endl;

    cout << "p2's age " << *p2.m_Age << endl;

}

int main()
{
    test01();
    system("pause");
    return 0;
}
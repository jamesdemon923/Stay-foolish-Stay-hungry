#include<iostream>

using namespace std;

class Person
{
public:

    //this本质 是 指针常量 指针的指向是不可以修改的
    //成员函数后面加const，修饰的是this指针，让指针指向的值也不可以修改
    void showPerson() const
    {
        this->m_B = 100;
        //this->m_A = 100;//因为const
        //this = NULL;//this指针不可以修改指针的指向

    }

    void func()
    {
        m_A = 100;
    }

    int m_A;
    mutable int m_B;//特殊变量，即使在常函数中，也可以修改这个值，加关键字mutable

};

void test01()
{
    Person p;
    p.showPerson();

}

//常对象
void test02()
{
    const Person p;//在对象前加const，变为常对象
    //p.m_A = 100;
    p.m_B = 100;//因为加了mutable，所以可以修改

    //常对象只能调用常函数
    p.showPerson();
    //p.func();不可调用
}

int main()
{

    system("pause");
    return 0;
}
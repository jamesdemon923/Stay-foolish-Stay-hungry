#include<iostream>
using namespace std;

class Person
{
public:
    Person(int age)
    {
        //this指针指向 被调用的成员函数 所属对象
        this->age = age;
    }
    
    //用引用返回，可以保证一直返回的是p2，如果是Person PersonAddAge 返回值的话，返回的就是一个新对象
    Person& PersonAddAge(Person& p)
    {
        this->age += p.age;

        //this指向p2的指针，而*this指向的就是p2的本身
        return *this;
    }

    int age;

};

//1、解决名称冲突
void test01()
{
    Person p1(18);

    cout << "p1's age is " << p1.age << endl;

}

//2、返回对象本身用*this
void test02()
{
    Person p1(10);
    
    Person p2(10);

    //链式编程思想
    p2.PersonAddAge(p1).PersonAddAge(p1).PersonAddAge(p1);//因为返回值为p2，因此可以无限追加

    cout << "p2's age is " << p2.age << endl;
}
int main()
{
    //test01();
    test02();
    system("pause");
    return 0;
}
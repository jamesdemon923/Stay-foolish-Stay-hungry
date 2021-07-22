#include<iostream>

using namespace std;

class Animal
{
    public:

    virtual void speak()
    {
        cout << "动物在说话" << endl;
    }
};

class Cat:public Animal
{
    public:
    //重写 函数返回值类型 函数名 参数列表 完全相同
    void speak()
    {
        cout << "MewMew" << endl;
    }
};

class Dog:public Animal
{
    public:
    void speak()
    {
        cout << "BarkBark" << endl;
    }
};

//地址早绑定 编译阶段就已经确定函数地址
//如果想让猫说话，地址必须得晚绑定

//动态多态满足条件
//1、有继承关系
//2、子类重写父类虚函数

//动态多态使用
//父类的指针或者引用 执行于类对象

//底层原理：形成了vfptr指向虚函数，子类继承父类的vfptr和虚函数，但重写之后，会形成自己作用域下的虚函数

void doSpeak(Animal &animal)
{
    animal.speak();
}

test01()
{
    Cat cat;
    doSpeak(cat);

    Dog dog;
    doSpeak(dog);

}

test02()
{
    cout << "size of Animal = " << sizeof(Animal) << endl;
}

int main()
{
    test02();

    system("pause");
    return 0;
}
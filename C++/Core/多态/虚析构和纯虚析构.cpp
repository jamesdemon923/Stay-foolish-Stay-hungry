#include<iostream>
#include<string>
using namespace std;

class Animal
{
public:
    Animal()
    {
        cout << "Animal的构造函数调用" << endl;
    }

    virtual void speak() = 0;

/*     
    //利用虚析构可以解决 父类指针释放子类对象时不干净的问题
    virtual ~Animal()
    {
        
    } 
*/

    //纯虚析构
    //有了纯虚析构，这个类也变为抽象类，无法实例化对象
    virtual ~Animal() = 0;
};

Animal::~Animal()
{
    cout << "Animal的纯虚析构函数调用" << endl;
}

class Cat:public Animal
{
public:

    Cat(string name)
    {
        cout << "Car的构造函数调用" << endl;
        m_Name = new string(name);
    }

    virtual void speak()
    {
        cout << *m_Name << "\tMewMew" << endl;
    }

    ~Cat()
    {
        if(m_Name != NULL)
        {
            cout << "Cat的析构函数调用" << endl;
            delete m_Name;
            m_Name = NULL;
        }
    }

    string *m_Name;
};

void test01()
{
    Animal * animal = new Cat("Tom");
    animal->speak();
    delete animal;
}

int main()
{
    test01();
    system("pause");
    return 0;
}
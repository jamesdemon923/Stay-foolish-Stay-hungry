#include<iostream>
#include<string>
using namespace std;

class Animal
{
public:
    Animal()
    {
        cout << "Animal�Ĺ��캯������" << endl;
    }

    virtual void speak() = 0;

/*     
    //�������������Խ�� ����ָ���ͷ��������ʱ���ɾ�������
    virtual ~Animal()
    {
        
    } 
*/

    //��������
    //���˴��������������Ҳ��Ϊ�����࣬�޷�ʵ��������
    virtual ~Animal() = 0;
};

Animal::~Animal()
{
    cout << "Animal�Ĵ���������������" << endl;
}

class Cat:public Animal
{
public:

    Cat(string name)
    {
        cout << "Car�Ĺ��캯������" << endl;
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
            cout << "Cat��������������" << endl;
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
#include<iostream>

using namespace std;

class Person
{
    public:

    void showClassName()
    {
        cout << "This is Person class " << endl;
    }

    void showPersonAge()
    {
        //传入的指针为NULL，this访问不到成员
        if(this == NULL)
        {
            return;
        }
        cout << "Age is " << this->m_Age << endl;
    }

    int m_Age;
};

void test01()
{
    Person * p = NULL;

    p->showClassName();

    //p->showPersonAge();
}

int main()
{
    test01();

    system("pause");
    return 0;
}

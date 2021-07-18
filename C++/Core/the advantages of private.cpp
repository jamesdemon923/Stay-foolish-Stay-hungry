#include<iostream>
#include<string>

using namespace std;

//成员属性设置为私有
//1、可以自己控制读写权限
//2、对于写，可以检测数据的有效性

class Person
{
public:
    //可读可写
    void setName(string name)
    {
        m_Name = name;
    }

    string getName()
    {
        return m_Name;
    }

    //只读权限
    int getAge()
    {
        //int m_Age = 18;
        return m_Age;
    }
    //通过return等功能，从而限定数据的范围，保证其有效性
    void setAge(int age)
    {
        if(age < 0 || age > 150)
        {
            cout << "输入年龄有误" << endl;
            return;
        }
        m_Age = age;
    }

    //只写权限
    int setLover(string lover)
    {
        m_Lover = lover; 
    }

private:
    string m_Name;

    int m_Age;

    string m_Lover;
};

int main()
{
    Person p;
    p.setName("James");
    cout << "His name is:" << p.getName() << endl;
    cout << "His age is:" << p.getAge() << endl;
    p.setLover("Christy");
    system("pause");
    return 0;
}
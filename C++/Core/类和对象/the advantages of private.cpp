#include<iostream>
#include<string>

using namespace std;

//��Ա��������Ϊ˽��
//1�������Լ����ƶ�дȨ��
//2������д�����Լ�����ݵ���Ч��

class Person
{
public:
    //�ɶ���д
    void setName(string name)
    {
        m_Name = name;
    }

    string getName()
    {
        return m_Name;
    }

    //ֻ��Ȩ��
    int getAge()
    {
        //int m_Age = 18;
        return m_Age;
    }
    //ͨ��return�ȹ��ܣ��Ӷ��޶����ݵķ�Χ����֤����Ч��
    void setAge(int age)
    {
        if(age < 0 || age > 150)
        {
            cout << "������������" << endl;
            return;
        }
        m_Age = age;
    }

    //ֻдȨ��
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
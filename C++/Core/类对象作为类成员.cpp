#include<iostream>
#include<string>
using namespace std;

//�������Ϊ���Ա

//�ֻ���
class Phone
{
public:

    Phone(string name)
    {
        cout << "Phone�Ĺ��캯������" << endl;
        m_PName = name;
    }

    ~Phone()
    {
        cout << "Phone��������������" << endl;
    }

    string m_PName;
};

//����
class Person
{

public:

    Person(string name, string pname):m_Name(name), m_Phone(pname)
    {
        cout << "Person�Ĺ��캯������" << endl;
    }

    ~Person()
    {
        cout << "Person��������������" << endl;
    } 


    string m_Name;

    Phone m_Phone;

};

//�������������Ϊ�����Ա���ȹ�������������ٹ�����������˳���빹��˳���෴
void test01()
{
    Person p("James", "HUAWEI"); // Phone m_Phone = pName; ��ʽת����

    cout << p.m_Name << " takes " << p.m_Phone.m_PName << endl;
}

int main()
{
    test01();

    system("pause");
    return 0;
}
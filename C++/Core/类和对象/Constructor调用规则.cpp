#include<iostream>
using namespace std;

//���캯�����ù���
//1������һ���࣬C++���������ÿ���඼�������3������
//Ĭ�Ϲ���(��ʵ��)
//��������(��ʵ��)
//��������(ֵ����)

class Person
{
public:
    //Person()
    //{
    //    cout << "Person��Ĭ�Ϲ��캯������" << endl;
    //}

    Person(int age)
    {
        cout << "Person���вι��캯������" << endl;
        m_Age = age;
    }

    Person(const Person& p)
    {
        cout << "Person�Ŀ������캯������" << endl;
        m_Age = p.m_Age;
    }

    ~Person()
    {
        cout << "Person��������������" << endl;
    }

    int m_Age;
};

//void test01()
//{
//    Person p;
//    p.m_Age = 18;
//    Person p2(p);
//    cout << "P2's age " << p2.m_Age << endl;
//}

//2���������д���вι��캯�����������Ͳ����ṩĬ�Ϲ��죬����Ȼ���ṩ��������
//�������д�˿������죬�������Ͳ����ṩ�������죬*****Ҳ�����ṩĬ�Ϲ���
void test02()
{
    Person p(28);
    Person p2(p);
    cout << "P2's age" << p2.m_Age << endl;
}

int main()
{
    //test01();
    test02();
    system("pause");
    return 0;
}




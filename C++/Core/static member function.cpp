#include<iostream>

using namespace std;

//��̬��Ա����
//���ж�����ͬһ������
//��̬��Ա����ֻ�ܷ��ʾ�̬��Ա����

class Person
{
public:
    static void func()
    {
        m_A = 100;//��̬��Ա���� ���Է��ʾ�̬��Ա����
        
        //error: invalid use of member 'Person::m_B' in static member function
        //m_B = 200;//��̬��Ա���� �����Է��ʷǾ�̬��Ա��������Ϊ�����������ض����󣬶������޷�����
        cout << "static void func����" << endl;
    }

    static int m_A;//��̬��Ա����
    int m_B;//�Ǿ�̬��Ա����


private:
    //��̬��Ա����Ҳ���з���Ȩ�޵�
    static void func2()
    {
        cout << "static void func2����" << endl;
    }
};

int Person::m_A = 0;

void test01()
{
    //ͨ���������
    Person p;
    p.func();
    //ͨ����������
    Person::func();

    //Person::func2(); ��Ϊ��private��������
}


int main()
{
    test01();
    system("pause");
    return 0;
}
#include<iostream>

using namespace std;

class Person
{
public:

    //this���� �� ָ�볣�� ָ���ָ���ǲ������޸ĵ�
    //��Ա���������const�����ε���thisָ�룬��ָ��ָ���ֵҲ�������޸�
    void showPerson() const
    {
        this->m_B = 100;
        //this->m_A = 100;//��Ϊconst
        //this = NULL;//thisָ�벻�����޸�ָ���ָ��

    }

    void func()
    {
        m_A = 100;
    }

    int m_A;
    mutable int m_B;//�����������ʹ�ڳ������У�Ҳ�����޸����ֵ���ӹؼ���mutable

};

void test01()
{
    Person p;
    p.showPerson();

}

//������
void test02()
{
    const Person p;//�ڶ���ǰ��const����Ϊ������
    //p.m_A = 100;
    p.m_B = 100;//��Ϊ����mutable�����Կ����޸�

    //������ֻ�ܵ��ó�����
    p.showPerson();
    //p.func();���ɵ���
}

int main()
{

    system("pause");
    return 0;
}
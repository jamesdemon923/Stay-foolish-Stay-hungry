#include<iostream>

using namespace std;

//��̬��Ա����
class Person
{
public:


    //����׶ξͷ����ڴ�
    static int m_A;

    //��̬��Ա�����з���Ȩ��
private:
    static int m_B;

};
//���������������ʼ��
int Person::m_A = 100;
int Person::m_B = 200;

void test01()
{
    Person p;
    cout << p.m_A << endl;

    Person p2;
    p2.m_A = 200;
    //���ж��󶼹���ͬһ������,p2�޸��ˣ�p�������޸ĺ������
    cout << p.m_A << endl;
}

void test02()
{

    //��̬��Ա���� ������ĳ�������ϣ����ж��󶼹���ͬһ������
    //��̬��Ա���������ַ��ʷ�ʽ

    //1��ͨ��������з���
    Person p;
    cout << p.m_A << endl;
    //2��ͨ���������з���
    cout << Person::m_A << endl;
    //cout << Person::m_B << endl; 'int Person::m_B' is private within this context

}


int main()
{
    //test01();
    test02();
    system("pause");
    //system("cls");
    return 0;
}
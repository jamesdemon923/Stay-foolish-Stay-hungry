#include<iostream>
using namespace std;

class Base
{
    public:
    Base()
    {
        m_A = 100;
    }

    void func()
    {
        cout << "�����е�function" << endl;
    }

    void func(int a)
    {
        cout << "�����е��в�function" << endl;
    }

    int m_A;

};

class Son:public Base
{
    public:
    Son()
    {
        m_A = 200;
    }

    void func()
    {
        cout << "�����е�function" << endl;
    }

    int m_A;
};

//ͬ�����Դ���ʽ
void test01()
{
    Son s;
    cout << "m_A = " << s.m_A << endl;//ֱ�ӵ��������ݣ���Son��
    //���ͨ��������� ���ʵ�������ͬ����Ա����Ҫ��������
    cout << "m_A = " << s.Base::m_A << endl;
}

//ͬ����������ʽ
void test02()
{
    Son s;
    s.func();//ֱ�ӵ������еĺ���
    //���ͨ��������� ���ʵ�������ͬ��������Ҳ��Ҫ��������
    s.Base::func();
    //�������ͬ�������������ظ�������ͬ�����������Ҫ���ʣ���Ҫ��������
    s.Base::func(100);

}

int main()
{
    test02();
    system("pause");
    return 0;
}
#include<iostream>

using namespace std;

class Base1
{
public:
    int m_A;
protected:
    int m_B;
private:
    int m_C;
};

//�����̳�
class Son1:public Base1
{
public:
    void func()
    {
        m_A = 10;//���� ����Ȩ�޳�Ա ������ ��Ȼ�ǹ���Ȩ��
        m_B = 10;//���� ����Ȩ�޳�Ա ������ ��Ȼ�Ǳ���Ȩ��
    }
};

void test01()
{
    Son1 s1;
    s1.m_A = 100;
    //s1.m_B = 100;����Ȩ�ޣ������޷�����
}

//�����̳�
class Son2:protected Base1
{
public:
    void func()
    {
        m_A = 10;//���� ����Ȩ�޳�Ա ������ ��Ϊ����Ȩ��
        m_B = 10;//���� ����Ȩ�޳�Ա ������ ��Ȼ�Ǳ���Ȩ��
    }
};

void test02()
{
    Son2 s2;
    //s2.m_A = 100;����Ȩ�ޣ������޷�����
    //s2.m_B = 100;����Ȩ�ޣ������޷�����
}

//˽�м̳�
class Son3:protected Base1
{
public:
    void func()
    {
        m_A = 10;//���� ����Ȩ�޳�Ա ������ ��Ϊ˽��Ȩ��
        m_B = 10;//���� ����Ȩ�޳�Ա ������ ��Ȼ��˽��Ȩ��
    }
};

class GrandSon3:public Son3
{
public:
    void func()
    {
        //m_A = 10;//�Ѿ���˽��Ȩ���ˣ����ʲ���
        //m_B = 10;//�Ѿ���˽��Ȩ���ˣ����ʲ���
    }
};


void test03()
{
    Son3 s3;
    //s3.m_A = 100;˽��Ȩ�ޣ������޷�����
    //s3.m_B = 100;˽��Ȩ�ޣ������޷�����
}

int main()
{
    test01();
    system("pause");
    return 0;
}
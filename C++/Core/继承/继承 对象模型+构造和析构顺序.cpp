#include<iostream>

using namespace std;

class Base
{
public:
    int m_A;

    Base()
    {
        cout << "Base���캯��" << endl;
    }

    ~Base()
    {
        cout << "Base����������" << endl;
    }

protected:
    int m_B;
private:
    int m_C;
    
};

class Son:public Base
{
public:

    int m_D;

    Son()
    {
        cout << "Son���캯��" << endl;
    }

    ~Son()
    {
        cout << "Son����������" << endl;
    }
};

void test01()
{
    //�����зǾ�̬��Ա���Զ��ᱻ����̳���ȥ
    //������˽�г�Ա���� �������������ˣ���˷��ʲ��� �����ᱻ�̳�
    //cout << "size of Son = " << sizeof(Son) << endl;

    //Base b;

    //���죺���и��࣬�������ࣻ����˳���빹���෴
    Son s;
}

int main()
{
    test01();
    system("pause");
    return 0;
}
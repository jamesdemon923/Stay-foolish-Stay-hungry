#include<iostream>

using namespace std;

class Person
{
    public:
    int m_A; //�Ǿ�̬��Ա������������Ķ�����
    static int m_B;//��̬��Ա������������������ϣ����Բ�Ӱ��p���ֽ���Ϊ4
    void func()//�Ǿ�̬��Ա�����ֿ����棬������������ϣ����Բ�Ӱ��p���ֽ���Ϊ4
    {

    }

    static void func2()//��̬��Ա������������������ϣ����Բ�Ӱ��p���ֽ���Ϊ4
    {

    }

};
int Person::m_B;

void test01()
{
    Person p;
    //C++���������ÿ���ն������һ���ֽڿռ䣬��Ϊ�����ֿն���ռ�ڴ��λ��
    //ÿ���ն���ҲӦ����һ����һ�޶����ڴ��ַ
    cout << "size of p = " << sizeof(p) << endl;
}

void test02()
{
    Person p;
    cout << "size of p = " << sizeof(p) << endl;
}

int main()
{
    test02();
    system("pause");
    return 0;
}
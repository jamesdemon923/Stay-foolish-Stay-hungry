#include<iostream>
using namespace std;

class Person
{
    public:
    Person()
    {
        cout << "Person��Ĭ���鹹��������" << endl;
    }

    Person(int age, int height)
    {
        m_Age = age;
        m_Height = new int(height);//new �����ݴ�������ռ䣬���ص�ַ�������ַ������height����ֵ���������ݼ����ڴ�������
        cout << "Person���в��鹹��������" << endl;
    }

    //�Լ�ʵ�ֿ������캯�� ���ǳ��������������
    Person (const Person&p)
    {
        cout << "Person�Ŀ������캯������" << endl;
        m_Age = p.m_Age;
        //m_Height = p.m_Height; ������Ĭ��ʵ��Ϊ����
        m_Height = new int(*p.m_Height);//*****���������new�����µĶ���
    }

    ~Person()
    {
        //���������������������������ͷŲ���
        if(m_Height != NULL)
        {
            delete m_Height;//delete�ͷţ���Ӧnew�Ĵ���
            m_Height = NULL;//��ֹҰָ�����
        }
        //���жϵ��������Ϊ�ñ������ṩ�Ŀ������캯��������ǳ��������
        //ǳ����������������ظ��ͷţ��Ӷ����³������
        //*****�������:�������(�����µĶ�����������ͬ����ַ��ͬ)���н��
        cout << "Person��������������" << endl;
    }



    int m_Age;

    int *m_Height;
};

void test01()
{

    Person p1(18,160);

    cout << "p1's age is " << p1.m_Age << "\tp1's height is " << *p1.m_Height << endl;

    Person p2(p1);

    cout << "p2's age is " << p2.m_Age << "\tp2's height is " << *p2.m_Height << endl;
}

int main()
{
    test01();
    system("pause");
    return 0;
}
#include<iostream>
using namespace std;

class Person
{
public:
    //�޲ι���(Ĭ�Ϲ���)
    Person()
    {
        cout << "Person���޲ι��캯������" << endl;
    }
    //�вι���
    Person(int a)
    {
        age = a;
        cout << "Person���вι��캯������" << endl;
    }
    //�������캯��
    Person(const Person& p)
    {
        //������Ķ������ϵ��������ԣ��������µĶ�������
        age = p.age;
        cout << "Person�Ŀ������캯������" << endl;
    }
    //��������
    ~Person()
    {
        cout << "Person��������������" << endl;
    }

    int age;

};

//�������Ե���
void test01()
{
    //*****���ŷ�
    //Person p1;//Ĭ�Ϲ��캯������
    //Person p2(10);//�вι��캯������
    //Person p3(p2);//�������캯������

    //cout << "p2's age is " << p2.age << endl;
    //cout << "p3's age is " << p3.age << endl;

    //ע������1
    //ʹ��Ĭ�Ϲ��캯��ʱ�򣬲�Ҫ��()
    //�������д��벻����������Ϊcompiler����Ϊ����һ������������
    //Person p1();

    //��ʾ��
    Person p1;
    Person p2 = Person(10); //�����вι���
    //Person p3 = Person(p2); //���ÿ�������
    Person p3 = p2; //���ÿ����������һ��д��

    //Person(10); //*****�������� �ص㣺������ִ�н�����ϵͳ���������յ���������
    //cout << "test ��������" << endl;

    //ע������2 
    //��Ҫ���ÿ������캯�� ��ʼ������������Ϊ����������Ϊ�Ƕ�������
    //Person(p3);//����������Ϊ Person(p3) = Person p3;

    //��ʽת����
    Person p4 = 10;//�൱��Person p4 = Person(10);
    Person p5 = p4;//�൱��Person p5 = Person(p4);
}

int main()
{
    test01();
    system("pause");
    return 0;
}
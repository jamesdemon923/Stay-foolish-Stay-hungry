#include<iostream>

using namespace std;

//Constructor: class(){}
//Destructor: ~class(){}
class Person
{
public:
    //Constructor
    //û�з���ֵ������дvoid
    //������ ��������ͬ
    //���캯�������в��������Է�������
    //���������ʱ�򣬹��캯�����Զ����ã�����ֻ����һ��
    Person()
    {
        cout << "Person ���캯���ĵ���" << endl;
    }

    //Destructor
    //�������������в��������ᷢ������
    //�ͷŶ����ʱ�����������Ż���ã�ֻ����һ��
    ~Person()
    {
        cout << "Person ���������ĵ���" << endl;
    }
};

//����������Ǳ����е�ʵ�飬��������Լ����ṩ�����������ṩһ����ʵ�ֵĹ��������
void test01()
{
    Person p; //ջ������(�ֲ�����)��test01ִ����Ϻ��ͷ��������
}

int main()
{
    test01();

    //Person p; //�����˿̲������ͷţ�Ҫ�ȵ�main�����Ż��ͷţ�Ҳֻ�ܵ��Ǹ�ʱ��Ż������������

    system("pause");
    return 0;
}

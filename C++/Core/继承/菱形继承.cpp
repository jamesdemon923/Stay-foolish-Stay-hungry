#include<iostream>

using namespace std;

//������
class Animal
{
    public:
    int m_Age;

};


//������̳п��Խ������
//�̳�֮ǰ����virtual��Ϊ ��̳�
//Animal��Ϊ �����
//����
class Sheep:virtual public Animal
{

};

//����
class Camel:virtual public Animal
{

};

//������
class Alpaca:public Sheep, public Camel
{

};

void test01()
{
    Alpaca alpaca;
    alpaca.Sheep::m_Age = 18;
    alpaca.Camel::m_Age = 28; 
    //�����μ̳У���������ӵ����ͬ���ݣ����������������
    //���μ̳е������������ݣ���Դ�˷� 
    //תΪ��̳�֮�����ݹ����ˣ�ֻ��һ��������
    cout << "alpaca.Sheep::m_Age = " << alpaca.Sheep::m_Age << endl;
    cout << "alpaca.Camel::m_Age = " << alpaca.Camel::m_Age << endl;
    cout << "alpaca.m_Age = " << alpaca.m_Age << endl;


}

int main()
{
    test01();
    system("pause");
    return 0;
}
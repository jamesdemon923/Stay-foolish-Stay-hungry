#include<iostream>

using namespace std;

class Animal
{
    public:

    virtual void speak()
    {
        cout << "������˵��" << endl;
    }
};

class Cat:public Animal
{
    public:
    //��д ��������ֵ���� ������ �����б� ��ȫ��ͬ
    void speak()
    {
        cout << "MewMew" << endl;
    }
};

class Dog:public Animal
{
    public:
    void speak()
    {
        cout << "BarkBark" << endl;
    }
};

//��ַ��� ����׶ξ��Ѿ�ȷ��������ַ
//�������è˵������ַ��������

//��̬��̬��������
//1���м̳й�ϵ
//2��������д�����麯��

//��̬��̬ʹ��
//�����ָ��������� ִ���������

//�ײ�ԭ���γ���vfptrָ���麯��������̳и����vfptr���麯��������д֮�󣬻��γ��Լ��������µ��麯��

void doSpeak(Animal &animal)
{
    animal.speak();
}

test01()
{
    Cat cat;
    doSpeak(cat);

    Dog dog;
    doSpeak(dog);

}

test02()
{
    cout << "size of Animal = " << sizeof(Animal) << endl;
}

int main()
{
    test02();

    system("pause");
    return 0;
}
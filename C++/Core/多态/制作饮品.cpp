#include<iostream>

using namespace std;

class AbstractDrinking
{
public:

    //��ˮ
    virtual void Boil() = 0;

    //����
    virtual void Brew() = 0;

    //���뱭��
    virtual void PourInCup() = 0;

    //���븨��
    virtual void AddIngredient() = 0;

    //������Ʒ
    virtual void MakeDrinking()
    {
        cout << "��������:" << endl;
        Boil();
        Brew();
        PourInCup();
        AddIngredient();
    }
};

class Coffee:public AbstractDrinking
{
public:

    //��ˮ
    virtual void Boil()
    {
        cout << "��ˮ" << endl;
    }

    //����
    virtual void Brew()
    {
        cout << "���ݿ���" << endl;
    }

    //���뱭��
    virtual void PourInCup()
    {
        cout << "���뱭��" << endl;
    }

    //���븨��
    virtual void AddIngredient()
    {
        cout << "�����Ǻ�ţ��" << endl;
    }
};

class Tea:public AbstractDrinking
{
public:

    //��ˮ
    virtual void Boil()
    {
        cout << "��ˮ" << endl;
    }

    //����
    virtual void Brew()
    {
        cout << "���ݲ�" << endl;
    }

    //���뱭��
    virtual void PourInCup()
    {
        cout << "���뱭��" << endl;
    }

    //���븨��
    virtual void AddIngredient()
    {
        cout << "�������" << endl;
    }
};

void doWork(AbstractDrinking * abs)
{
    abs->MakeDrinking();
    delete abs;//�ͷţ���ֹ�ڴ�й©
}

void test01()
{
    doWork(new Coffee);
    cout << "----------" << endl;
    doWork(new Tea);
}

int main()
{
    test01();
    system("pause");
    return 0;
}
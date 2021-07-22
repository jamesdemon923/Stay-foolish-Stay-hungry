#include<iostream>

using namespace std;

class AbstractDrinking
{
public:

    //煮水
    virtual void Boil() = 0;

    //冲泡
    virtual void Brew() = 0;

    //倒入杯中
    virtual void PourInCup() = 0;

    //加入辅料
    virtual void AddIngredient() = 0;

    //制作饮品
    virtual void MakeDrinking()
    {
        cout << "步骤如下:" << endl;
        Boil();
        Brew();
        PourInCup();
        AddIngredient();
    }
};

class Coffee:public AbstractDrinking
{
public:

    //煮水
    virtual void Boil()
    {
        cout << "煮开水" << endl;
    }

    //冲泡
    virtual void Brew()
    {
        cout << "冲泡咖啡" << endl;
    }

    //倒入杯中
    virtual void PourInCup()
    {
        cout << "倒入杯中" << endl;
    }

    //加入辅料
    virtual void AddIngredient()
    {
        cout << "加入糖和牛奶" << endl;
    }
};

class Tea:public AbstractDrinking
{
public:

    //煮水
    virtual void Boil()
    {
        cout << "煮开水" << endl;
    }

    //冲泡
    virtual void Brew()
    {
        cout << "冲泡茶" << endl;
    }

    //倒入杯中
    virtual void PourInCup()
    {
        cout << "倒入杯中" << endl;
    }

    //加入辅料
    virtual void AddIngredient()
    {
        cout << "加入枸杞" << endl;
    }
};

void doWork(AbstractDrinking * abs)
{
    abs->MakeDrinking();
    delete abs;//释放，防止内存泄漏
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
#include<iostream>

using namespace std;

//动物类
class Animal
{
    public:
    int m_Age;

};


//利用虚继承可以解决问题
//继承之前加上virtual变为 虚继承
//Animal称为 虚基类
//羊类
class Sheep:virtual public Animal
{

};

//驼类
class Camel:virtual public Animal
{

};

//羊驼类
class Alpaca:public Sheep, public Camel
{

};

void test01()
{
    Alpaca alpaca;
    alpaca.Sheep::m_Age = 18;
    alpaca.Camel::m_Age = 28; 
    //当菱形继承，两个父类拥有相同数据，需加以作用域区分
    //菱形继承导致数据有两份，资源浪费 
    //转为虚继承之后，数据共享了，只有一份数据了
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
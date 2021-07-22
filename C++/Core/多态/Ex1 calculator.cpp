#include<iostream>
#include<string>
using namespace std;

class Calculator
{
    public:
    int m_Num1;
    int m_Num2;

    int getResult(string oper)
    {
        if (oper == "+")
        {
            return m_Num1 + m_Num2;
        }
        else if (oper == "-")
        {
            return m_Num1 - m_Num2;
        }
        else if (oper == "*")
        {
            return m_Num1 * m_Num2;
        }

        //实际开发中，开闭原则：对扩展进行开放，对修改进行关闭
    }
};

void test01()
{
    Calculator c;
    c.m_Num1 = 10;
    c.m_Num2 = 10;

    cout << c.m_Num1 << " + " << c.m_Num2 << " = " << c.getResult("+") << endl;
    cout << c.m_Num1 << " - " << c.m_Num2 << " = " << c.getResult("-") << endl;
    cout << c.m_Num1 << " * " << c.m_Num2 << " = " << c.getResult("*") << endl;
}

//利用多态实现计算器

//多态好处
//1、组织结构清晰
//2、可读性强
//3、对于前期和后期扩展及维护性高
//实现计算器抽象类
class AbstractCalculator
{
    public:
    virtual int getResult()
    {
        return 0;
    }

    int m_Num1;
    int m_Num2;

};

//加法计算器类
class AddCalculator :public AbstractCalculator
{
    public:

    int getResult()
    {
        return m_Num1 + m_Num2;
    }

};

//减法计算器类
class SubCalculator :public AbstractCalculator
{
    public:

    int getResult()
    {
        return m_Num1 - m_Num2;
    }

};

//乘法计算器类
class MulCalculator :public AbstractCalculator
{
    public:

    int getResult()
    {
        return m_Num1 * m_Num2;
    }

};

void test02()
{
    //多态使用条件
    //父类指针或者引用指向子类对象

    //加法运算
    AbstractCalculator * abc = new AddCalculator;//指针形式
    abc->m_Num1 = 100;
    abc->m_Num2 = 10;

    cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;
    //用完记得销毁
    delete abc;

    //减法运算
    abc = new SubCalculator;//指针形式
    abc->m_Num1 = 100;
    abc->m_Num2 = 100;

    cout << abc->m_Num1 << " - " << abc->m_Num2 << " = " << abc->getResult() << endl;

    delete abc;

    //乘法运算
    abc = new MulCalculator;//指针形式
    abc->m_Num1 = 100;
    abc->m_Num2 = 100;

    cout << abc->m_Num1 << " * " << abc->m_Num2 << " = " << abc->getResult() << endl;
}

int main()
{
    test02();
    system("pause");
    return 0;
}
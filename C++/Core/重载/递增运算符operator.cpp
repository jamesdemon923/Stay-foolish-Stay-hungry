#include<iostream>

using namespace std;


class MyIntegar
{
    friend ostream & operator<<(ostream& cout,MyIntegar myint);

public:
    MyIntegar()
    {
        m_Num = 0;
    }

    //重载前置++运算符
    //返回引用是为一直对一个数据进行递增
    MyIntegar& operator++()
    {
        m_Num++;
        return *this;
    }
    //重载后置++运算符
    //void operator++(int) int代表占位参数，用于区分前置和后置
    //必须返回值，因为temp用完就被释放，就无法返回引用了
    MyIntegar operator++(int)
    {
        MyIntegar temp = *this;
        m_Num++;
        return temp;
    }



private:
    int m_Num;

};

//重载左移运算符
ostream & operator<<(ostream& cout,MyIntegar myint)
{
    cout << myint.m_Num;
    return cout;
}

void test01()
{
    MyIntegar myint;
    cout << ++(++myint) << endl;
    cout << myint << endl;
}

void test02()
{
    MyIntegar myint;
    cout << myint++ << endl;
    cout << myint << endl;
}

int main()
{
    test02();
    system("pause");
    return 0;
}
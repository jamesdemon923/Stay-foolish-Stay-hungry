#include<iostream>

using namespace std;

class MyIntegar
{
    friend ostream & operator<<(ostream & cout, MyIntegar myint);
    public:
    MyIntegar()
    {
        m_Num = 0;
    }

    //Ç°ÖÃ
    MyIntegar& operator--()
    {
        m_Num--;
        return *this;
    }

    //ºóÖÃ
    MyIntegar operator--(int)
    {
        MyIntegar temp = *this;
        m_Num--;
        return temp;
    }
    private:

    int m_Num;

};
ostream & operator<<(ostream & cout, MyIntegar myint)
{
    cout << myint.m_Num;
    return cout;
}

void test01()
{
    MyIntegar myint;
    cout << --(--myint) << endl;
    cout << myint << endl;
}

void test02()
{
    MyIntegar myint;
    cout << myint-- << endl;
    cout << myint << endl;
}

int main()
{
    test02();
    system("pause");
    return 0;
}
#include<iostream>

using namespace std;

//类的默认权限是private
class C1
{
    int m_A;
};

//结构体的默认权限是public
struct C2
{
    int m_B;
};

int main()
{
    C1 c1;
    //c1.m_A = 100; 私有权限无法访问
    C2 c2;
    c2.m_B = 200;//公共权限可以访问
    system("pause");
    return 0;
}
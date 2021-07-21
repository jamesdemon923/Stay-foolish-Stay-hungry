#include<iostream>

using namespace std;

class Base1
{
public:
    int m_A;
protected:
    int m_B;
private:
    int m_C;
};

//公共继承
class Son1:public Base1
{
public:
    void func()
    {
        m_A = 10;//父类 公共权限成员 到子类 依然是公共权限
        m_B = 10;//父类 保护权限成员 到子类 依然是保护权限
    }
};

void test01()
{
    Son1 s1;
    s1.m_A = 100;
    //s1.m_B = 100;保护权限，类外无法访问
}

//保护继承
class Son2:protected Base1
{
public:
    void func()
    {
        m_A = 10;//父类 公共权限成员 到子类 变为保护权限
        m_B = 10;//父类 保护权限成员 到子类 仍然是保护权限
    }
};

void test02()
{
    Son2 s2;
    //s2.m_A = 100;保护权限，类外无法访问
    //s2.m_B = 100;保护权限，类外无法访问
}

//私有继承
class Son3:protected Base1
{
public:
    void func()
    {
        m_A = 10;//父类 公共权限成员 到子类 变为私有权限
        m_B = 10;//父类 保护权限成员 到子类 仍然是私有权限
    }
};

class GrandSon3:public Son3
{
public:
    void func()
    {
        //m_A = 10;//已经是私有权限了，访问不到
        //m_B = 10;//已经是私有权限了，访问不到
    }
};


void test03()
{
    Son3 s3;
    //s3.m_A = 100;私有权限，类外无法访问
    //s3.m_B = 100;私有权限，类外无法访问
}

int main()
{
    test01();
    system("pause");
    return 0;
}
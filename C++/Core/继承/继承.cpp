#include<iostream>

using namespace std;

/* 
//普通实现页面

//Java页面
class Java
{
    public:
    void header()
    {
        cout << "公共头部" << endl;
    }

    void footer()
    {
        cout << "公共底部" << endl;
    }
    void left()
    {
        cout << "公共分类列表" << endl;
    }
    void content()
    {
        cout << "Java videos" << endl;
    }
};

//Python页面
class Python
{
    public:
    void header()
    {
        cout << "公共头部" << endl;
    }

    void footer()
    {
        cout << "公共底部" << endl;
    }
    void left()
    {
        cout << "公共分类列表" << endl;
    }
    void content()
    {
        cout << "Python videos" << endl;
    }
};

//CPP页面
class CPP
{
    public:
    void header()
    {
        cout << "公共头部" << endl;
    }

    void footer()
    {
        cout << "公共底部" << endl;
    }
    void left()
    {
        cout << "公共分类列表" << endl;
    }
    void content()
    {
        cout << "CPP videos" << endl;
    }
}; 
*/

//继承实现
//语法：class 子类:继承方式 父类
//子类也称为派生类
//父类也称为基类
class BasePage
{
    public:
    void header()
    {
        cout << "公共头部" << endl;
    }

    void footer()
    {
        cout << "公共底部" << endl;
    }
    void left()
    {
        cout << "公共分类列表" << endl;
    }

};

//Java页面
class Java:public BasePage
{
    public:
    void content()
    {
        cout << "Java videos" << endl;
    }
};

//Python页面
class Python:public BasePage
{
    public:
    void content()
    {
        cout << "Python videos" << endl;
    }
};

//CPP页面
class CPP:public BasePage
{
    public:
    void content()
    {
        cout << "CPP videos" << endl;
    }
};



void test01()
{
    cout << "Java页面如下" << endl;
    Java ja;
    ja.header();
    ja.footer();
    ja.left();
    ja.content();

    cout << "------------" << endl;

    cout << "Python页面如下" << endl;
    Python py;
    py.header();
    py.footer();
    py.left();
    py.content();

    cout << "------------" << endl;

    cout << "CPP页面如下" << endl;
    CPP cpp;
    cpp.header();
    cpp.footer();
    cpp.left();
    cpp.content();


}
int main()
{
    test01();

    system("pause");
    return 0;
}
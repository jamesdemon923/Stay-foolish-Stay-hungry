#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//二进制文件 写文件
class Person
{
    public:

    char m_Name[64];
    int m_Age;
};

void test01()
{

    //1、包含头文件

    //2、创建流对象
    ofstream ofs("person.txt",ios::out|ios::binary);

    //3、打开文件 可以和2合在一起
    //ofs.open("person.txt",ios::out|ios::binary);

    //4、写文件
    Person p = {"James", 18};
    ofs.write((const char*)&p, sizeof(Person));

    //5、关闭文件
    ofs.close();
}

int main()
{
    test01();
    system("pause");
    return 0;
}

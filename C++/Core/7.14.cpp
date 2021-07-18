#include<iostream>
#include<string>
using namespace std;

class Student
{
public:

//类中的属性和行为 统一称为 成员
//属性 成员属性 成员变量
//行为 成员函数 成员方法
    int s_ID;
    string s_Name;

    void showStudent()
    {
    cout << "姓名为：" << s_Name << "\t学号为：" << s_ID << endl;
    }

    void setName(string name)
    {
        s_Name = name;
    }

    void setName(int id)
    {
        s_ID = id;
    }
//保护和私有权限，类外均不可访问，但保护权限父类可以被子类访问
protected:
    int s_age;

private:
    int s_score;
};

int main()
{

    //实例化
    Student s1;
    s1.s_ID;
    s1.s_Name;

    cout << "请输入4位学号" << endl;
    cin >> s1.s_ID;

    cout << "请输入学生的姓名" << endl;
    cin >> s1.s_Name;

    s1.setName("Xu");
    s1.setID("0001");

    s1.showStudent();
    system("pause");
    return 0;
}
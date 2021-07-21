#include<iostream>
#include<string>
using namespace std;

class Building
{
    //GoodFriend全局函数是Building好朋友，可以访问Building私有成员
    //key sentence!!!!
    friend void GoodFriend(Building& building);
    
public:

    Building()
    {
        m_SittingRoom = "客厅";
        m_BedRoom = "卧室";
    }


    string m_SittingRoom;//客厅

private:
    string m_BedRoom;//卧室
};

//全局函数
void GoodFriend(Building& building)
{
    cout << "好朋友的全局函数 正在访问: " << building.m_SittingRoom << endl;
    cout << "好朋友的全局函数 正在访问: " << building.m_BedRoom << endl;
}

void test01()
{
    Building building;
    GoodFriend(building);
}

int main()
{
    test01();
    system("pause");
    return 0;
}
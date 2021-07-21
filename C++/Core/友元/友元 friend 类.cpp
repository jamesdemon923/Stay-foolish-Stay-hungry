#include<iostream>
#include<string>
using namespace std;

class Building
{
    //key sentence!!!!
    friend class GoodFriend;
public:
    Building();
    string m_SittingRoom;

private:
    string m_BedRoom;
};


class GoodFriend
{
public:

    GoodFriend();

    void visit();//参观函数 访问Building中的属性

    Building * building;

};

//类外实现成员函数
Building::Building()
{
    m_SittingRoom = "客厅";
    m_BedRoom = "卧室";
}

GoodFriend::GoodFriend()
{
    building = new Building;
}

void GoodFriend::visit()
{
    cout << "GoodFriend 正在访问: " << building->m_SittingRoom << endl;

    cout << "GoodFriend 正在访问: " << building->m_BedRoom << endl;
}

void test01()
{
    GoodFriend gg;
    gg.visit();

}

int main()
{
    test01();
    system("pause");
    return 0;
}
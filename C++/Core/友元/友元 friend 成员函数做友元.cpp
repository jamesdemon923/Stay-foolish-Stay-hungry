#include<iostream>

using namespace std;

class Building;

class GoodFriend
{
    public:
    GoodFriend();

    void visit();
    void visit2();

    Building * building;
};

class Building
{
    //tell compiler，the memeber function "visit" in class GoodFriend can visit the private member in class Building
    //key sentence!!!!
    friend void GoodFriend::visit();
public:
    Building();

    string m_SittingRoom;

private:
    string m_BedRoom;

};
//Building构造函数
Building::Building()
{
    m_SittingRoom = "Sitting room";
    m_BedRoom = "Bedroom";
}
//GoodFriend构造函数
GoodFriend::GoodFriend()
{
    building = new Building;
}

void GoodFriend::visit()
{
    cout << "GoodFriend 通过visit 函数 正在访问 " << building->m_SittingRoom << endl;

    cout << "GoodFriend 通过visit 函数 正在访问 " << building->m_BedRoom << endl;
}

void GoodFriend::visit2()
{
    cout << "GoodFriend 通过visit2 函数 正在访问 " << building->m_SittingRoom << endl;

    //cout << "GoodFriend 通过visit2 函数 正在访问 " << building->m_BedRoom << endl;
}

void test01()
{
    GoodFriend gg;
    gg.visit();
    gg.visit2();
}

int main()
{
    test01();
    system("pause");
    return 0;
}
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

    void visit();//�ιۺ��� ����Building�е�����

    Building * building;

};

//����ʵ�ֳ�Ա����
Building::Building()
{
    m_SittingRoom = "����";
    m_BedRoom = "����";
}

GoodFriend::GoodFriend()
{
    building = new Building;
}

void GoodFriend::visit()
{
    cout << "GoodFriend ���ڷ���: " << building->m_SittingRoom << endl;

    cout << "GoodFriend ���ڷ���: " << building->m_BedRoom << endl;
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
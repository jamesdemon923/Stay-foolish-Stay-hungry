#include<iostream>
#include<string>
using namespace std;

class Building
{
    //GoodFriendȫ�ֺ�����Building�����ѣ����Է���Building˽�г�Ա
    //key sentence!!!!
    friend void GoodFriend(Building& building);
    
public:

    Building()
    {
        m_SittingRoom = "����";
        m_BedRoom = "����";
    }


    string m_SittingRoom;//����

private:
    string m_BedRoom;//����
};

//ȫ�ֺ���
void GoodFriend(Building& building)
{
    cout << "�����ѵ�ȫ�ֺ��� ���ڷ���: " << building.m_SittingRoom << endl;
    cout << "�����ѵ�ȫ�ֺ��� ���ڷ���: " << building.m_BedRoom << endl;
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
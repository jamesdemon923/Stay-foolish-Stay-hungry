#include<iostream>
#include<string>
using namespace std;

class Student
{
public:

//���е����Ժ���Ϊ ͳһ��Ϊ ��Ա
//���� ��Ա���� ��Ա����
//��Ϊ ��Ա���� ��Ա����
    int s_ID;
    string s_Name;

    void showStudent()
    {
    cout << "����Ϊ��" << s_Name << "\tѧ��Ϊ��" << s_ID << endl;
    }

    void setName(string name)
    {
        s_Name = name;
    }

    void setName(int id)
    {
        s_ID = id;
    }
//������˽��Ȩ�ޣ���������ɷ��ʣ�������Ȩ�޸�����Ա��������
protected:
    int s_age;

private:
    int s_score;
};

int main()
{

    //ʵ����
    Student s1;
    s1.s_ID;
    s1.s_Name;

    cout << "������4λѧ��" << endl;
    cin >> s1.s_ID;

    cout << "������ѧ��������" << endl;
    cin >> s1.s_Name;

    s1.setName("Xu");
    s1.setID("0001");

    s1.showStudent();
    system("pause");
    return 0;
}
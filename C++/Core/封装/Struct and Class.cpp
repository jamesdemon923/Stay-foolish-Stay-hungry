#include<iostream>

using namespace std;

//���Ĭ��Ȩ����private
class C1
{
    int m_A;
};

//�ṹ���Ĭ��Ȩ����public
struct C2
{
    int m_B;
};

int main()
{
    C1 c1;
    //c1.m_A = 100; ˽��Ȩ���޷�����
    C2 c2;
    c2.m_B = 200;//����Ȩ�޿��Է���
    system("pause");
    return 0;
}
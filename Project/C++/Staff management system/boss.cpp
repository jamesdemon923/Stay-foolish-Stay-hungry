#include "boss.h"

Boss::Boss(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//������Ϣ
void Boss::showInfo()
{
	cout << "ְ�����: " << this->m_ID
		<< "\tְ������: " << this->m_Name
		<< "\t��λ: " << this->gerDeptName()
		<< "\t��λְ��:����˾��������" << endl;
}

//��λ����
string Boss::gerDeptName()
{
	return string("�ܲ�");
}
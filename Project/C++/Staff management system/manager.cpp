#include "manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//������Ϣ
void Manager::showInfo()
{
	cout << "ְ�����: " << this->m_ID
		<< "\tְ������: " << this->m_Name
		<< "\t��λ: " << this->gerDeptName()
		<< "\t��λְ��:����ϰ彻�������񣬲��·������Ա��" << endl;
}

//��λ����
string Manager::gerDeptName()
{
	return string("����");
}
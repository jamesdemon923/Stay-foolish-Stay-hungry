#include "employee.h"

Employee::Employee(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//������Ϣ
void Employee::showInfo()
{
	cout << "ְ�����: " << this->m_ID
		 << "\tְ������: " << this->m_Name
		 << "\t��λ: " << this->gerDeptName()
		 << "\t��λְ��:��ɾ�����������" << endl;
}

//��λ����
string Employee::gerDeptName()
{
	return string("Ա��");
}
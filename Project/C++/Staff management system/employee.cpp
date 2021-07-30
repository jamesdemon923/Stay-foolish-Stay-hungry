#include "employee.h"

Employee::Employee(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//个人信息
void Employee::showInfo()
{
	cout << "职工编号: " << this->m_ID
		 << "\t职工姓名: " << this->m_Name
		 << "\t岗位: " << this->gerDeptName()
		 << "\t岗位职责:完成经理交给的任务" << endl;
}

//岗位名称
string Employee::gerDeptName()
{
	return string("员工");
}
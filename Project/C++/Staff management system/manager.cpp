#include "manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dId;
}

//个人信息
void Manager::showInfo()
{
	cout << "职工编号: " << this->m_ID
		<< "\t职工姓名: " << this->m_Name
		<< "\t岗位: " << this->gerDeptName()
		<< "\t岗位职责:完成老板交给的任务，并下发任务给员工" << endl;
}

//岗位名称
string Manager::gerDeptName()
{
	return string("经理");
}
#pragma once
#include <iostream>
using namespace std;
#include <string>

//职工抽象类
class Worker
{
public:

	//个人信息
	virtual void showInfo() = 0;

	//岗位名称
	virtual string gerDeptName() = 0;


	int m_ID;
	string m_Name;
	int m_DeptID;
};

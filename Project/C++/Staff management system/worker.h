#pragma once
#include <iostream>
using namespace std;
#include <string>

//ְ��������
class Worker
{
public:

	//������Ϣ
	virtual void showInfo() = 0;

	//��λ����
	virtual string gerDeptName() = 0;


	int m_ID;
	string m_Name;
	int m_DeptID;
};

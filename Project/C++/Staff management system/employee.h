#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Employee :public Worker
{
public:

	Employee(int id, string name, int dId);

	//个人信息
	virtual void showInfo();

	//岗位名称
	virtual string gerDeptName();

};
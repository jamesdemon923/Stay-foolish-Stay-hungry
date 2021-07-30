#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Manager :public Worker
{
public:

	Manager(int id, string name, int dId);

	//个人信息
	virtual void showInfo();

	//岗位名称
	virtual string gerDeptName();
};
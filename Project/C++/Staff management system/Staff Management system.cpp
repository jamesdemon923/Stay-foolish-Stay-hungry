#include<iostream>
#include "workerManager.h"

using namespace std;

int main()
{

	//实例化管理者对象
	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://增加信息
			wm.Add_Emp();
			break;
		case 2://显示信息
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改信息
			wm.Mod_Emp();
			break;
		case 5://查找信息
			wm.Find_Emp();
			break;
		case 6://进行排序
			wm.Sort_Emp();
			break;
		case 7://清空文档
			wm.Clean_File();
			break;
		default:
			system("cls");//清屏操作
			break;
		}

	}

	system("pause");
	return 0;
}
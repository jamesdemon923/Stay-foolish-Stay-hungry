#include "workerManager.h"

WorkerManager::WorkerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	int num = this->get_EmpNum();
	//cout << "职工人数为多少: " << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker *[this->m_EmpNum];
	//将文件中的数据存到数组中
	this->init_Emp();
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

//展示函数
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加的职工数量: " << endl;

	int addNum = 0;//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间 = 原来记录的人数 + 新增人数

		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int ID;
			string name;
			int dSelect;
			cout << "请输入第 " << i + 1 << " 个新职工的编号: " << endl;
			cin >> ID;
			cout << "请输入第 " << i + 1 << " 个新职工的姓名: " << endl;
			cin >> name;
			cout << "请选择该职工的岗位 " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(ID, name, 1);
				break;
			case 2:
				worker = new Manager(ID, name, 2);
				break;
			case 3:
				worker = new Boss(ID, name, 3);
				break;
			default:
				break;
			}
			//创建的职工指针，保存在数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空
		this->m_FileIsEmpty = false;

		//保存数据到文件中
		this->save();

		//提示添加成功
		cout << "成功添加 " << addNum << " 位职工！" << endl;

	}
	else
	{
		cout << "输入数据有误" << endl;
	}

	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//将每个人数据写入文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}

	ofs.close();
}

//统计文件人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int ID;
	string name;
	int dId;

	int num = 0;

	while (ifs >> ID && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

//初始化职工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int ID;
	string name;
	int dId;

	int index = 0;

	while (ifs >> ID && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;

		if (dId == 1) //普通员工
		{
			worker = new Employee(ID, name, dId);
		}
		else if (dId == 2) //经理
		{
			worker = new Manager(ID, name, dId);
		}
		else if (dId == 3) //老板
		{
			worker = new Boss(ID, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int ID)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == ID)
		{
			index = i;

			break;
		}
	}
	return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入想要删除职工编号" << endl;
		int ID = 0;
		cin >> ID;

		int index = this->IsExist(ID);

		if (index != -1)
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录人员个数
			this->save();//同步到文件中
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入想要修改职工编号" << endl;
		int ID = 0;
		cin >> ID;
		int ret = this->IsExist(ID);
		if (ret != -1)
		{
			//查找到该人

			delete this->m_EmpArray[ret];

			int newID = 0;
			string newName = " ";
			int dSelect = 0;
			cout << "查到: " << ID << "号职工，请输入新职工号: " << endl;
			cin >> newID;

			cout << "请输入新姓名: " << endl;
			cin >> newName;

			cout << "请输入岗位: " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case1:
				worker = new Employee(newID, newName, dSelect);
				break;
			case2:
				worker = new Manager(newID, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newID, newName, dSelect);
				break;
			default:
				break;
			}

			//更改数据 到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}

	//按任意键 清屏
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //按职工号查找
		{
			int ID;
			cout << "请输入查找的职工编号：" << endl;
			cin >> ID;

			int ret = IsExist(ID);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_ID
						<< " 号的信息如下：" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;


		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (m_EmpArray[minOrMax]->m_ID > m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else  //降序
				{
					if (m_EmpArray[minOrMax]->m_ID < m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Worker * temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}

		}

		cout << "排序成功,排序后结果为：" << endl;
		this->save();
		this->Show_Emp();
	}
	system("pause");
	system("cls");
}

//清空文件
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}
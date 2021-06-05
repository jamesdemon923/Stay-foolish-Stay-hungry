#include<iostream>
#include <string>
#define MAX 1000
using namespace std;

//菜单界面
void showMenu()
{
	cout << "******************************" << endl;
	cout << "*****  1.Add Contact     *****" << endl;
	cout << "*****  2.Show Contact    *****" << endl;
	cout << "*****  3.Delete Contact  *****" << endl;
	cout << "*****  4.Search Contact  *****" << endl;
	cout << "*****  5.Modify Contact  *****" << endl;
	cout << "*****  6.Format Contact  *****" << endl;
	cout << "*****  0.Exit Directory  *****" << endl;
	cout << "******************************" << endl;
}

struct Person
{
	string m_Name; //姓名
	int m_Sex; //性别：1男 0女
	int m_Age; //年龄
	string m_Phone; //电话
	string m_Addr; //住址
};

struct Addressbooks
{
	struct Person personArray[MAX]; //通讯录中保存的联系人数组
	int m_Size; //通讯录中人员个数
};

void addPerson(Addressbooks *abs)
{
	//判断电话本是否满了
	if (abs->m_Size == MAX)
	{
		cout << "Sorry, the directory is full." << endl;
		return;
	}
	else
	{
		//姓名
		string name;
		cout << "Please enter the name:" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		cout << "Please enter the gender:" << endl;
		cout << "1 -- Male" << endl;
		cout << "0 -- Female" << endl;

		//性别
		int sex = 0;
		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 0)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "Please enter the right number";
		}

		//年龄
		cout << "Please enter the age:" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//联系电话
		cout << "Please enter the telephone:" << endl;
		string phone = "";
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//家庭住址
		cout << "Please enter the address:" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//更新通讯录人数
		abs->m_Size++;

		cout << "Success!" << endl;
		system("pause");
		system("cls");
	}
}

void showPerson(Addressbooks * abs)
{
	if (abs->m_Size == 0)
	{
		cout << "The directory is empty." << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "Name:" << abs->personArray[i].m_Name << "\t";
			cout << "Gender:" << (abs->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";
			cout << "Age:" << abs->personArray[i].m_Age << "\t";
			cout << "Telephone:" << abs->personArray[i].m_Phone << "\t";
			cout << "Address:" << abs->personArray[i].m_Addr << endl;
		}
	}
	
	system("pause");
	system("cls");

}

//判断是否存在查询的人员，存在返回在数组中索引位置，不存在返回-1
int isExist(Addressbooks * abs, string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (abs->personArray[i].m_Name == name)
		{
			return i;
		}
	}
	return -1;
}

void deletePerson(Addressbooks * abs)
{
	cout << "Please enter the name:" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);
	if (ret != -1)
	{
		for (int i = ret; i < abs->m_Size; i++)
		{
			abs->personArray[i] = abs->personArray[i + 1];
		}
         abs->m_Size--;
		cout << "Success!" << endl;
	}
	else
	{
		cout << "Not exist" << endl;
	}

	system("pause");
	system("cls");
}

void findPerson(Addressbooks * abs)
{
	cout << "Please enter the name:" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);
	if (ret != -1)
	{
		cout << "Name:" << abs->personArray[ret].m_Name << "\t";
		cout << "Gender:" << abs->personArray[ret].m_Sex << "\t";
		cout << "Age:" << abs->personArray[ret].m_Age << "\t";
		cout << "Telephone:" << abs->personArray[ret].m_Phone << "\t";
		cout << "Address:" << abs->personArray[ret].m_Addr << endl;
	}
	else
	{
		cout << "Not exist" << endl;
	}

	system("pause");
	system("cls");

}

void modifyPerson(Addressbooks * abs)
{
	cout << "Please enter the name:" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);
	if (ret != -1)
	{
		//姓名
		string name;
		cout << "Please enter the NEW name:" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		//性别
		cout << "Please enter the NEW gender:" << endl;
		cout << "1 -- Male" << endl;
		cout << "0 -- Female" << endl;
		int sex = 0;
		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 0)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "Please enter the right number";
		}

        //年龄
		cout << "Please enter the NEW age:" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[ret].m_Age = age;

		//联系电话
		cout << "Please enter the NEW telephone:" << endl;
		string phone = "";
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;
		//家庭住址
		cout << "Please enter the NEW address:" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Addr = address;
		cout << "Success!" << endl;
	}
	else
	{
		cout << "Not exist" << endl;
	}

	system("pause");
	system("cls");

}

void cleanPerson(Addressbooks * abs)
{
	abs->m_Size = 0;
	cout << "The directory has been empty" << endl;
	system("pause");
	system("cls");
}

int main() {


	//创建通讯录
	Addressbooks abs;
	abs.m_Size = 0;

	int select = 0;
	while (true)
	{
	    showMenu();
		cin >> select;
		
		switch (select)
		{
		case 1:  //添加联系人
		    addPerson(&abs);
			break;
		case 2:  //显示联系人
			showPerson(&abs);
			break;
		case 3:  //删除联系人
		    deletePerson(&abs);
			break;
		case 4:  //查找联系人
		    findPerson(&abs);
			break;
		case 5:  //修改联系人
		    modifyPerson(&abs);
			break;
		case 6:  //清空联系人
		    cleanPerson(&abs);
			break;
		case 0:  //退出通讯录
			cout << "See you next time" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	system("pause");

	return 0;
}

#include<iostream>
#include <string>
#define MAX 1000
using namespace std;

//�˵�����
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
	string m_Name; //����
	int m_Sex; //�Ա�1�� 0Ů
	int m_Age; //����
	string m_Phone; //�绰
	string m_Addr; //סַ
};

struct Addressbooks
{
	struct Person personArray[MAX]; //ͨѶ¼�б������ϵ������
	int m_Size; //ͨѶ¼����Ա����
};

void addPerson(Addressbooks *abs)
{
	//�жϵ绰���Ƿ�����
	if (abs->m_Size == MAX)
	{
		cout << "Sorry, the directory is full." << endl;
		return;
	}
	else
	{
		//����
		string name;
		cout << "Please enter the name:" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		cout << "Please enter the gender:" << endl;
		cout << "1 -- Male" << endl;
		cout << "0 -- Female" << endl;

		//�Ա�
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

		//����
		cout << "Please enter the age:" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//��ϵ�绰
		cout << "Please enter the telephone:" << endl;
		string phone = "";
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//��ͥסַ
		cout << "Please enter the address:" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//����ͨѶ¼����
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
			cout << "Gender:" << (abs->personArray[i].m_Sex == 1 ? "��" : "Ů") << "\t";
			cout << "Age:" << abs->personArray[i].m_Age << "\t";
			cout << "Telephone:" << abs->personArray[i].m_Phone << "\t";
			cout << "Address:" << abs->personArray[i].m_Addr << endl;
		}
	}
	
	system("pause");
	system("cls");

}

//�ж��Ƿ���ڲ�ѯ����Ա�����ڷ���������������λ�ã������ڷ���-1
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
		//����
		string name;
		cout << "Please enter the NEW name:" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		//�Ա�
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

        //����
		cout << "Please enter the NEW age:" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[ret].m_Age = age;

		//��ϵ�绰
		cout << "Please enter the NEW telephone:" << endl;
		string phone = "";
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;
		//��ͥסַ
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


	//����ͨѶ¼
	Addressbooks abs;
	abs.m_Size = 0;

	int select = 0;
	while (true)
	{
	    showMenu();
		cin >> select;
		
		switch (select)
		{
		case 1:  //�����ϵ��
		    addPerson(&abs);
			break;
		case 2:  //��ʾ��ϵ��
			showPerson(&abs);
			break;
		case 3:  //ɾ����ϵ��
		    deletePerson(&abs);
			break;
		case 4:  //������ϵ��
		    findPerson(&abs);
			break;
		case 5:  //�޸���ϵ��
		    modifyPerson(&abs);
			break;
		case 6:  //�����ϵ��
		    cleanPerson(&abs);
			break;
		case 0:  //�˳�ͨѶ¼
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

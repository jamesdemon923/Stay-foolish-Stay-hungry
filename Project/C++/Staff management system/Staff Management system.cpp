#include<iostream>
#include "workerManager.h"

using namespace std;

int main()
{

	//ʵ���������߶���
	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://������Ϣ
			wm.Add_Emp();
			break;
		case 2://��ʾ��Ϣ
			wm.Show_Emp();
			break;
		case 3://ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4://�޸���Ϣ
			wm.Mod_Emp();
			break;
		case 5://������Ϣ
			wm.Find_Emp();
			break;
		case 6://��������
			wm.Sort_Emp();
			break;
		case 7://����ĵ�
			wm.Clean_File();
			break;
		default:
			system("cls");//��������
			break;
		}

	}

	system("pause");
	return 0;
}
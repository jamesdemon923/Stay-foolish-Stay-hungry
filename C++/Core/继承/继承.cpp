#include<iostream>

using namespace std;

/* 
//��ͨʵ��ҳ��

//Javaҳ��
class Java
{
    public:
    void header()
    {
        cout << "����ͷ��" << endl;
    }

    void footer()
    {
        cout << "�����ײ�" << endl;
    }
    void left()
    {
        cout << "���������б�" << endl;
    }
    void content()
    {
        cout << "Java videos" << endl;
    }
};

//Pythonҳ��
class Python
{
    public:
    void header()
    {
        cout << "����ͷ��" << endl;
    }

    void footer()
    {
        cout << "�����ײ�" << endl;
    }
    void left()
    {
        cout << "���������б�" << endl;
    }
    void content()
    {
        cout << "Python videos" << endl;
    }
};

//CPPҳ��
class CPP
{
    public:
    void header()
    {
        cout << "����ͷ��" << endl;
    }

    void footer()
    {
        cout << "�����ײ�" << endl;
    }
    void left()
    {
        cout << "���������б�" << endl;
    }
    void content()
    {
        cout << "CPP videos" << endl;
    }
}; 
*/

//�̳�ʵ��
//�﷨��class ����:�̳з�ʽ ����
//����Ҳ��Ϊ������
//����Ҳ��Ϊ����
class BasePage
{
    public:
    void header()
    {
        cout << "����ͷ��" << endl;
    }

    void footer()
    {
        cout << "�����ײ�" << endl;
    }
    void left()
    {
        cout << "���������б�" << endl;
    }

};

//Javaҳ��
class Java:public BasePage
{
    public:
    void content()
    {
        cout << "Java videos" << endl;
    }
};

//Pythonҳ��
class Python:public BasePage
{
    public:
    void content()
    {
        cout << "Python videos" << endl;
    }
};

//CPPҳ��
class CPP:public BasePage
{
    public:
    void content()
    {
        cout << "CPP videos" << endl;
    }
};



void test01()
{
    cout << "Javaҳ������" << endl;
    Java ja;
    ja.header();
    ja.footer();
    ja.left();
    ja.content();

    cout << "------------" << endl;

    cout << "Pythonҳ������" << endl;
    Python py;
    py.header();
    py.footer();
    py.left();
    py.content();

    cout << "------------" << endl;

    cout << "CPPҳ������" << endl;
    CPP cpp;
    cpp.header();
    cpp.footer();
    cpp.left();
    cpp.content();


}
int main()
{
    test01();

    system("pause");
    return 0;
}
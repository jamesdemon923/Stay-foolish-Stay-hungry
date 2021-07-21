#include<iostream>
#include"Circle.h"
#include"point.h"

using namespace std;

//�жϵ�λ�ú���
void isInCircle(Circle &c, Point &p)
{
    //��Բ�ĵľ���
    int distance =
    (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) +
    (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());
    //�뾶��ƽ��
    int rDistance = c.getR() * c.getR();
    //�жϹ�ϵ
    if (distance == rDistance)
    {
        cout << "����Բ��" << endl;
    }
    else if(distance < rDistance)
    {
        cout << "����Բ��" << endl;
    }
    else if(distance > rDistance)
    {
        cout << "����Բ��" << endl;
    }

}

int main()
{
    Circle c;
    c.setR(10);
    Point center;
    center.setX(10);
    center.setY(10);
    c.setCenter(center);

    Point p;
    p.setX(10);
    p.setY(10);

    isInCircle(c,p);

    system("pause");
    return 0;
}
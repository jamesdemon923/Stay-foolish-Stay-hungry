#include<iostream>
#include"Circle.h"
#include"point.h"

using namespace std;

//判断点位置函数
void isInCircle(Circle &c, Point &p)
{
    //到圆心的距离
    int distance =
    (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) +
    (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());
    //半径的平方
    int rDistance = c.getR() * c.getR();
    //判断关系
    if (distance == rDistance)
    {
        cout << "点在圆上" << endl;
    }
    else if(distance < rDistance)
    {
        cout << "点在圆内" << endl;
    }
    else if(distance > rDistance)
    {
        cout << "点在圆外" << endl;
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
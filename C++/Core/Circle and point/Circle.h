#pragma
#include<iostream>
#include"point.h"
using namespace std;

class Circle
{
public:
    void setR(int r);

    int getR();

    void setCenter(Point center);

    Point getCenter();


private:
    int m_R;

    //�����п�������һ������Ϊ��Ա
    Point m_Center;
};

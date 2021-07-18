#include<iostream>
#include<string>

using namespace std;

class Cube
{

public:
    //set L
    int setL(int l)
    {
        c_L = l;
    }
    //get L
    int getL()
    {
        return c_L;
    }

    //set W
    int setW(int w)
    {
        c_W = w;
    }
    //get W
    int getW()
    {
        return c_W;
    }

    //set H
    int setH(int h)
    {
        c_H = h;
    }
    //get H
    int getH()
    {
        return c_H;
    }

    //area
    int getArea()
    {
        return 2 * c_L * c_W + 2 * c_L * c_H + 2 * c_W * c_H;
    }
    //volume
    int getVolume()
    {
        return c_L * c_W * c_H;
    }

    bool isSameByClass(Cube &c)
    {
        if (c_L == c.getL() && c_W == c.getW() && c_H == c.getH())
        {
            return true;
            }
            return false;
        }

private:
    int c_L;
    int c_W;
    int c_H;
};

//判断真假是布尔函数
bool isSame(Cube &c1, Cube &c2)
{
    if (c1.getL() == c2.getL() && c1.getW() == c2.getW() && c1.getH() == c2.getH())
    {
        return true;
    }
    return false;
}

int main()
{
    Cube c1;
    c1.setL(10);
    c1.setW(10);
    c1.setH(10);

    cout << "c1's area is " << c1.getArea() << endl;
    cout << "c1's volume is " << c1.getVolume() << endl;   

    Cube c2;
    c2.setL(10);
    c2.setW(10);
    c2.setH(10);

    //利用全局函数判断c1和c2是否相等
    bool ret = isSame(c1,c2);
    if(ret)
    {
        cout << "c1 = c2" << endl;
    }
    else
    cout << "c1 != c2" << endl;
    //利用成员函数判断c1和c2是否相等
    ret = c1.isSameByClass(c2);
    if(ret)
    {
        cout << "成员函数判断：c1 = c2" << endl;
    }
    else
    cout << "成员函数判断：c1 != c2" << endl;
    //两个判断结果一致

    system("pause");
    return 0;
}
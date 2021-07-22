#include<iostream>
using namespace std;

//抽象不同零件
//抽象CPU
class CPU
{
public:
    //抽象计算函数
    virtual void calculate()= 0;

};

//抽象GPU
class GPU
{
public:
    //抽象显示函数
    virtual void display()= 0;

};

//抽象内存条
class Memory
{
public:
    //抽象存储函数
    virtual void storage()= 0;

};


//电脑类
class Computer
{
public:
    Computer(CPU *cpu, GPU *gpu, Memory *mem)
    {
        m_cpu = cpu;
        m_gpu = gpu;
        m_memory = mem;
    }

    //提供工作的函数
    void work()
    {

        m_cpu->calculate();
        m_gpu->display();
        m_memory->storage();

    }

    ~Computer()
    {

        //释放CPU
        if(m_cpu != NULL)
        {
            delete m_cpu;
            m_cpu = NULL;
        }

        //释放GPU
        if(m_gpu != NULL)
        {
            delete m_gpu;
            m_gpu = NULL;
        }

        //释放Memory
        if(m_memory != NULL)
        {
            delete m_memory;
            m_memory = NULL;
        }
    }

private:
    CPU *m_cpu;
    GPU *m_gpu;
    Memory *m_memory;

};

//具体厂商
//Intel厂商
class IntelCPU:public CPU
{
public:
    virtual void calculate()
    {
        cout << "Intel CPU is working" << endl;
    }
};

//Nvidia厂商
class NvidiaGPU:public GPU
{
public:
    virtual void display()
    {
        cout << "Nvidia GPU is working" << endl;
    }
};

//G.skill厂商
class GskillMem:public Memory
{
public:
    virtual void storage()
    {
        cout << "G.skill Memory is working" << endl;
    }
};

//AMD厂商
class AMDCPU:public CPU
{
public:
    virtual void calculate()
    {
        cout << "AMD CPU is working" << endl;
    }
};

class AMDGPU:public GPU
{
public:
    virtual void display()
    {
        cout << "AMD GPU is working" << endl;
    }
};

class GALAXYMem:public Memory
{
public:
    virtual void storage()
    {
        cout << "GALAXY Memory is working" << endl;
    }
};

//未来的扩展直接添加厂商，即可丰富零件，再拼装即可，不需要再写拼装等基础功能代码。

void test01()
{
    //第一台电脑的零件
    CPU * intelCPU = new IntelCPU;
    GPU * nvidiaGPU = new NvidiaGPU;
    Memory * gskillMem = new GskillMem;

    //创建第一台电脑
    cout << "The first choice:" << endl;
    Computer * computer1 = new Computer(intelCPU, nvidiaGPU, gskillMem);
    computer1->work();
    delete computer1;

    cout << "-------------" << endl;
    cout << "The second choice:" << endl;
    //第二台电脑组装
    Computer * computer2 = new Computer(new AMDCPU, new AMDGPU, new GALAXYMem);
    computer2->work();
    delete computer2; 
}

int main()
{
    test01();
    system("pause");
    return 0;
}
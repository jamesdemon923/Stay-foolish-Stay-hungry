#include<iostream>
using namespace std;

//����ͬ���
//����CPU
class CPU
{
public:
    //������㺯��
    virtual void calculate()= 0;

};

//����GPU
class GPU
{
public:
    //������ʾ����
    virtual void display()= 0;

};

//�����ڴ���
class Memory
{
public:
    //����洢����
    virtual void storage()= 0;

};


//������
class Computer
{
public:
    Computer(CPU *cpu, GPU *gpu, Memory *mem)
    {
        m_cpu = cpu;
        m_gpu = gpu;
        m_memory = mem;
    }

    //�ṩ�����ĺ���
    void work()
    {

        m_cpu->calculate();
        m_gpu->display();
        m_memory->storage();

    }

    ~Computer()
    {

        //�ͷ�CPU
        if(m_cpu != NULL)
        {
            delete m_cpu;
            m_cpu = NULL;
        }

        //�ͷ�GPU
        if(m_gpu != NULL)
        {
            delete m_gpu;
            m_gpu = NULL;
        }

        //�ͷ�Memory
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

//���峧��
//Intel����
class IntelCPU:public CPU
{
public:
    virtual void calculate()
    {
        cout << "Intel CPU is working" << endl;
    }
};

//Nvidia����
class NvidiaGPU:public GPU
{
public:
    virtual void display()
    {
        cout << "Nvidia GPU is working" << endl;
    }
};

//G.skill����
class GskillMem:public Memory
{
public:
    virtual void storage()
    {
        cout << "G.skill Memory is working" << endl;
    }
};

//AMD����
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

//δ������չֱ����ӳ��̣����ɷḻ�������ƴװ���ɣ�����Ҫ��дƴװ�Ȼ������ܴ��롣

void test01()
{
    //��һ̨���Ե����
    CPU * intelCPU = new IntelCPU;
    GPU * nvidiaGPU = new NvidiaGPU;
    Memory * gskillMem = new GskillMem;

    //������һ̨����
    cout << "The first choice:" << endl;
    Computer * computer1 = new Computer(intelCPU, nvidiaGPU, gskillMem);
    computer1->work();
    delete computer1;

    cout << "-------------" << endl;
    cout << "The second choice:" << endl;
    //�ڶ�̨������װ
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
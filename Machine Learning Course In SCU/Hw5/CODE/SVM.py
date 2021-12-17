 -*- coding:utf-8 -*-
#svm.py
 
import numpy as np
import random
import struct
from collections import  Counter
#读取数据
trainimage_path="..."
trainlabel_path="..."
def getimage(filepath):#将二进制文件转换成像素特征的数据
    readfile= open(filepath, 'rb') #以二进制方式打开文件
    file= readfile.read()
    readfile.close()
    index = 0
    nummagic,numimgs,numrows,numcols=struct.unpack_from(">iiii",file,index)
    index += struct.calcsize("iiii")
    images = []
    for i in range(numimgs):
        imgval = struct.unpack_from(">784B", file, index)
        index += struct.calcsize("784B")
        imgval = list(imgval)
        for j in range(len(imgval)):
            if imgval[j] > 1:
                imgval[j] = 1
        images.append(imgval)
    return np.array(images)
def getlabel(filepath):
    readfile = open(filepath, 'rb')
    file = readfile.read()
    readfile.close()
    index = 0
    magic, numitems = struct.unpack_from(">ii", file, index)
    index += struct.calcsize("ii")
    labels = []
    for x in range(numitems):
        im = struct.unpack_from(">1B", file, index)
        index += struct.calcsize("1B")
        labels.append(im[0])
    return np.array(labels)
trainimage=getimage(trainimage_path)
trainimage=[list(i) for i in trainimage]
xdata=trainimage[:2000]
trainlabel=getlabel(trainlabel_path)
trainlabel=list(trainlabel)
ydata=trainlabel[:2000]
class Svc(object):
    def __init__(self,c=100,b=0,xdata=xdata,ydata=0,alpha=np.ones(len(xdata))):#初始化函数
        self.c=c
        self.b=b
        self.xdata=xdata
        self.ydata=ydata
        self.alpha=alpha
    def kernels(self,x1,x2):#核函数np.dot()
        x1=np.mat(x1)
        x2=np.mat(x2)
        a=np.dot(x1,x2.T)
        a=np.array(a)[0][0]
        return a
        # a=0
        # for i in range(len(x1)):
        #         a=a+(x1[i]-x2[i])**2
        # a=np.exp((-1)*a/(2*self.sigma**2))
        # return a
    def kernelmat(self):#核矩阵
        kmat=np.eye(len(self.xdata),len(self.xdata))
        for i in range(len(self.xdata)):
            for j in range(len(self.xdata)):
                kmat[i][j]=self.kernels(self.xdata[i],self.xdata[j])
        return kmat
    def ui(self,i,kmat):  # 求ui
        a=sum([self.alpha[j] * self.ydata[j] *kmat[j,i] for j in range(len(self.xdata))])+self.b
        return a
    def Ei(self,i,kmat):  # 求Ei=ui-yi
        a = self.ui(i,kmat) - self.ydata[i]
        return a
    def alpha2(self,i, tflist,kmat):  # 找第二个alpha2在alpha向量中的位置，通过max|Ei-Ej|
        ei = self.Ei(i,kmat)
        a = 0
        d = 0
        for j in range(len(self.xdata)):
            if tflist[j] == True:
                ej = self.Ei(j,kmat)
                bi = abs(ei - ej)
                if bi > a:
                    a = bi
                    d = j
        return d
    def eta(self, i, j,kmat):  # 求分母eta
        a =  kmat[i,i]+kmat[j,j]-2*kmat[i,j]
        return a
    def alpha2new(self,i, j,kmat):  # 求alpha2new，这里直接做约束
        a = self.alpha[j] + self.ydata[j] * (self.Ei(i,kmat) - self.Ei(j,kmat)) / self.eta(i, j,kmat)
        if self.ydata[i] == self.ydata[j]:
            L = np.max([0, self.alpha[i] + self.alpha[j] - self.c])
            H = np.min([self.c, self.alpha[i] + self.alpha[j]])
            if a > H:
                return H
            elif a < L:
                return L
            else:
                return a
        else:
            L = np.max([0, self.alpha[j] - self.alpha[i]])
            H = np.min([self.c, self.c + self.alpha[j] - self.alpha[i]])
            if a > H:
                return H
            elif a < L:
                return L
            else:
                return a
    def alpha1new(self,i, j,kmat):  # 把alpha2new带进去求alpha1new
        a = self.alpha[i] + self.ydata[i] * self.ydata[j] * (self.alpha[j] - self.alpha2new(i,j,kmat))
        return a
    def bnew(self,i,j,kmat):  # 更新b
        ei = self.Ei(i,kmat)
        ej = self.Ei(j,kmat)
        yi = self.ydata[i]
        yj = self.ydata[j]
        alphai = self.alpha1new(i,j,kmat)
        alphaj = self.alpha2new(i,j,kmat)
        b1 = self.b - ei - yi * (alphai - self.alpha[i]) * kmat[i,i]- yj * (alphaj - self.alpha[j]) *  kmat[i,j]
        b2 = self.b - ej - yi * (alphai - self.alpha[i]) *  kmat[i,j] - yj * (alphaj - self.alpha[j]) *  kmat[j,j]
        if alphai > 0 and alphai < self.c:
            return b1
        elif alphaj > 0 and alphaj < self.c:
            return b2
        else:
            return (b1 + b2) / 2
    def sign(self,x):  # 符号函数
        if x > 0:
            return 1
        elif x < 0:
            return -1
        else:
            return 0
    def acc(self,kmat):  # 计算正确率,判断函数
        a = sum([self.sign( self.ui(i,kmat)) == self.ydata[i] for i in range(len(self.xdata))])
        return a / len(self.xdata)
    def al(self,kmat):  # 训练函数输出alpha,b
        alphav = self.alpha.copy()
        while self.acc(kmat) < 0.90:
            tflist = []
            for i in range(len(self.alpha)):
                tflist.append((self.ydata[i] * self.ui(i,kmat) == 1 and self.alpha[i] == 0) or (self.ydata[i] * self.ui(i,kmat) > 1 and self.alpha[i] != 0) or (self.ydata[i] * self.ui(i,kmat) < 1))
            for i in range(len(self.alpha)):
                if tflist[i] == True:
                    j = self.alpha2(i,tflist,kmat)
                    t = self.alpha2new(i,j,kmat)
                    alphav[j] = t
                    alphav[i] = self.alpha1new(i,j,kmat)
                    self.b = self.bnew(i,j,kmat)
                    self.alpha = alphav
                    if (self.acc(kmat) < 0.90)==False:
                        return self.alpha, self.b
        return self.alpha,self.b
 
def train():
    def xydata(xdata,ydata,i,j):#提取i和j类的数据
        xresult=[]
        yresult=[]
        for m in range(len(xdata)):
            if ydata[m]==i:
                xresult.append(xdata[m])
                yresult.append(1)
            elif ydata[m]==j:
                xresult.append(xdata[m])
                yresult.append(-1)
        return xresult,yresult
    xdatas=[]
    ydatas=[]
    names=[]#储存ij标签
    alphas=[]#储存alpha
    bs=[]#储存b
    for i in range(9):
        for j in range(i+1,10):
            x,y=xydata(xdata,ydata,i,j)
            xdatas.append(x)
            ydatas.append(y)
            s=Svc()
            s.xdata = x
            s.ydata = y
            kmat=s.kernelmat()
            s.alpha=np.ones(len(s.xdata))
            aa,bb=s.al(kmat)
            names.append([i, j])
            alphas.append(aa)
            bs.append(bb)
            print([i,j])
    return xdatas,ydatas,names,alphas,bs
def test(xdatas, ydatas, names, alphas, bs):
    def kernel(x1,x2):#核函数np.dot()
        x1=np.mat(x1)
        x2=np.mat(x2)
        a=np.dot(x1,x2.T)
        a=np.array(a)[0][0]
        return a
    n=0
    for i in range(1000):
        a=[]
        for j in range(45):
            b=sum([kernel(xdatas[j][m],xdata[i])*ydatas[j][m]*alphas[j][m] for m in range(len(ydatas[j]))])+bs[j]
            if b>0:
                a.append(names[j][0])
            else:
                a.append(names[j][1])
        a=Counter(a).most_common(1)[0][0]
        n=n+(a==ydata[i])
    return n/1000#输出准确率，为了快速出结果，这里只验证前1000条数据
def main():
    xdatas, ydatas, names, alphas, bs=train()
    testresult=test(xdatas,ydatas,names,alphas,bs)
    print(testresult)
 
if __name__=="__main__":
    main()
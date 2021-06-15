#!/usr/bin/env python
# coding: utf-8

# In[1]:


#-*- coding=utf-8 -*-

#打开Modeldata.csv，将其数据读取入列表中
path = 'C:\Users\94496\Desktop\OPVs\代码\Modeldata.csv'
with open(path, 'r', encoding='utf-8') as dmf:
    count = 1
    head = []
    rdata = []
    row = []
    for line in dmf.readlines():
        if count == 1:
            head = line.split( )
            count += 1
        else:
            row = line.split( )
            rdata.append(row)
            count += 1
dmf.close()


# In[9]:


#将数据分为“id”“smiles”“pce”三部分存储在列表mdata[]中
id = 0
smiles = 1
pce = 4
row = []
mdata = []
count = 1
for item in rdata:
    row = [item[id], item[smiles], item[pce]]
    mdata.append(row)
print(mdata[0])
#print(type(eval(item[pce])))


# In[35]:


#Z-score标准化
from sklearn import preprocessing
import numpy as np
count = 0
pce = 2
numlist = []
#print(mdata[0])
#print(type(eval(mdata[0][pce])))
for item in mdata:
    numlist.append(eval(item[pce]))
#导入相关数据，将其转化为数组
cdata = np.array(numlist)
#将数据标准化
cdata_scaled = preprocessing.scale(X)
#标准化后数据的均值
#print(X_scaled.mean())
#标准化后数据的方差
#print(X_scaled.std())


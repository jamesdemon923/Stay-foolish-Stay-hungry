

# In[33]:


#导入模型所需要的数据库
import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
from sklearn.metrics import precision_score
from sklearn import preprocessing
from pylab import *


# In[47]:


#读取数据
df_train=pd.read_csv(r'C:\Users\94496\Desktop\Mycode\Data mining\Random forest\Train.csv',sep=None)
df_test=pd.read_csv(r'C:\Users\94496\Desktop\Mycode\Data mining\Random forest\Test.csv',sep=None)


# In[48]:


#将训练数据的输入输出分开
X_train=df_train.iloc[0:80,1:9]
Y_train=df_train.iloc[0:80,0:1]
print(X_train,Y_train)


# In[65]:


#将预测数据的输入输出分开
X_test=df_test.iloc[:24,1:9]
Y_test=df_test.iloc[:24,0:1]
Y_test


# In[53]:


#建立模型
model=RandomForestClassifier(n_estimators=4,max_features=3)
model.fit(X_train,Y_train)


# In[54]:


#模型预测
Y_pred=model.predict(X_test)
Y_pred

# In[56]:


#计算准确率
precision_score(Y_test, Y_pred, average='micro')


# In[71]:


#做出混淆矩阵
confusion_matrix(Y_test,Y_pred)
cfm = confusion_matrix(Y_test,Y_pred)
plt.matshow(cfm, cmap=plt.cm.Blues)
plt.show()


# In[86]:


Y_test=np.array(Y_test)
Y_test=Y_test.tolist()


# In[87]:


#将对应的故障标签值转换为对应数字，方便作图
le = preprocessing.LabelEncoder()
le.fit(Y_test)
list(le.classes_)
Y_test=le.transform(Y_test)
Y_pred=le.transform(Y_pred)


# In[121]:


#作图
x=range(0,15)
#设置图形大小
plt.figure(figsize=(12,8),dpi=50)
# color可以百度颜色代码
plt.plot(x,Y_pred,label=u"预测值",color="#F08080")
plt.plot(x,Y_test,label=u"真实值",color="#DB7093",linestyle="--")
plt.xlabel(u'序号',fontsize=20) 
plt.rcParams['font.sans-serif'] = ['SimHei']  #显示中文
plt.xticks(fontsize=20)
plt.yticks(fontsize=20)
plt.legend(loc='upper center',fontsize=20)
plt.show()


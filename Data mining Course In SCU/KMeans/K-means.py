import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.cluster import KMeans


#算法部分
X = pd.read_csv(r'TE.csv')
X = X.iloc[:,0:2]
estimator = KMeans(n_clusters=3,init='k-means++',n_init=10,max_iter=300,tol=1e-04,random_state=0)
Y = estimator.fit_predict(X)
label_pred = estimator.labels_ #获取聚类标签
centers=estimator.cluster_centers_ 
center_x=[]
center_y=[]
for i in range(3):
    center_x.append(centers[i][0])
    center_y.append(centers[i][1])

x0 = X[label_pred == 0]
x1 = X[label_pred == 1]
x2 = X[label_pred == 2]
#x3 = X[label_pred == 3]
#fig = plt.figure(figsize = (4,3),dpi=200)

#画图部分
plt.figure(figsize=(16, 6))
ax1 = plt.subplot(1,2,1)
ax2 = plt.subplot(1,2,2)
plt.rcParams['font.sans-serif']=['SimHei'] #用来正常显示中文标签

#原始数据图
plt.sca(ax1)
plt.scatter(X.iloc[:, 0], X.iloc[:, 1], c = "red", marker='o', label='see') #分别取第一列和第二列数据
plt.xlabel('A FEED (kg/hr)')
plt.ylabel('D FEED (kg/hr)')
plt.title('原始数据')

#聚类处理后的数据图
plt.sca(ax2)
plt.scatter(x0.iloc[:, 0], x0.iloc[:, 1], c = "yellow", marker='o', label='label0')
plt.scatter(x1.iloc[:, 0], x1.iloc[:, 1], c = "c", marker='^', label='label1')
plt.scatter(x2.iloc[:, 0], x2.iloc[:, 1], c = "dodgerblue", marker='+', label='label2')
plt.scatter(center_x,center_y, c = "red", marker='*', label='cluster_center')
#plt.scatter(x3.iloc[:, 0], x3.iloc[:, 1], c = "blue", marker='_', label='label2')
plt.xlabel('A FEED (kg/hr)')
plt.ylabel('D FEED (kg/hr)')
plt.xlim(3550,3820)
plt.legend(loc=1)
plt.title('聚类处理后数据')
plt.show()


  
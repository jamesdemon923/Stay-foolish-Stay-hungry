from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import BaggingClassifier
import numpy as np
from sklearn import metrics
from sklearn.model_selection import train_test_split,cross_val_score
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
import matplotlib as mpl
import matplotlib.pyplot as plt

#1读入表格
pos = pd.read_excel('d00_1.xlsx',header = None,index_col = None)
neg01 = pd.read_excel('d01_1.xlsx',header = None,index_col = None)
neg02 = pd.read_excel('d02_1.xlsx',header = None,index_col = None)

#2做标记,贴标签
neg01['result'] = 1
pos['result'] = 0
neg02['result'] = 2

#3合并表格
pn = pd.concat([pos,neg01,neg02],ignore_index = True)

#4划分训练集和测试集
y = pn['result']
x = pn.iloc[0:,:52]
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.2)

#5建立模型knn1，取经验K值
knn1 = KNeighborsClassifier( weights = "distance",n_neighbors = 3 )
knn1.fit(x_train,y_train)
y_predict = knn1.predict(x_test)
knn1.predict_proba(x_test)
score = knn1.score(x_test,y_test,sample_weight = None)
print(score)

#5.1通过交叉验证寻找最佳K值
k_range = [2 * i + 1 for i in range(11)]
k_ranges = [str(i) for i in k_range]
k_scores = []
for k in k_range:
    knn = KNeighborsClassifier(n_neighbors = k )
    scores = cross_val_score(knn, x_train, y_train,cv = 10,scoring = 'accuracy')
    k_scores.append(scores.mean())

#5.2将交叉验证结果可视化
plt.style.use('seaborn-whitegrid')
figure1 = plt.figure()
selectKImg = figure1.add_axes([0.1,0.1,0.8,0.8])
plt.ylim(0.97,0.99)
plt.xticks(k_range,k_ranges)

font01 = {'family' : 'Times New Roman',
        'weight' : 'normal',
        'size'   : 15,
        }
font02 = {'family' : 'Times New Roman',
        'weight' : 'normal',
        'size'   : 15,
        }

plt.xlabel('Value of k for kNN1',font01)
plt.ylabel('Cross-Validated Accuracy',font02)
plt.yticks(fontproperties = 'Times New Roman', size = 14)
plt.xticks(fontproperties = 'Times New Roman', size = 14)
selectKImg.plot(k_range,k_scores,color = 'b',marker = '',lw = 1)
selectKImg.scatter(k_range,k_scores,color = 'r',s = 20)
plt.savefig("最佳K值选取可视化.png")

#5.3得到best_knn模型
best_knn = KNeighborsClassifier(n_neighbors = 3,weights = 'distance')# 选择最优的K=3传入模型
best_knn.fit(x_train,y_train)#训练模型
print(best_knn.score(x_test,y_test))#看看评分

#6降维数据绘制分类结果图
LDA = LinearDiscriminantAnalysis()
x_lda = LDA.fit_transform(x_train,y_train)
x_test_lda = LDA.fit_transform(x_test,y_test)
right = x_test_lda[y_predict == y_test]
wrong = x_test_lda[y_predict != y_test]

mpl.rcParams['font.family'] = 'STSong'
mpl.rcParams['axes.unicode_minus'] = False
mpl.rcParams['xtick.labelsize'] = 15
mpl.rcParams['ytick.labelsize'] = 15
# mpl.rcParams['vaxes.titlesize'] = large
font1 = {'family' : 'Times New Roman',
        'weight' : 'normal',
        'size'   : 15,
        }
font2 = {'family' : 'Times New Roman',
        'weight' : 'normal',
        'size'   : 15,
        }

plt.figure(figsize=(10, 10))
plt.yticks(fontproperties='Times New Roman', size=15)#设置行列值字体字号
plt.xticks(fontproperties='Times New Roman', size=15)

plt.scatter(x=x_lda[y_train == 0, 0], y=x_lda[y_train == 0, 1], color=[1, 1, 0], s=15, marker='s', label='训练集正常状态')
plt.scatter(x=x_lda[y_train == 1, 0], y=x_lda[y_train == 1, 1], color='g', s=15, label='训练集故障模式1')
plt.scatter(x=x_lda[y_train == 2, 0], y=x_lda[y_train == 2, 1], color='b', s=15, marker='D', label='训练集故障模式2')

plt.scatter(x=right[:, 0], y=right[:, 1], color='grey', marker='>', s=25, label='测试集正确分类结果')
plt.scatter(x=wrong[:, 0], y=wrong[:, 1], color='purple', marker='x', s=40, label='测试集错误分类结果')

plt.xlabel("Charactor1", font1)#设置行列标签字体字号
plt.ylabel('Charactor2', font2)
plt.title("KNN分类结果显示")
plt.legend(loc="best")
plt.show()
plt.style.use('seaborn-whitegrid')#设置绘图样式
plt.savefig("KNN分类效果可视化.png")#保存图片

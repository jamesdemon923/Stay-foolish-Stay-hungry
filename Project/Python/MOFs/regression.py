import numpy
from sklearn.model_selection import train_test_split
from sklearn import datasets
from sklearn import svm
import pandas as pd
import numpy as np
from sklearn.externals import joblib
from sklearn.linear_model import LogisticRegression
from sklearn import ensemble
from sklearn.tree import ExtraTreeRegressor
import matplotlib.pyplot as plt
from sklearn.ensemble import BaggingRegressor
from sklearn import neighbors
from sklearn import linear_model
from sklearn import tree

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用黑体显示中文
plt.rcParams['axes.unicode_minus'] = False  # 正常显示负号


# 获取目标列
def getY(column_name, rate) -> numpy.ndarray:
    data = pd.read_csv('data1.csv', usecols=[column_name])
    row_count = len(data)
    a = np.asarray(data).reshape(2000, )
    index = (int)(row_count * rate)
    return a[0:index], a[index + 1:row_count]


# 获取特征变量
def getX(ls, rate) -> numpy.ndarray:
    data = pd.read_csv('data1.csv', usecols=[i for i in ls])
    row_count = len(data)
    a = np.asarray(data)
    index = (int)(row_count * rate)
    return a[0:index], a[index + 1:row_count]


# 测试不同的模型
def try_different_method(model, x_train, y_train, x_test, y_test):
    model.fit(x_train, y_train)
    # joblib.dump(model, "model.m")  保存模型
    score = model.score(x_test, y_test)
    return score
    # result = model.predict(x_test)
    # plt.figure()
    # plt.xlabel('数据编号', fontsize=13)
    # plt.ylabel('工作性能', fontsize=13)
    # plt.plot(np.arange(len(result)), sorted(y_test), 'go-', label='真实值')
    # plt.plot(np.arange(len(result)), sorted(result), 'ro-', label='预测值')
    # plt.title('预测模型得分: %f' % score)
    # plt.legend()
    # plt.show()


if __name__ == '__main__':
    # 特征变量所在的列
    ls = [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
    # 总的数据量为200，这里选取1600即80%的数据进行训练，用20%的数据进行测试
    x_train, x_test = getX(ls, 0.8)
    y_train, y_test = getY("wc-propane", 0.8)

    treeCount = 0
    for i in range(1, 100):
        n = try_different_method(ensemble.RandomForestRegressor(n_estimators=i), x_train, y_train, x_test, y_test)
        print("第%d棵决策树的得分为:%f" % (i, n))
    # try_different_method(ExtraTreeRegressor(), x_train, y_train, x_test, y_test)
    # try_different_method(BaggingRegressor(), x_train, y_train, x_test, y_test)
    # try_different_method(ensemble.GradientBoostingRegressor(n_estimators=100), x_train, y_train, x_test, y_test)
    # try_different_method(neighbors.KNeighborsRegressor(), x_train, y_train, x_test, y_test)
    # try_different_method(svm.SVR(), x_train, y_train, x_test, y_test)
    # try_different_method(linear_model.LinearRegression(), x_train, y_train, x_test, y_test)
    # try_different_method(tree.DecisionTreeRegressor(), x_train, y_train, x_test, y_test)
    # try_different_method(ensemble.AdaBoostRegressor(n_estimators=50), x_train, y_train, x_test, y_test)

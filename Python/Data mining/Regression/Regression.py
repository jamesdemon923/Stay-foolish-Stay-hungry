#多项式回归模型拟合反应器模型
#导入所需要的模型库
import numpy as np
import xlrd
import xlwt
import sklearn
from sklearn.preprocessing import PolynomialFeatures
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.pipeline import Pipeline
from sklearn.metrics import *
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
#from sklearn.externals import joblib
import joblib
from sklearn import linear_model
import numpy as np

#打开反应器输入数据作为矩阵储存
data = xlrd.open_workbook("InputData.xlsx")
table = data.sheets()[3]
nrows = table.nrows  # 行数
ncols = table.ncols  # 列数
c1 = np.arange(0, nrows, 1)
datamatrix = np.zeros((nrows, ncols))
for i in range(ncols):
    cols = table.col_values(i)
    cols1 = np.matrix(cols)  # 把list转换为矩阵进行矩阵操作
    datamatrix[:, i] = cols1 # 把数据进行存储
x=datamatrix
#打开反应器输出数据作为矩阵储存
data2 = xlrd.open_workbook("OutputData.xlsx")
table2 = data2.sheets()[3]
nrows2 = table2.nrows  # 行数
ncols2 = table2.ncols  # 列数
c2 = np.arange(0, nrows2, 1)
datamatrix2 = np.zeros((nrows2, ncols2))
for i in range(ncols2):
    cols2 = table2.col_values(i)
    cols12 = np.matrix(cols2)  # 把list转换为矩阵进行矩阵操作
    datamatrix2[:, i] = cols12# 把数据进行存储
y=datamatrix2
#闪蒸罐与反应器相同，此处略
#定义多项式特征
def PolynomialRegression(degree):
    poly_reg = Pipeline([('poly',PolynomialFeatures(degree=degree)), ('std_scaler',StandardScaler()), ('lin_reg',LinearRegression())])
    return poly_reg 

#拆分训练集和测试集
x_train,x_test,y_train,y_test = train_test_split(x,y)
poly_reg2 = PolynomialRegression(2)
#训练、测试多项式
poly_reg2.fit(x_train,y_train)
y_predict = poly_reg2.predict(x_test)
#定义测试指标
R2=r2_score(y_test, y_predict)
yr=np.array((y_predict-y_test))
RMSE=(mean_squared_error(y_test,y_predict))**0.5
print(RMSE,R2)

#保存模型
joblib.dump(poly_reg2,"DF_P3_NewMole.m")

#查看回归系数和截距
poly_reg =PolynomialFeatures(degree=2)
X_ploy =poly_reg.fit_transform(x_train)
lin_reg_3=linear_model.LinearRegression()
lin_reg_3.fit(X_ploy,y_train)
print('Cofficients:',lin_reg_3.coef_)
print('intercept',lin_reg_3.intercept_)

#保存模型回归系数和截距
workbook=xlwt.Workbook()  
booksheet=workbook.add_sheet('Sheet 1', cell_overwrite_ok=True)  
for i,row in enumerate(np.transpose(lin_reg_3.coef_)):  
    for j,col in enumerate(row):  
        booksheet.write(i,j,col)
workbook.save("\Polynomial.xlsx")


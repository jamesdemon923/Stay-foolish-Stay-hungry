import pandas as pd
import numpy as np
from keras.models import Sequential
from keras.layers import Dense, LSTM, Dropout
import matplotlib.pyplot as plt
import sys
from sklearn.preprocessing import MinMaxScaler
#导入数据
Io=r'C:\Users\94496\Desktop\vscode\Python\7-时间序列分析\Original data.csv'
data = pd.read_excel(io=Io)
data=data.drop(columns=['time'])
column=data.shape[1]#列数
row=data.shape[0]#行数

#时间序列数据转化为监督问题数据
def series_to_supervised(data, n_in=1, n_out=1, dropnan=True):
    n_vars = 1 if type(data) is list else data.shape[1]
    df = pd.DataFrame(data)
    cols, names = list(), list()
    # input sequence (t-n, ... t-1)
    for i in range(n_in, 0, -1):
        cols.append(df.shift(i))
        names += [('var%d(t-%d)' % (j+1, i)) for j in range(n_vars)]
    # forecast sequence (t, t+1, ... t+n)
    for i in range(0, n_out):
        cols.append(df.shift(-i))
        if i == 0:
            names += [('var%d(t)' % (j+1)) for j in range(n_vars)]
        else:
            names += [('var%d(t+%d)' % (j+1, i)) for j in range(n_vars)]
    # put it all together
    agg = pd.concat(cols, axis=1)
    agg.columns = names
    # drop rows with NaN values
    if dropnan:
        agg.dropna(inplace=True)
    return agg

# 将数据归一化到0-1之间,无量纲化
scaler = MinMaxScaler(feature_range=(0,1))
scaled_data = scaler.fit_transform(data.values)

# 将时序数据转换为监督问题数据
reframed = series_to_supervised(scaled_data, 1, 1)

#删除无用的label数据
reframed.drop(reframed.columns[column:column*2-1], axis=1, inplace=True)

# 数据集划分,选取前80%天的数据作为训练集,其余的作为测试集
train_days = round(row*0.8)
test_days = round(row*0.2)
values = reframed.values
train = values[:train_days,:]
test = values[train_days:,:]
train_X, train_y = train[:, :-1], train[:, -1]
test_X, test_y = test[:, :-1], test[:, -1]

# 将数据集重构为符合LSTM要求的数据格式,即 [样本，时间步，特征]
train_X = train_X.reshape((train_X.shape[0], 1, train_X.shape[1]))
test_X = test_X.reshape((test_X.shape[0], 1, test_X.shape[1]))
train_y = train_y.reshape(train_y.shape[0])
test_y = test_y.reshape(test_y.shape[0])

#建立模型并训练
model = Sequential()
model.add(LSTM(50, activation='relu',input_shape=(train_X.shape[1], train_X.shape[2])))
model.add(Dense(1))
model.compile(loss='mean_squared_error', optimizer='adam')
LSTM=model.fit(train_X, train_y, epochs=100, batch_size=32, validation_data=(test_X, test_y), verbose=2, shuffle=False)
# plot history
plt.plot(LSTM.history['loss'])
plt.legend()
plt.show()

#模型预测并可视化
train_predict = model.predict(train_X)
test_predict = model.predict(test_X)
traintemp = np.zeros((len(train_y), column-1))
testtemp = np.zeros((len(test_y), column-1))
train_temp = np.hstack((traintemp, train_predict))
predict_temp = np.hstack((testtemp, test_predict))
train_predict = scaler.inverse_transform(train_temp)
test_predict = scaler.inverse_transform(predict_temp)
plt.rcParams['font.sans-serif']=['SimHei'] #用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False #用来正常显示负号
plt.plot(data[data.columns[-1]], c='b',label='real')
plt.plot(train_predict[:, -1], c='g',label='train')
plt.plot([None for _ in train_predict]  + [x for x in test_predict[:, -1]], c='y',label='test')
plt.xlabel('序号', fontsize=12)
plt.ylabel('产量（t/h）', fontsize=12)
plt.legend()
plt.show()


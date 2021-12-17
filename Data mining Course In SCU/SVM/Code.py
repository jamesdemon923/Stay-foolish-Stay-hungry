import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error

import warnings
warnings.filterwarnings('ignore') # 忽略不妨碍程序运行的warning eg.FutureWarning

# 读取 excel
data_in = np.array(pd.read_excel(io='./输入.xlsx', header=0))
data_out = pd.read_excel(io='./输出.xlsx', header=0, usecols=[0, ]) # usecols = int or list, default=None
outputs_d = np.array(data_out).reshape(-1, 1)

# 归一化
min_max_scaler = MinMaxScaler()
inputs = min_max_scaler.fit_transform(data_in)
outputs = min_max_scaler.fit_transform(outputs_d).ravel()
# print(inputs.shape)
# print(outputs.shape)

# PCA降维
from sklearn.decomposition import PCA
pca = PCA(n_components=15)
pca.fit(inputs)
inputs_p = pca.transform(inputs)
# contribution = pca.explained_variance_ratio_
# print(contribution)
# print(sum(contribution))

# 划分测试集与训练集
X_train, X_test, y_train, y_test = train_test_split(inputs_p, outputs, test_size=0.2, random_state=8264)

# 使用 SVR 模型
from sklearn.svm import SVR
svr = SVR(kernel='rbf', C=13, gamma=0.35)
svr.fit(X_train, y_train)

score = svr.score(X_test, y_test)
y_predict = svr.predict(X_test)
MSE = mean_squared_error(y_test, y_predict)

print('score =', score)
print('MSE =', str(MSE))

# 反归一化图像
y_predict_r = min_max_scaler.inverse_transform(y_predict.reshape(1, -1))
y_test_r = min_max_scaler.inverse_transform(y_test.reshape(1, -1))

plt.figure(figsize=(10, 6.5), dpi=80, )
plt.scatter(y_test_r, y_predict_r, color='blue')
all_value = np.vstack((y_test_r, y_predict_r))
plt.plot([np.min(all_value), np.max(all_value)], [np.min(all_value), np.max(all_value)])
plt.xticks(fontsize=20)
plt.yticks(fontsize=20)
plt.title('Mass flow of Gasoline', fontsize=20)
plt.xlabel('Industrial values (t/h)', fontsize=20)
plt.ylabel('Model values (t/h)', fontsize=20)
plt.show()

import numpy as np
import pandas
import pandas as pd
import torch
from torch import nn
from d2l import torch as d2l
from functions import *

if __name__ == '__main__':
    filePath = 'data/train_data.csv'
    columnName = ['Henry Coef of propane', 'Henry Coef of propene',
                  'avg_loading_absolute_propane-1', 'avg_loading_absolute_propene-1',
                  'avg_loading_absolute_propane-0.1', 'avg_loading_absolute_propene-0.1',
                  'wc-propane', 'wc-propene', 'S-propane-1', 'S-propene-1', 'APS-propane',
                  'APS-propene']
    data = clean_data(filePath, columnName)
    columnName = 'APS-propane'
    data = data.drop(data[data[columnName] < 1].index)  # 去除APS性能评分低于1的数据
    flag = 0  # 0表示对propane(丙烷)做预测,1表示对propene(丙烯做预测)
    standard_data = standardize_data(data)
    all_features = pd.concat([standard_data.iloc[:, 13:25],
                              standard_data.iloc[:, 25 + flag: 25 + flag],
                              standard_data.iloc[:, 27 + flag: 27 + flag],
                              standard_data.iloc[:, 29 + flag: 29 + flag]], axis=1)
    # 这里选取数据集中80%数据作为训练,20%作为测试集
    rate = 0.8
    length = int(data.shape[0] * rate)
    train_data = data.iloc[0:length, :]
    train_features = torch.tensor(all_features[0:length].values, dtype=d2l.float32)
    test_data = data.iloc[length:, :]
    test_features = torch.tensor(all_features[length:].values, dtype=d2l.float32)

    # in_features = train_features.shape[1]
    train_labels = get_labels(train_data, columnName=columnName)
    test_labels = get_labels(test_data, columnName=columnName)

    k, num_epochs, lr, weight_decay, batch_size = 3, 50, 1, 0.00, 150

    '''
    使用代码时只需要取消注释,建议单独运行每一个功能
    '''

    '作图分析'
    # draw_scatter(data.iloc[:, 0], data[columnName], y_label=columnName)

    '训练代码。超参数已经进行了调整'
    # train_l, valid_l = k_fold(k, train_features, train_labels, num_epochs, lr,
    #                           weight_decay, batch_size)
    # print(f'{k}-折验证: 平均训练log rmse: {float(train_l):f}, '
    #       f'平均验证log rmse: {float(valid_l):f}')

    '预测代码'
    train_and_pred(train_features, test_features, train_labels, test_data,
                   num_epochs, lr, weight_decay, batch_size, columnName)

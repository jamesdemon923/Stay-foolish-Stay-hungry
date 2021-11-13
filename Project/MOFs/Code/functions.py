import numpy as np
import pandas
import pandas as pd
import torch
from torch import nn
from d2l import torch as d2l
import math

loss = nn.MSELoss()


def clean_data(csvFilepath='', columnNames=[]) -> pandas.DataFrame:
    # 删除 选中列存在数值缺失的行
    data = pd.read_csv(csvFilepath)
    data = data.dropna(axis=0, subset=columnNames)
    return data


def standardize_data(data=None, start=0, end=None) -> pandas.DataFrame:
    '''
    将原始数据进行一定的处理，得到能够进行训练的数据集
    :param train_data: 训练数据集
    :param start: 数据特征值的起始列,默认从第一列开始读取数据
    :param end: 数据特征值的结束列,默认读到最后一列
    :return: 以DataFrame的数据类型返回处理好的数据，便于后续训练使用
    '''
    if end is not None:
        end += 1
    features = data.iloc[:, start:end]
    # 对数值数据进行标准化处理,使每一列的数据均值为0,方差为1
    numeric_features = features.dtypes[features.dtypes != 'object'].index
    features[numeric_features] = features[numeric_features].apply(
        lambda x: (x - x.mean()) / (x.std()))
    # 在标准化数据之后，所有原始数据都意味着消失，因此我们可以将缺失值设置为0
    features[numeric_features] = features[numeric_features].fillna(0)
    return features


def get_labels(data=None, columnName='') -> torch.Tensor:
    '''
    得到真实数据的结果集
    :param data: 数据集
    :param columnName: 结果集所在的列的列名
    :return: 以张量的形式返回结果集
    '''
    train_labels = torch.tensor(data[columnName].values.reshape(-1, 1), dtype=d2l.float32)
    return train_labels


def get_net(in_features=0):
    '''
    :param in_features: 特征的个数
    :return: 一个带有层级的神经网络
    '''
    net = nn.Sequential(nn.Linear(in_features, 1))
    return net


def log_rmse(net, features, labels):
    # 为了在取对数时进一步稳定该值，将小于1的值设置为1
    rmse = loss(net(features), labels)
    return rmse.item()


def train(net, train_features, train_labels, test_features, test_labels,
          num_epochs, learning_rate, weight_decay, batch_size):
    train_ls, test_ls = [], []
    train_iter = d2l.load_array((train_features, train_labels), batch_size)
    net = get_net(train_features.shape[1])
    # 这里使用的是Adam优化算法
    optimizer = torch.optim.Adam(net.parameters(),
                                 lr=learning_rate,
                                 weight_decay=weight_decay)
    for epoch in range(num_epochs):
        for X, y in train_iter:
            optimizer.zero_grad()
            l = loss(net(X), y)
            l.backward()
            optimizer.step()
        train_ls.append(log_rmse(net, train_features, train_labels))
        if test_labels is not None:
            test_ls.append(log_rmse(net, test_features, test_labels))
    return train_ls, test_ls


def get_k_fold_data(k, i, X, y):
    assert k > 1
    fold_size = X.shape[0] // k
    X_train, y_train = None, None
    for j in range(k):
        idx = slice(j * fold_size, (j + 1) * fold_size)
        X_part, y_part = X[idx], y[idx]
        if j == i:
            X_valid, y_valid = X_part, y_part
        elif X_train is None:
            X_train, y_train = X_part, y_part
        else:
            X_train = torch.cat((X_train, X_part), 0)
            y_train = torch.cat((y_train, y_part), 0)
    return X_train, y_train, X_valid, y_valid


def k_fold(k, X_train, y_train, num_epochs, learning_rate, weight_decay,
           batch_size):
    train_l_sum, valid_l_sum = 0, 0
    for i in range(k):
        data = get_k_fold_data(k, i, X_train, y_train)
        net = get_net(X_train.shape[1])
        train_ls, valid_ls = train(net, *data, num_epochs, learning_rate,
                                   weight_decay, batch_size)
        train_l_sum += train_ls[-1]
        valid_l_sum += valid_ls[-1]
        if i == 0:
            d2l.plot(list(range(1, num_epochs + 1)), [train_ls, valid_ls],
                     xlabel='epoch', ylabel='rmse', xlim=[1, num_epochs],
                     legend=['train', 'valid'])
            d2l.plt.show()
        print(f'fold {i + 1}, train rmse {float(train_ls[-1]):f}, '
              f'valid rmse {float(valid_ls[-1]):f}')
    return train_l_sum / k, valid_l_sum / k


def draw_scatter(x=None, y=None, length=10, width=8, size=0.5, x_label='', y_label=''):
    if x_label == '':
        x_label = '数据编号'
    d2l.plt.figure(figsize=(length, width))
    d2l.plt.rcParams['font.sans-serif'] = 'SimHei'
    d2l.plt.rcParams['axes.unicode_minus'] = False  # 设置正常显示符号
    d2l.plt.xlabel(x_label)
    d2l.plt.ylabel(y_label, rotation=0)
    d2l.plt.scatter(x, y, s=size)
    d2l.plt.show()

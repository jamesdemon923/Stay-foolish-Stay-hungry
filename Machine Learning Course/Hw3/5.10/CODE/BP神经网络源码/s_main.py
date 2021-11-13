import numpy as np
import matplotlib.pyplot as plt
from TwoLayerNet import TwoLayerNet
from mnist import load_mnist

(x_train, t_train), (x_test, t_test) = load_mnist(normalize=True, one_hot_label=True)
net = TwoLayerNet(input_size=784, hidden_size=50, output_size=10, weight_init_std=0.01)

epoch = 20000
batch_size = 100
lr = 0.1

train_size = x_train.shape[0]  # 60000
iter_per_epoch = max(train_size / batch_size, 1)  # 600

train_loss_list = []
train_acc_list = []
test_acc_list = []

for i in range(epoch):
    batch_mask = np.random.choice(train_size, batch_size)  # 从0到60000 随机选100个数
    x_batch = x_train[batch_mask]
    y_batch = net.predict(x_batch)
    t_batch = t_train[batch_mask]
    grad = net.gradient(x_batch, t_batch)

    for key in ('w1', 'b1', 'w2', 'b2'):
        net.dict[key] -= lr * grad[key]
    loss = net.loss(y_batch, t_batch)
    train_loss_list.append(loss)

    # 每批数据记录一次精度和当前的损失值
    if i % iter_per_epoch == 0:
        train_acc = net.accuracy(x_train, t_train)
        test_acc = net.accuracy(x_test, t_test)
        train_acc_list.append(train_acc)
        test_acc_list.append(test_acc)
        print(
            '第' + str(i + 1) + '次迭代''train_acc, test_acc, loss :| ' + str(train_acc) + ", " + str(test_acc) + ',' + str(
                loss))


markers = {'train': 'o', 'test': 's'}
x = np.arange(len(train_acc_list))
plt.plot(x, train_acc_list, label='train acc')
plt.plot(x, test_acc_list, label='test acc', linestyle='--')
plt.xlabel("epochs")
plt.ylabel("accuracy")
plt.ylim(0, 1.0)
plt.legend(loc='lower right')
plt.show()

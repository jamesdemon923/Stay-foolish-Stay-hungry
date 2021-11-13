import numpy as np
from functions import sigmoid, sigmoid_grad, softmax, cross_entropy_error

class TwoLayerNet:

    def __init__(self, input_size, hidden_size, output_size, weight_init_std):
        # 初始化权重
        self.dict = {}
        self.dict['w1'] = weight_init_std * np.random.randn(input_size, hidden_size)  # 0.01*(784,50)
        self.dict['b1'] = np.zeros(hidden_size)  # (0......0) 1*50
        self.dict['w2'] = weight_init_std * np.random.randn(hidden_size, output_size)  # 0.01*(50,10)
        self.dict['b2'] = np.zeros(output_size)  # (0......0) 1*10

    def predict(self, x):
        w1, w2 = self.dict['w1'], self.dict['w2']
        b1, b2 = self.dict['b1'], self.dict['b2']

        a1 = np.dot(x, w1) + b1
        z1 = sigmoid(a1)
        a2 = np.dot(z1, w2) + b2
        y = softmax(a2)

        return y

    def loss(self, y, t):
        t = t.argmax(axis=1)
        num = y.shape[0]
        s = y[np.arange(num), t]

        return -np.sum(np.log(s)) / num

    def gradient(self, x, t):
        w1, w2 = self.dict['w1'], self.dict['w2']
        b1, b2 = self.dict['b1'], self.dict['b2']
        grads = {}

        a1 = np.dot(x, w1) + b1
        z1 = sigmoid(a1)
        a2 = np.dot(z1, w2) + b2
        y = softmax(a2)

        num = x.shape[0]
        dy = (y - t) / num
        grads['w2'] = np.dot(z1.T, dy)
        grads['b2'] = np.sum(dy, axis=0)

        da1 = np.dot(dy, w2.T)
        dz1 = sigmoid_grad(a1) * da1
        grads['w1'] = np.dot(x.T, dz1)
        grads['b1'] = np.sum(dz1, axis=0)

        return grads

    def accuracy(self,x,t):
        y = self.predict(x)
        p = np.argmax(y, axis=1)
        q = np.argmax(t, axis=1)
        acc = np.sum(p == q) / len(y)
        return acc

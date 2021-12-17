#全连接网络
from torch import nn,optim
class linear_model(nn.Module):
    def __init__(self):
        super(linear_model, self).__init__()
        self.dense = nn.Sequential(nn.Linear(28*28, 256), nn.PReLU(),nn.Linear(256, 10)) #PReLU效果比ReLU好

    def forward(self, x):
        return self.dense(x)
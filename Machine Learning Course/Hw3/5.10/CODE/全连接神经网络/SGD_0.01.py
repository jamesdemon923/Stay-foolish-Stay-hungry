#learning_rate=0.01,optim=SGD
learning_rate = 0.01
model = linear_model().cuda()
loss = nn.CrossEntropyLoss()    
opt = optim.SGD(model.parameters(), lr=learning_rate)

for epoch in range(n_epochs):
    running_loss = []
    #data_train是一个划分了batch的数据加载器，每一个batch看作一个训练集进行训练
    for x, y in tqdm(data_train):
        x = Variable(x).cuda()
        y = Variable(y).cuda()
        model.train() #启用BatchNormalization和Dropout进行训练模式
        y_prediction = model(x)
        l = loss(y_prediction, y)
        opt.zero_grad() #将梯度设为0，因为每次训练把一个batch当作一个训练集进行训练
        l.backward() #反向传播计算梯度
        opt.step() #通过梯度下降进行一次参数更新，比如w=w-a*(grad(w))
        running_loss.append(float(l))
    running_acc = []
    for x, y in data_test:
        x = Variable(x).cuda()
        y = Variable(y).cuda()
        model.eval() #不启用BatchNormalization和Dropout进行测试模式
        y_prediction = model(x)
        y_prediction = torch.argmax(y_prediction, dim=1) #dim=1表示取每一行最大值的索引
        acc = float(torch.sum(y_prediction == y)) / batch_size_test
        running_acc.append(acc)

    print("#summary:% 4d %.4f %.2f%%" % (epoch, np.mean(running_loss), np.mean(running_acc)*100))

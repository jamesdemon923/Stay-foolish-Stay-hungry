import numpy as np
import matplotlib.pyplot as plt


def getDataSet():
    dataSet = np.loadtxt('C:\Users\94496\Desktop\机器学习\第二次作业\3.3\3.0Alpha.csv', delimiter=",")
    dataSet = np.insert(dataSet, 0, np.ones(dataSet.shape[0]), axis=1)
    dataArr = dataSet[:, :-1]
    labelArr = dataSet[:, -1]
    return dataArr, labelArr


def sigmoid(Z):
    return 1.0 / (1 + np.exp(-Z))


def newton(dataArr, labelArr):
    """
    calculate logistic parameters by newton method

    :param dataArr: input data set with shape (m, n)
    :param labelArr: the label of data set with shape (m, 1)

    :return: returns the parameters obtained by newton method
    """
    m, n = dataArr.shape
    labelArr = labelArr.reshape(-1, 1)
    beta = np.ones((n, 1))
    errList = [] # save error history

    z = np.dot(dataArr, beta)
    oldLbeta = 0
    # shape (m, 1)
    newLBetaMat = -labelArr * z + np.log(1 + sigmoid(z))
    newLBeta = np.sum(newLBetaMat)
    it = 0
    while abs(oldLbeta - newLBeta) > 1e-5:
        it += 1
        # py0 = p(y=0|x) with shape (m,1)
        py0 = sigmoid(-np.dot(dataArr, beta))
        py1 = 1 - py0
        # 'reshape(n)' get shape (n,); 'np.diag' get diagonal matrix with shape (m,m)
        p = np.diag((py0 * py1).reshape(m))

        # shape (m,n)
        dBetaMat = -dataArr * (labelArr - py1)
        # first derivative with shape (1, n)
        dBeta = np.sum(dBetaMat, axis=0, keepdims=True)
        # second derivative with shape (n, n)
        dBeta2 = dataArr.T.dot(p).dot(dataArr)
        dBeta2Inv = np.linalg.inv(dBeta2)
        # (n,1) (n,1)          (n,n)    (n,1)
        beta = beta - np.dot(dBeta2Inv, dBeta.T)

        z = np.dot(dataArr, beta)
        oldLbeta = newLBeta
        newLBetaMat = -labelArr * z + np.log(1 + sigmoid(z))
        newLBeta = np.sum(newLBetaMat)

        pre = predict(beta, dataArr)
        errorRate = cntErrRate(pre, labelArr)
        errList.append(errorRate)
    print("newton iteration is ", it)
    return beta, errList


def gradDescent(dataArr, labelArr, alpha, T):
    """
    calculate logistic parameters by gradient descent

    :param dataArr: input data set with shape (m, n)
    :param labelArr: the label of data set with shape (m, 1)
    :param alpha: step length (learning rate)
    :param T: iteration
    :return: parameters
    """
    m, n = dataArr.shape
    labelArr = labelArr.reshape(-1, 1)
    errList = []

    beta = np.ones((n, 1))
    for t in range(T):
        # py0 = p(y=1|x) with shape (m,1)
        py1 = sigmoid(np.dot(dataArr, beta))
        dBetaMat = -dataArr * (labelArr - py1)
        # shape (1,n)
        dBeta = np.sum(dBetaMat, axis=0, keepdims=True)
        beta -= alpha * dBeta.T

        # test code
        pre = predict(beta, dataArr)
        errorRate = cntErrRate(pre, labelArr)
        errList.append(errorRate)

    return beta, errList


def predict(beta, dataArr):
    preArr = sigmoid(np.dot(dataArr, beta))
    preArr[preArr > 0.5] = 1
    preArr[preArr <= 0.5] = 0

    return preArr


def cntErrRate(preLabel, label):
    """
    calculate error rate
    :param preLabel: predict label
    :param label: real label
    :return: error rate
    """
    m = len(preLabel)
    cnt = 0.0

    for i in range(m):
        if preLabel[i] != label[i]:
            cnt += 1.0
    return cnt / float(m)


def main():
    dataArr, labelArr = getDataSet()

    # newton
    betaNew, errNew = newton(dataArr, labelArr)
    print("newton error rate is ", errNew[-1])

    # gradient descent
    T = 500
    learningRate = 0.001
    betaGrad, errGrad = gradDescent(dataArr, labelArr, learningRate , T )
    print("gradient descent error rate is ", errGrad[-1])

    # positive points and negative points
    posPoints = dataArr[labelArr > 0.5]
    negPoints = dataArr[labelArr < 0.5]
    # plot decision boundary
    plt.figure()
    plt.scatter(posPoints[:, 1], posPoints[:, 2])
    plt.scatter(negPoints[:, 1], negPoints[:, 2])
    x1 = np.linspace(0, 1, 100)
    x2New = -(betaNew[0] + betaNew[1] * x1) / betaNew[2]
    x2Grad = -(betaGrad[0] + betaGrad[1] * x1) / betaGrad[2]
    plt.plot(x1, x2New, label="newton method")
    plt.plot(x1, x2Grad, label="gradient descent")
    plt.xlabel("x1")
    plt.xlabel("x2")
    plt.title("decision boundary")
    plt.legend()

    # plot newton Ein
    length = len(errNew)
    x1 = np.linspace(1, length+1, length)
    plt.figure()
    plt.plot(x1, errNew, label="newton method")
    plt.xlabel("t")
    plt.ylabel("Ein")
    plt.title("newton method Ein")
    plt.legend()

    # plot gradient decent Ein
    plt.figure()
    x1 = np.linspace(1, T+1, T)
    plt.plot(x1, errGrad, label="gradient descent")
    plt.xlabel("t")
    plt.ylabel("Ein")
    plt.title("gradient descent Ein")
    plt.legend()

    plt.show()


if __name__ == '__main__':
    main()
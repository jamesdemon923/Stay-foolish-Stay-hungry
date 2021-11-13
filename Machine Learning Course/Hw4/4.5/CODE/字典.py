import numpy as np
import matplotlib.pyplot as plt
from pylab import *
import pandas as pd

# 特征字典
featureDic = {
    '色泽': ['浅白', '青绿', '乌黑'],
    '根蒂': ['硬挺', '蜷缩', '稍蜷'],
    '敲声': ['沉闷', '浊响', '清脆'],
    '纹理': ['清晰', '模糊', '稍糊'],
    '脐部': ['凹陷', '平坦', '稍凹'],
    '触感': ['硬滑', '软粘']}

# ***********************画图***********************
# **********************start***********************

# 定义文本框和箭头格式
decisionNode = dict(boxstyle="sawtooth", fc="0.8")
leafNode = dict(boxstyle="round4", fc="0.8")
arrow_args = dict(arrowstyle="<-")
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 没有这句话汉字都是口口


# mpl.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题


def plotMidText(cntrPt, parentPt, txtString):
    xMid = 2 * (parentPt[0] - cntrPt[0]) / 5.0 + cntrPt[0]
    yMid = 2 * (parentPt[1] - cntrPt[1]) / 5.0 + cntrPt[1]
    createPlot.ax1.text(xMid, yMid, txtString, fontsize=20)


def plotNode(nodeTxt, centerPt, parentPt, nodeType):  # 绘制带箭头的注解
    createPlot.ax1.annotate(nodeTxt,
                            xy=parentPt,
                            xycoords="axes fraction",
                            xytext=centerPt,
                            textcoords="axes fraction",
                            va="center",
                            ha="center",
                            bbox=nodeType,
                            arrowprops=arrow_args,
                            fontsize=12)


def getNumLeafs(myTree):  # 获取叶节点的数目
    numLeafs = 0
    firstStr = list(myTree.keys())[0]
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if type(secondDict[key]).__name__ == 'dict':
            numLeafs += getNumLeafs(secondDict[key])
        else:
            numLeafs += 1
    return numLeafs


def getTreeDepth(myTree):  # 获取树的层数
    maxDepth = 0
    firstStr = list(myTree.keys())[0]
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if type(secondDict[key]).__name__ == 'dict':
            thisDepth = 1 + getTreeDepth(secondDict[key])
        else:
            thisDepth = 1
        if thisDepth > maxDepth: maxDepth = thisDepth
    return maxDepth


def plotTree(myTree, parentPt, nodeTxt):
    numLeafs = getNumLeafs(myTree)
    getTreeDepth(myTree)
    firstStr = list(myTree.keys())[0]
    cntrPt = (plotTree.xOff + (1.0 + float(numLeafs)) / 2.0 / plotTree.totalW,
              plotTree.yOff)
    plotMidText(cntrPt, parentPt, nodeTxt)
    plotNode(firstStr, cntrPt, parentPt, decisionNode)
    secondDict = myTree[firstStr]
    plotTree.yOff = plotTree.yOff - 1.0 / plotTree.totalD
    for key in secondDict.keys():
        if type(secondDict[key]).__name__ == 'dict':
            plotTree(secondDict[key], cntrPt, str(key))
        else:
            plotTree.xOff = plotTree.xOff + 1.0 / plotTree.totalW
            plotNode(secondDict[key], (plotTree.xOff, plotTree.yOff),
                     cntrPt, leafNode)
            plotMidText((plotTree.xOff, plotTree.yOff), cntrPt, str(key))
    plotTree.yOff = plotTree.yOff + 1.0 / plotTree.totalD


def createPlot(inTree):
    fig = plt.figure(1, figsize=(600, 30), facecolor='white')
    fig.clf()
    axprops = dict(xticks=[], yticks=[])
    createPlot.ax1 = plt.subplot(111, frameon=False, **axprops)
    plotTree.totalW = float(getNumLeafs(inTree))
    plotTree.totalD = float(getTreeDepth(inTree))
    plotTree.xOff = -0.5 / plotTree.totalW
    plotTree.yOff = 0.9
    plotTree(inTree, (0.5, 0.9), '')
    plt.show()


# ***********************画图***********************
# ***********************end************************


def getDataSet():
    """
    get watermelon data set 3.0 alpha.
    :return: 编码好的数据集以及特征的字典。
    """
    dataSet = [
        ['青绿', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', 0.697, 0.460, 1],
        ['乌黑', '蜷缩', '沉闷', '清晰', '凹陷', '硬滑', 0.774, 0.376, 1],
        ['乌黑', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', 0.634, 0.264, 1],
        ['青绿', '蜷缩', '沉闷', '清晰', '凹陷', '硬滑', 0.608, 0.318, 1],
        ['浅白', '蜷缩', '浊响', '清晰', '凹陷', '硬滑', 0.556, 0.215, 1],
        ['青绿', '稍蜷', '浊响', '清晰', '稍凹', '软粘', 0.403, 0.237, 1],
        ['乌黑', '稍蜷', '浊响', '稍糊', '稍凹', '软粘', 0.481, 0.149, 1],
        ['乌黑', '稍蜷', '浊响', '清晰', '稍凹', '硬滑', 0.437, 0.211, 1],
        ['乌黑', '稍蜷', '沉闷', '稍糊', '稍凹', '硬滑', 0.666, 0.091, 0],
        ['青绿', '硬挺', '清脆', '清晰', '平坦', '软粘', 0.243, 0.267, 0],
        ['浅白', '硬挺', '清脆', '模糊', '平坦', '硬滑', 0.245, 0.057, 0],
        ['浅白', '蜷缩', '浊响', '模糊', '平坦', '软粘', 0.343, 0.099, 0],
        ['青绿', '稍蜷', '浊响', '稍糊', '凹陷', '硬滑', 0.639, 0.161, 0],
        ['浅白', '稍蜷', '沉闷', '稍糊', '凹陷', '硬滑', 0.657, 0.198, 0],
        ['乌黑', '稍蜷', '浊响', '清晰', '稍凹', '软粘', 0.360, 0.370, 0],
        ['浅白', '蜷缩', '浊响', '模糊', '平坦', '硬滑', 0.593, 0.042, 0],
        ['青绿', '蜷缩', '沉闷', '稍糊', '稍凹', '硬滑', 0.719, 0.103, 0]
    ]

    features = ['色泽', '根蒂', '敲声', '纹理', '脐部', '触感', '密度', '含糖量']
    # features = ['color', 'root', 'knocks', 'texture', 'navel', 'touch', 'density', 'sugar']

    # #得到特征值字典，本来用这个生成的特征字典，还是直接当全局变量方便
    # featureDic = {}
    # for i in range(len(features)):
    #     featureList = [example[i] for example in dataSet]
    #     uniqueFeature = list(set(featureList))
    #     featureDic[features[i]] = uniqueFeature

    # 每种特征的属性个数
    numList = []  # [3, 3, 3, 3, 3, 2]
    for i in range(len(features) - 2):
        numList.append(len(featureDic[features[i]]))

    dataSet = np.array(dataSet)
    return dataSet[:, :-1], dataSet[:, -1], features


# data, classLabel, feature = getDataSet()
# print(data)
# print(classLabel)
# print(feature)


def newData():
    """
    利用pandas将分类变量转化为数值变量。将分类变量进行one-hot编码。
    :return: 变量全为数值的变量，以及新的特征标签。
    """
    dataSet, classLabel, features = getDataSet()
    df = pd.DataFrame(dataSet)
    df.columns = features
    # 类别变量转化为数字变量
    # features = ['色泽', '根蒂', '敲声', '纹理', '脐部', '触感', '密度', '含糖量']
    # features = ['color', 'root', 'knocks', 'texture', 'navel', 'touch', 'density', 'sugar']
    # 色泽
    color = pd.get_dummies(df.色泽, prefix="色泽")
    # 根蒂
    root = pd.get_dummies(df.根蒂, prefix="根蒂")
    # 敲声
    knocks = pd.get_dummies(df.敲声, prefix="敲声")
    # 纹理
    texture = pd.get_dummies(df.纹理, prefix="纹理")
    # 脐部
    navel = pd.get_dummies(df.脐部, prefix="脐部")
    # 触感
    touch = pd.get_dummies(df.触感, prefix="触感")
    # 密度和含糖量
    densityAndsugar = pd.DataFrame()
    densityAndsugar["密度"] = df.密度
    densityAndsugar["含糖量"] = df.含糖量
    # 融合
    newData = pd.concat([color, root, knocks, texture, navel, touch, densityAndsugar], axis=1)
    newFeatures = list(newData.columns)
    newData = np.asarray(newData, dtype="float64")
    classLabel = np.asarray(classLabel, dtype="int").reshape(-1, 1)

    # 新的特征数据和类融合
    newDataSet = np.concatenate((newData, classLabel), axis=1)
    # 在第一列添加1
    newDataSet = np.insert(newDataSet, 0,
                           np.ones(dataSet.shape[0]),
                           axis=1)

    return newDataSet, newFeatures


# data, feature = newData()
# print(data)
# print(feature)


# 对率回归
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
    errList = []  # save error history

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
    # errList = []

    beta = np.ones((n, 1))
    for t in range(T):
        # py0 = p(y=1|x) with shape (m,1)
        py1 = sigmoid(np.dot(dataArr, beta))
        dBetaMat = -dataArr * (labelArr - py1)
        # shape (1,n)
        dBeta = np.sum(dBetaMat, axis=0, keepdims=True)
        beta -= alpha * dBeta.T

        # test code
        # pre = predict(beta, dataArr)
        # errorRate = cntErrRate(pre, labelArr)
        # errList.append(errorRate)

    return beta


# dataSet, features = newData()
# testBeta = gradDescent(dataSet[:, :-1], dataSet[:, -1], 0.1, 500)
# print(testBeta)


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


def majorityCnt(classList):
    classCount = {}
    for vote in classList:
        if vote not in classCount:
            classCount[vote] = 0
        classCount[vote] += 1
    # classCount.items()将字典的key-value对变成元组对，如{'a':1, 'b':2} -> [('a',1),('b',2)]
    # operator.itemgetter(1)按照第二个元素次序进行排序
    # reverse=True表示从大大到小。[('b',2), ('a',1)]
    sortedClassCount = sorted(classCount.items(),
                              key=operator.itemgetter(1),
                              reverse=True)
    return sortedClassCount[0][0]  # 返回第0个元组的第0个值


def splitDataSet(dataSet, bestBeta):
    """
    将数据分为两部分
    :param dataSet:
    :param bestBeta:
    :return:
    """
    dot = np.dot(dataSet[:, :-1], bestBeta).flatten()
    dataSet1 = dataSet[dot <= 0]
    dataSet2 = dataSet[dot > 0]
    return dataSet1, dataSet2


# # 用来保存beta
# class TreeNode:
#     def __init__(self):
#         self.beta = beta
#         self.classLabel = -1
#         self.left = None
#         self.right = None
# 定义节点类的版本，这一版本在节点处保存权重，容易计算精确度。
# def createTreeV2(dataSet, features):
#     classList = dataSet[:, -1].tolist()
#     if classList.count(classList[0]) == len(classList):
#         leaf = TreeNode()
#         leaf.classLabel = classList[0]
#         return leaf
#     if len(dataSet[0]) == 1:
#         leaf = TreeNode(-1)
#         leaf.classLabel = majorityCnt(classList)
#         return leaf
#
#     bestBeta = gradDescent(dataSet[:, :-1], dataSet[:, -1], 0.1, 500)
#
#     Node = TreeNode()
#     subDataIs, subDataNotIs = splitDataSet(dataSet, bestBeta)
#     Node.left = createTreeV2(subDataIs, features)
#     Node.right = createTreeV2(subDataNotIs, features)
#
#     return Node


def createTree(dataSet, features):
    classList = dataSet[:, -1].tolist()
    if classList.count(classList[0]) == len(classList):
        return classList[0]
    if len(dataSet[0]) == 1:
        return majorityCnt(classList)

    bestBeta = gradDescent(dataSet[:, :-1], dataSet[:, -1], 0.1, 500)
    # 得到节点txt
    txt = ""
    for i in range(len(bestBeta)):
        if i == 0:
            continue
        if bestBeta[i] > 0:
            txt += "+" + str(bestBeta[i][0]) + "x" + features[i - 1] + '\n'
        else:
            txt += str(bestBeta[i][0]) + "x" + features[i - 1] + '\n'
    txt += "<=" + str(-bestBeta[0][0])

    myTree = {txt: {}}
    subDataIs, subDataNotIs = splitDataSet(dataSet, bestBeta)
    myTree[txt]['是'] = createTree(subDataIs, features)
    myTree[txt]['否'] = createTree(subDataNotIs, features)

    return myTree


def main():
    dataSet, features = newData()
    myTree = createTree(dataSet, features)
    print(myTree)
    createPlot(myTree)


if __name__ == '__main__':
main()
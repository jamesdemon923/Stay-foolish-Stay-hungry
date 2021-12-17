'''
# 汽车调度问题的最优化
# 采用遗传算法进行编程
'''

from tqdm import tqdm
import numpy as np
import random as rd
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt


class vehicleRoutingProblem(object):

    # 初始化参数
    def __init__(self, file_address, car_load_max, car_speed, oper_dist_cost,
                oper_veh_cost, wait_time_cost,delay_time_cost,
                 popsize, chrom_length, prob_cross, prob_mut):
        self.file_address = file_address # 文件地址
        self.car_load_max = car_load_max # 车辆最大载荷
        self.car_speed = car_speed # 车速
        self.oper_dist_cost = oper_dist_cost  # 运行单位距离成本
        self.oper_veh_cost = oper_veh_cost  # 启用单位车辆成本
        self.wait_time_cost = wait_time_cost  # 等待单位时间成本
        self.delay_time_cost = delay_time_cost  # 延误单位时间成本
        self.popsize = popsize # 种群大小
        self.chrom_length = chrom_length # 每条染色体的基因位数
        self.prob_cross = prob_cross # 交叉概率
        self.prob_mut = prob_mut # 变异概率
        self.car_num = 0 # 车辆数

    # 导入原始数据
    def loadOriginalData(self):
        self.df = pd.read_csv(self.file_address, header=0)

    # 对原始数据进行绘图
    def plotOriginalData(self):
        # 绘图
        plt.figure('各个运营点位置')
        matplotlib.rcParams['font.family'] = 'SimHei'
        matplotlib.rcParams['font.sans-serif'] = ['SimHei']
        plt.scatter(self.df.iloc[0, 1], self.df.iloc[0, 2], marker='^', s=40, c='r')
        plt.scatter(self.df.iloc[1:, 1], self.df.iloc[1:, 2], marker='*', s=25, c='b')
        plt.title('各个运营点的具体位置', fontsize=20)
        # 加入text
        label = 0
        for x, y in zip(self.df.iloc[:, 1], self.df.iloc[:, 2]):
            plt.text(x + 0.3, y + 0.3, label, fontsize=14, color='k', fontweight='heavy')
            label += 1
        plt.xlabel('横坐标', fontsize=15)
        plt.ylabel('纵坐标', fontsize=15) # fontsize设置'纵坐标'这三个字的大小
        plt.tick_params(labelsize=15) # 设置X轴和Y轴刻度值的大小
        plt.grid()
        plt.show()

    # 定义一个函数，该函数用于创建一个字典，将各个点的位置与各个点的坐标关联起来
    # 该字典的键是位点序号，值是一个包含两个元素的元组(包括横坐标和纵坐标)
    # 包括起始点的位置
    def locDict(self):
        self.loc_dict = {}
        for i, loc in zip(self.df.iloc[:, 0], zip(self.df.iloc[:, 1], self.df.iloc[:, 2])):
            self.loc_dict[i] = loc

    # 定义一个函数，该函数用于创建一个字典，将各个销售点和其需求量关联起来
    # 该字典不包含起始点位置，即不包含位点0
    def demandDict(self):
        self.demand_dict = {}
        for x, y in zip(self.df.iloc[1:, 0], self.df.iloc[1:, 3]):
            self.demand_dict[x] = y

    # 定义一个函数，该函数用于创建一个字典，将各个销售点的最早接受时间、最晚接受时间和服务时间
    # 该字典包含起始点位置，即包含位点0
    # 该字典键是位点序号，值是一个包含三个元素元组（分别是最早接受时间、最晚接受时间和服务时间）
    def timeDict(self):
        self.time_dict = {}
        for x, y in zip(self.df.iloc[:, 0], zip(self.df.iloc[:, 4], self.df.iloc[:, 5], self.df.iloc[:, 6])):
            self.time_dict[x] = y

    # 定义一个函数将所有的染色体进行车辆分配，用字典保存
    # 该字典键为染色体的序号，值为分配的车辆列表
    def vehAllocDict(self, population):
        veh_alloc_dict = {}
        for i in range(self.popsize):
            chrom = population[i, :]
            list = []
            cum1 = 0
            cum2 = self.time_dict[0][0]
            count1 = 0
            count2 = 0
            while count1 < self.chrom_length:
                for j in range(count1, self.chrom_length):
                    cum1 += self.demand_dict[chrom[j]]
                    if j==count1:
                        cum2 += ((self.loc_dict[chrom[j]][0] - self.loc_dict[0][0]) ** 2 + (self.loc_dict[chrom[j]][1] - self.loc_dict[0][1]) ** 2) ** 0.5 / self.car_speed + self.time_dict[chrom[j]][2]
                    elif j == self.chrom_length - 1:
                        cum2 += 0
                    else:
                        cum2 += ((self.loc_dict[chrom[j]][0] - self.loc_dict[chrom[j+1]][0]) ** 2 + (self.loc_dict[chrom[j]][1] - self.loc_dict[chrom[j+1]][1]) ** 2) ** 0.5 / self.car_speed ++ self.time_dict[chrom[j+1]][2]

                    cum2 += ((self.loc_dict[chrom[j]][0] - self.loc_dict[0][0]) ** 2 + (self.loc_dict[chrom[j]][1] - self.loc_dict[0][1]) ** 2) ** 0.5 / self.car_speed + self.time_dict[chrom[j]][2]

                    if cum1 > self.car_load_max or cum2 > self.time_dict[0][1]:
                        list.append(chrom[count1:j])
                        cum1 = 0
                        cum2 = 0
                        count1 = j
                        count2 = 0
                        break
                    elif j==self.chrom_length - 1:
                        list.append(chrom[count1:])
                        count1 = j + 1
                        break
                    cum2 -= ((self.loc_dict[chrom[j]][0] - self.loc_dict[0][0]) ** 2 + (self.loc_dict[chrom[j]][1] - self.loc_dict[0][1]) ** 2) ** 0.5 / self.car_speed + self.time_dict[chrom[j]][2]

            veh_alloc_dict[i] = list

            r'''
            # 每条染色体每辆车的车载量计算
            for element in list:
                sum = 0
                for i in element:
                    sum += self.demand_dict[i]
                print(sum)
            r'''

        return veh_alloc_dict

    # 定义一个函数，计算每条染色体的每辆车的距离，用字典表示
    # 该字典的键为染色体序号，值为一个元组，大小为车辆数，元组内的每个元素为列表（里面的元素为每两个位点之间的距离）
    def distDict(self, veh_alloc_dict):
        dist_dict = {}
        begin_x = self.loc_dict[0][0] # 起点x轴坐标
        begin_y = self.loc_dict[0][1] # 终点y轴坐标
        for k in range(self.popsize):
            list = []
            chrom_alloc = veh_alloc_dict[k]
            for array in chrom_alloc:
                array_length = len(array)
                list_dist = []
                if array_length!=1:
                    # 计算去的路上与位点0链接的一个点距离
                    x1 = self.loc_dict[array[0]][0]
                    y1 = self.loc_dict[array[0]][1]
                    dist = ((x1 - begin_x) ** 2 + (y1 - begin_y) ** 2) ** 0.5
                    list_dist.append(dist)
                    for i in range(array_length - 1):
                        x3 = self.loc_dict[array[i]][0]
                        y3 = self.loc_dict[array[i]][1]
                        x4 = self.loc_dict[array[i + 1]][0]
                        y4 = self.loc_dict[array[i + 1]][1]
                        dist = ((x3 - x4) ** 2 + (y3 - y4) ** 2) ** 0.5
                        list_dist.append(dist)
                    # 计算回来的路上与位点0链接的一个点距离
                    x2 = self.loc_dict[array[-1]][0]
                    y2 = self.loc_dict[array[-1]][1]
                    dist = ((x2 - begin_x) ** 2 + (y2 - begin_y) ** 2) ** 0.5
                    list_dist.append(dist)
                    list.append(list_dist)
                else:
                    x = self.loc_dict[array[0]][0]
                    y = self.loc_dict[array[0]][1]
                    dist = ((x - begin_x) ** 2 + (y - begin_y) ** 2) ** 0.5
                    list.append([dist, dist])
            dist_dict[k] = list
        return dist_dict

    # 定义目标函数的计算式
    # 定义其为一个字典
    # 键为染色体序号，值为总的花费值
    def allCost(self, veh_alloc_dict, dist_dict):
        all_cost = {}
        # 位点0的起始和截止时间
        time_begin = self.time_dict[0][0] + 0 # 起始时间
        time_end = self.time_dict[0][1] # 截止时间
        for i in range(self.popsize):
            # 运输成本
            all_dist = sum([sum(dist_car) for dist_car in dist_dict[i]])
            dist_cost = all_dist * self.oper_dist_cost # 该染色体所有车辆运输成本费用
            # 启动成本
            car_num = len(dist_dict[i]) # 该条染色体车辆数
            start_cost = car_num * self.oper_veh_cost # 该条染色体所有车辆操作费用
            # 等待费用+延迟费用
            wait_delay_cost = 0 # 等待费用+延迟费用
            wait_cost = 0 # 延迟费用
            delay_cost = 0 # 延迟费用
            time_stamp = 0  # 时间戳
            for j in range(car_num):
                # car_num 表示第i条染色体具有的车辆数
                car_time_list = list(np.array(dist_dict[i][j]) / self.car_speed) # 每两个位点之间的运行时间
                # 先计算起始点
                wait_cost += wait_time_cost * max((self.time_dict[veh_alloc_dict[i][j][0]][0] - (car_time_list[0] + time_begin)), 0)
                delay_cost += delay_time_cost * max(((car_time_list[0] + time_begin) - self.time_dict[veh_alloc_dict[i][j][0]][1]), 0)
                wait_delay_cost += wait_cost + delay_cost
                time_stamp += time_begin + car_time_list[0] + self.time_dict[veh_alloc_dict[i][j][0]][2]

                for k in range(len(car_time_list)-2):
                    time_stamp += car_time_list[k + 1]
                    wait_cost += wait_time_cost * max((self.time_dict[veh_alloc_dict[i][j][k + 1]][0] - time_stamp), 0)
                    time_stamp += self.time_dict[veh_alloc_dict[i][j][k + 1]][2]
                    delay_cost += delay_time_cost * max((time_stamp - self.time_dict[veh_alloc_dict[i][j][k + 1]][1]), 0)
                    wait_delay_cost += wait_cost + delay_cost

            all_cost[i] = dist_cost + start_cost + wait_delay_cost
        return  all_cost

    # 初始化种群
    def popInitial(self):
        population = np.ones((self.popsize, self.chrom_length), dtype=int)
        for i in range(self.popsize):
            chrom = rd.sample(range(1, self.chrom_length + 1), self.chrom_length)
            population[i, :] = np.array(chrom)
        return population

    # 适应度计算
    # 返回一个列表
    def adaptability(self, all_cost):
        adaptability_list = []
        for value in all_cost.values():
            adaptability_list.append(1 / value)
        return adaptability_list

    # 累计适应度计算
    def cumAdaptability(self, adaptability_list):
        cumadaptability = []
        cum = 0
        for element in adaptability_list:
            cum += element
            cumadaptability.append(cum)
        return cumadaptability

    # 选择操作
    def chooseChrom(self, population, cumadaptability):
        # 对cumadaptability进行归一化
        choose_chrom = np.ones((self.popsize, self.chrom_length), dtype=int)
        normalized_cumadaptability = [i / max(cumadaptability) for i in cumadaptability]
        # 选择
        a = [0]
        a.extend(normalized_cumadaptability) # 在最前面增加元素0
        normalized_cumadaptability = a[:]
        for k in range(self.popsize):
            random_num = np.random.random()
            for i in range(len(normalized_cumadaptability) - 1):
                if random_num > normalized_cumadaptability[i] and random_num <= normalized_cumadaptability[i + 1]:
                    choose_chrom[k, :] = population[i, :]
                    break
        return choose_chrom

    # 交叉操作
    # PMX交叉，即部分匹配交叉
    def crossChrom(self, choose_chrom):
        cross_chrom = choose_chrom[:, :]
        for i in range(int(self.popsize / 2) - 1):
            random_num = np.random.random()
            if random_num <= self.prob_cross:
                # 进行交叉运算
                # 确定两条染色体
                list1 = []
                list2 = []
                chrom1 = choose_chrom[i, :] # 第一条染色体
                chrom2 = choose_chrom[2 * i + 1, :] # 第二条染色体
                # 确定交叉位点，两个
                cross_point1 = np.random.randint(0, self.chrom_length - 1) # 确定交叉位点1
                cross_point2 = np.random.randint(0, self.chrom_length - 1) # 确定交叉位点2
                while cross_point2==cross_point1:
                    cross_point2 = np.random.randint(0, self.chrom_length - 1)  # 确定交叉位点2
                if cross_point2 < cross_point1:
                    cross_point1, cross_point2 = cross_point2, cross_point1
              #  print(cross_point1)
              #  print(cross_point2)
                # 取出两条染色体的交叉片段
                cross_fragment1 = chrom1[cross_point1:cross_point2 + 1]
                cross_fragment2 = chrom2[cross_point1:cross_point2 + 1]
              # 对chrom1和chrom2去重
                for element1 in chrom2:
                    if element1 not in cross_fragment1:
                        list1.append(element1)
                for element2 in chrom1:
                    if element2 not in cross_fragment2:
                        list2.append(element2)
                chrom3 = np.array(list1)
                chrom4 = np.array(list2)
                chrom5 = np.append(chrom3[0:cross_point1], cross_fragment1)
                chrom6 = np.append(chrom4[0:cross_point1], cross_fragment2)
                chrom7 = np.append(chrom5, chrom3[cross_point1:])
                chrom8 = np.append(chrom6, chrom4[cross_point1:])
                cross_chrom[i, :] = chrom7
                cross_chrom[2 * i + 1, :] = chrom8
        return cross_chrom

    # 变异操作
    def mutChrom(self, cross_chrom):
        mut_chrom = cross_chrom[:]
        for i in range(self.popsize):
            mut_num = np.random.random()
            if mut_num <= self.prob_mut:
                mut_point1 = np.random.randint(0, self.chrom_length - 1)
                mut_point2 = np.random.randint(0, self.chrom_length - 1)
                while mut_point2 == mut_point1:
                    mut_point2 = np.random.randint(0, self.chrom_length - 1)  # 确定交叉位点2
                if mut_point2 < mut_point1:
                    mut_point1, mut_point2 = mut_point2, mut_point1
                mut_chrom[i, mut_point1], mut_chrom[i, mut_point2] = mut_chrom[i, mut_point2], mut_chrom[i, mut_point1]
        return mut_chrom

    @staticmethod
    # 创建一个静态方法，用于计算最值
    def bestIndividual(iteration_num):
        init_pop = vrp.popInitial()  # 初始化之后的种群，二维数组
        population = init_pop
        list = []
        p_bar = tqdm(range(iteration_num))
        p_bar.set_description('正在迭代：')
        for i in p_bar:
            veh_alloc_dict = vrp.vehAllocDict(population=population)
            dist_dict = vrp.distDict(veh_alloc_dict)
            all_cost = vrp.allCost(veh_alloc_dict, dist_dict)
            list.append(min(all_cost.values()))
            adaptability_list = vrp.adaptability(all_cost)
            cumadaptability = vrp.cumAdaptability(adaptability_list)
            choose_chrom = vrp.chooseChrom(population=population, cumadaptability=cumadaptability)
            cross_chrom = vrp.crossChrom(choose_chrom)
            mut_chrom= vrp.mutChrom(cross_chrom)
            population = mut_chrom
        matplotlib.rcParams['font.family'] = 'SimHei'
        matplotlib.rcParams['font.sans-serif'] = ['SimHei']
        matplotlib.rcParams['axes.unicode_minus'] = False  # 解决负号问题
        plt.plot(range(iteration_num), list)
        plt.xlabel('迭代次数', fontsize=15)
        plt.ylabel('总费用', fontsize=15)
        plt.title('车辆调度与总费用的关系', fontsize=20)
        plt.grid()
        plt.tick_params(labelsize=15)  # 设置X轴和Y轴刻度值的大小
        plt.show()
        return population


    # 获取最小花费数据
    def bestScheme(self, population):
        veh_alloc_dict = vrp.vehAllocDict(population=population)
        dist_dict = vrp.distDict(veh_alloc_dict)
        all_cost = vrp.allCost(veh_alloc_dict, dist_dict)
        # 获取最小发费时候的索引和最小花费
        min_cost = all_cost[0]
        min_index = 0
        for i in range(self.popsize):
            if min_cost > all_cost[i]:
                min_cost = all_cost[i]
                min_index = i
        print("最小花费是第%d条染色体，且最小花费为%s" % (min_index, all_cost[min_index]))
        print("车辆调度情况是: ", veh_alloc_dict[min_index])
        return veh_alloc_dict[min_index]
    # 对最优调度数据进行绘图

    def plotBestScheme(self, best_veh_alloc):
        # 绘图
        plt.figure('车辆调度')
        matplotlib.rcParams['font.family'] = 'SimHei'
        matplotlib.rcParams['font.sans-serif'] = ['SimHei']
        plt.scatter(self.df.iloc[0, 1], self.df.iloc[0, 2], marker='^', s=40, c='r')
        plt.scatter(self.df.iloc[1:, 1], self.df.iloc[1:, 2], marker='*', s=25, c='b')
        plt.title('车辆调度情况', fontsize=20)
        # 加入text
        label = 0
        for x, y in zip(self.df.iloc[:, 1], self.df.iloc[:, 2]):
            plt.text(x + 0.3, y + 0.3, label, fontsize=14, color='k', fontweight='heavy')
            label += 1
        plt.xlabel('横坐标', fontsize=15)
        plt.ylabel('纵坐标', fontsize=15)  # fontsize设置'纵坐标'这三个字的大小
        plt.tick_params(labelsize=15)  # 设置X轴和Y轴刻度值的大小
        plt.grid()

        # 绘制各个车辆的行使路线
        color = ['r', 'k', 'y', 'b', 'g', 'purple', 'c', 'b']
        k = 0
        for car in best_veh_alloc:
            x_list = []
            y_list = []
            x_list.append(self.loc_dict[0][0])
            y_list.append(self.loc_dict[0][1])
            for loc_point in car:
                x_list.append(self.loc_dict[loc_point][0])
                y_list.append(self.loc_dict[loc_point][1])
            x_list.append(self.loc_dict[0][0])
            y_list.append(self.loc_dict[0][1])
            plt.plot(x_list, y_list, linewidth=1, c=color[k], linestyle='--')
            k += 1
        plt.show()

if __name__ == '__main__':
    # 原始数据地址
    file_address = r'C:\Users\94496\Desktop\Mycode\Data mining\GA\25 location information.csv'
    # 模型参数设置
    car_load_max = 200  # 车辆最大载荷
    car_speed = 1  # 车速
    oper_dist_cost = 8  # 运行单位距离成本
    oper_veh_cost = 60  # 启用单位车辆成本
    wait_time_cost = 0.5  # 等待单位时间成本
    delay_time_cost = 1.5  # 延误单位时间成本
    # 遗传算法参数设置
    iteration_num = 2000  # 迭代次数
    popsize = 100  # 种群大小
    chrom_length = 25  # 染色体基因位点数
    prob_cross = 0.25  # 交叉概率
    prob_mut = 0.05  # 变异概率

    # 需要运行的语句
    # 创建一个汽运调度对象
    vrp = vehicleRoutingProblem(file_address = file_address, car_load_max=car_load_max, car_speed=car_speed,
                                oper_dist_cost =oper_dist_cost,
                                oper_veh_cost=oper_veh_cost, wait_time_cost=wait_time_cost,
                                delay_time_cost=delay_time_cost, popsize=popsize,
                                chrom_length=chrom_length, prob_cross=prob_cross,
                                prob_mut=prob_mut)

    # 需要调用的方法，用于数据的处理
    vrp.loadOriginalData()  # 导入原始数据，并保留为df
    vrp.demandDict()  # 将原始数据处理得到一个字典，键为位点序号，值为需求量，不包含起始位置
    vrp.timeDict()  # 将原始数据处理得到一个字典，键为位点序号，值为包含三个元素（起始时间、截止时间、卸货时间）的元组
    vrp.locDict()  # 将原始数据处理得到一个字典，键为位点序号，值为包含两个元素（X坐标和Y坐标）的元组
    population = vrp.bestIndividual(iteration_num=iteration_num)
    best_veh_alloc = vrp.bestScheme(population)
    vrp.plotBestScheme(best_veh_alloc)


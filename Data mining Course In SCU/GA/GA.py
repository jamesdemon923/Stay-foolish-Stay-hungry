
"""
Time    :   2021/3/28 21:51
Author  :   Cheng Min
File    :   GA.py
Software:   PyCharm
"""

"""遗传算法用于催化剂设计"""

import numpy as np
from matplotlib import pyplot as plt


class GA(object):
    def __init__(self, n_pop, n_length, n_component, prob_crossover, prob_mutate):
        """初始化

        :param n_pop:种群大小
        :param n_length:染色体长度
        :param n_component: 催化剂组分个数
        :param prob_crossover: 交叉概率
        :param prob_mutate: 变异概率
        """
        self.n_pop = n_pop
        self.n_length = n_length
        self.n_component = n_component
        self.prob_cross = prob_crossover
        self.prob_mutate = prob_mutate

    def pop_ini(self):
        """种群初始化

        :return:None
        """
        self.population = np.random.randint(0, 2, (self.n_pop, self.n_component, self.n_length), dtype=np.int)
        return None

    @staticmethod
    def __get_components_ratio(population):
        """计算各组分比例

        :return:催化剂中各个组分的占比，type:array
        """
        list_commopent_ratio = []
        for individual in population:
            list_temp = []
            for i in range(individual.shape[0]):
                temp = 0
                for j in range(individual.shape[1]):
                    temp += np.power(2, individual.shape[1]-j-1) * individual[i, j]
                list_temp.append(temp)
            list_temp_ratio = [_/sum(list_temp) for _ in list_temp]
            list_commopent_ratio.append(list_temp_ratio)
        return np.array(list_commopent_ratio)

    @staticmethod
    def __get_fitness(arr_comp_ratio):
        list_fitness = []
        for i in range(arr_comp_ratio.shape[0]):
            x_v = arr_comp_ratio[i, 0]
            x_mg = arr_comp_ratio[i, 1]
            x_mo = arr_comp_ratio[i, 2]
            x_mn = arr_comp_ratio[i, 3]
            x_fe = arr_comp_ratio[i, 4]

            selectivity = 66 * x_v * x_mg * (1 - x_v - x_mg) + 2 * x_mo - 0.1 * x_mn - 0.1 * x_fe
            convertion = 66 * x_v * x_mg * (1 - x_v - x_mg) - 0.1 * x_mo + 1.5 * x_mn + 1.5 * x_fe
            yield_catalyst = selectivity * convertion
            list_fitness.append(yield_catalyst)
        return np.array(list_fitness)

    def cal_fitness(self, population):
        """适应度计算

        :return:种群适应度
        """
        arr_comp_ratio = self.__get_components_ratio(population)  # 催化剂中各组分的占比
        population_fitness = self.__get_fitness(arr_comp_ratio)  # 种群中每个个体的适应度

        return population_fitness

    @staticmethod
    def cal_cum_fitness(population_fitness):
        """计算累计概率

        :param population_fitness:适应度
        :return:累计概率
        """
        cum_prop = np.cumsum(population_fitness) / population_fitness.sum()
        return cum_prop

    def choose(self, cum_prop):
        """基于轮盘赌选择

        :return:选择的种群
        """
        list_choosed_index = []
        for i in range(len(cum_prop)):
            random_num = np.random.random()
            if random_num <= cum_prop[0]:
                list_choosed_index.append(0)
            else:
                for j in range(len(cum_prop) - 1):
                    if (random_num > cum_prop[j]) & (random_num <= cum_prop[j + 1]):
                        list_choosed_index.append(j + 1)
        arr_index = np.array(list_choosed_index)
        choosed_population = self.population[arr_index]
        return choosed_population

    def crossover(self, choose_population):
        """交叉算子

        :param choose_population: 选择算子之后的染色体种群
        :return: 交叉算子之后的染色体种群
        """
        crossover_population = choose_population.copy()
        for i in range(int(np.around(len(crossover_population)/2))):
            random_number = np.random.random()
            if random_number <= self.prob_cross:
                chromsome_1 = crossover_population[i].flatten()
                chromsome_2 = crossover_population[len(crossover_population)-i-1].flatten()
                crossover_site = np.random.randint(1, len(chromsome_2-1))
                chromsome_1, chromsome_2 = np.append(chromsome_1[:crossover_site], chromsome_2[crossover_site:]), np.append(chromsome_2[:crossover_site], chromsome_1[crossover_site:])
                crossover_population[i] = chromsome_1.reshape(self.n_component, self.n_length)
                crossover_population[len(crossover_population)-i-1] = chromsome_2.reshape(self.n_component, self.n_length)
        return crossover_population

    def mutate(self, crossover_population):
        """变异算子

        :param crossover_population: 交叉算子之后的染色体种群
        :return: 变异算子之后的染色体种群
        """
        mutate_population = crossover_population.copy()
        for i in range(len(mutate_population)):
            random_number = np.random.random()
            if random_number < self.prob_mutate:
                chromsome = mutate_population[i].flatten()
                mutate_site = np.random.randint(0, len(chromsome))
                chromsome[mutate_site] = abs(chromsome[mutate_site] - 1)
                mutate_population[i] = chromsome.reshape(self.n_component, self.n_length)
            return mutate_population

    def update_population(self, mutate_population):
        """更新种群

        :param mutate_population:变异算子之后的染色体种群
        :return:None
        """
        new_pop = mutate_population.copy()
        orig_fitness = self.cal_fitness(self.population)
        new_fitness = self.cal_fitness(mutate_population)
        orig_max = orig_fitness.max()
        new_max = new_fitness.max()
        if orig_max > new_max:
            max_index = np.where(orig_fitness == orig_max)[0][0]
            temp = self.population[max_index]
        else:
            max_index = np.where(new_fitness == new_max)[0][0]
            temp = mutate_population[max_index]
        min_index = np.where(new_fitness == new_fitness.min())[0][0]
        new_pop[min_index] = temp
        self.population = new_pop
        return None


if __name__ == '__main__':
    # 参数输入
    number_population = 80
    number_length = 6
    prob_crossover = 0.8
    prob_mutate = 0.05
    iteration = 300
    n_component = 6  # V、Mg、Mo、Mn、Fe和Ga
    # GA
    GA_test = GA(number_population, number_length, n_component, prob_crossover, prob_mutate)
    GA_test.pop_ini()
    list_max_values = []
    for i in range(iteration):
        population_fitness = GA_test.cal_fitness(GA_test.population)
        list_max_values.append(max(population_fitness))  # 保存每次迭代过程中的最大值
        cum_prop = GA_test.cal_cum_fitness(population_fitness)
        choosed_population = GA_test.choose(cum_prop)
        crossover_population = GA_test.crossover(choosed_population)
        mutate_population = GA_test.mutate(crossover_population)
        GA_test.update_population(mutate_population)
        GA_test.update_population(mutate_population)
    print(max(list_max_values))

    # 绘图
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 添加字体
    plt.plot(range(iteration), list_max_values, linewidth=2, color='b')
    plt.xlabel('迭代次数', fontsize=14)
    plt.ylabel('收率/%', fontsize=14)
    plt.title('收率与迭代次数的关系', fontsize=14)
    plt.show()

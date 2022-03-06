import matplotlib.pyplot as plt
import numpy as np
from pylab import mpl
class myLagrange:
    def __init__(self, data_x, data_y):
        self.data_x = data_x
        self.data_y = data_y
        self.parameters = []
        if len(data_x) != len(data_y):
            raise Exception('length error!')
        self.k = len(data_x)
        self.__initLagrangeInterpolation()

    # 拉格朗日插值l算子初始化
    def __initLagrangeInterpolation(self):
        for i in range(0, self.k):
            mul = 1
            for j in range(0, self.k):
                if i != j:
                    mul *= self.data_x[i] - self.data_y[j]
            self.parameters.append(self.data_y[i] / mul)

    # 计算插值运算的结果 L(x)
    def calculateLagrangeInterpolation(self, elem_x):
        res = 0
        for i in range(0, self.k):
            mul = 1
            for j in range(0, self.k):
                if i != j:
                    mul *= elem_x - self.data_x[j]
            res += mul * self.parameters[i]
        return res

    def draw(self, data_x, data_y):
        x = np.arange(-100, 100, 10)
        y = [self.calculateLagrangeInterpolation(item) for item in x]
        plt.plot(x, y, label="Lagrange曲线", color="black")
        plt.scatter(data_x, data_y, label="检验数据", color="red")
        mpl.rcParams['font.sans-serif'] = ['SimHei']
        mpl.rcParams['axes.unicode_minus'] = False
        plt.legend(loc=0)
        plt.show()
        return x, y


if __name__ == '__main__':
    x = np.random.randint(-100, 100, 5)
    y = np.random.randn(1, 5)[0]
    o = myLagrange(x, y)
    print('利用拉格朗日插值算法拟合的函数值：\n{}'.format(o.calculateLagrangeInterpolation(80)))
    tx, ty = o.draw(x, y)
    info = np.transpose([tx, ty])
    np.savetxt('info.csv', info, fmt='%f', delimiter=' ')
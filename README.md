# ML_Algorithm
一些基本机器学习算法的实现
##模拟退火Kmeans算法
1. 初始化温度$$$T_0$$$，退火速度$$$a$$$和最大退火次数
2. 对于某一温度$$$t$$$，在步骤(3)~(5)进行迭代，直到达到最大迭代次数，跳到步骤(6)
3. 随机产生$$$k$$$个中心点，确定每一个样本所属的类别，计算新的目标函数值$$$J_w'$$$
4. 计算新的目标函数值与当前目标函数值的差$$$\Delta J$$$
5. 判断$$$\Delta J$$$是否小于0。若$$$\Delta J < 0$$$，则接受新解，即将新解作为当前解。若$$$\Delta J \geq 0$$$，则以概率$$$p$$$接受新解，$$$p = e^{\frac{-\Delta J}{Kt}}$$$，$$$K$$$为玻尔兹曼常数，$$$t$$$为当前温度
6. 判断是否达到最大退火次数，是则结束算法，输出分类结果；否则根据退火公式对温度$$$t$$$进行退火，返回步骤(3)继续迭代

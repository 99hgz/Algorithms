import numpy as np
import matplotlib.pyplot as plt

x = [1,2,3,4,5,6,7]
y = [7.82,7.93,7.98,7.99,7.92,7.91,7.80,7.71]
mean_x = sum(x) / len(x)
mean_y = sum(y) / len(y)
sum_x = 0.0
sum_y = 0.0
for i in range(0, len(x)):
    sum_x += (x[i] - mean_x) * (y[i] - mean_y)
    sum_y += (x[i] - mean_x) ** 2

k = sum_x / sum_y
b = mean_y - k * mean_x

y2 = []
# y2 对真实数据的回归
for i in range(0, len(x)):
    y2.append(round(b + k*x[i], 2))

# y2 对 101 - 110 天内的预测
last_x = x[-1]
for i in range(1, 11):
    x.append(last_x + i)
    y2.append(round(b + k*(last_x + i), 2))
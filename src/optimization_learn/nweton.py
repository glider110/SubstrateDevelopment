'''
Author: glider
Date: 2023-07-12 10:26:51
LastEditTime: 2023-07-12 10:39:07
FilePath: /SubstrateDevelopment/src/optimization_learn/nweton.py
Version:  v0.01
Description: https://blog.csdn.net/bitcarmanlee/article/details/121501106?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-3-121501106-blog-97242815.235%5Ev38%5Epc_relevant_anti_t3_base&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-3-121501106-blog-97242815.235%5Ev38%5Epc_relevant_anti_t3_base&utm_relevant_index=4
************************************************************************
Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
************************************************************************
'''


import numpy as np

def newton_sqrt():
    x = 4
    num = 1.0
    eps = 1e-4
    n = 100
    for i in range(n):
        num = 0.5 * (num + x / num)
        pred_x = num * num
        if abs(x - pred_x) < eps:
            break

    print("sqrt num is: ", num)




def f(x, y):
    return (1 - x) ** 2 + 100 * (y - x * x) ** 2


def grad(x, y):
    return np.array([2 * x - 2 + 400 * x * (x * x - y),
      200 * (y - x * x)])


def H(x, y):
    return np.array([[1200 * x * x - 400 * y + 2, -400 * x],
                     [-400 * x, 200]])


def delta_newton(x, y):
    alpha = 1.0
    inverse_H = np.linalg.inv(H(x, y))
    delta = alpha * np.dot(inverse_H, grad(x, y)) # 
    return delta


def solution():
    n = 256
    x = np.array([-0.1, 0.6])
    tol = 0.00001
    for i in range(100):
        delta = delta_newton(x[0], x[1])
        if abs(delta[0]) < tol and abs(delta[1]) < tol:
            break

        x = x - delta
        print("i is: ", i, ", x is: ", x)

solution()

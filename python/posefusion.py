#coding=utf-8
# coding=UTF-8
 
import cv2
import numpy as np
from matplotlib import pyplot as plt
import pylab
 
#从.txt中读取数据 的函数
 
def loadData(fileName):
    inFile = open(fileName, 'r')#以只读方式打开某filename文件
    #定义2个空的list，用来存放文件中的数据
    t = []
    accx = []
    accy = []
    accz = []
    #gyrox = []
    #gyroy = []
    #gyroz = []
    for line in inFile:
        trainingSet = line.split(', ')#对于上面数据每一行，按' '把数据分开，这里是分成两部分
        t.append(float(trainingSet[0]))#第一部分，即文件中的第一列数据逐一添加到list t中
        accx.append(float(trainingSet[1]))#第二部分，即文件中的第二列数据逐一添加到list accx中
        accy.append(float(trainingSet[2]))#第三部分，即文件中的第三列数据逐一添加到list accy中
        accz.append(float(trainingSet[3]))#第四部分，即文件中的第四列数据逐一添加到list accz中
        #gyrox.append(float(trainingSet[4]))#第五部分，即文件中的第五列数据逐一添加到list gyrox中
        #gyroy.append(float(trainingSet[5]))#第六部分，即文件中的第六列数据逐一添加到list gyroy中
        #gyroz.append(float(trainingSet[6]))#第七部分，即文件中的第七列数据逐一添加到list gyroz中
 
    return (t, accx, accy, accz)
#, gyrox, gyroy, gyroz)
 
#绘制该文件中的数据 的函数
def plotData(x, y):
    length = len(y)
    pylab.plot(x, y,'r--') 
    pylab.xlabel('time')
    pylab.ylabel('gyro')
    
 
 
 
(t, accx, accy, accz) = loadData('fusion.txt')
#print(t, accx)
 
pylab.figure(1)
plotData(accx,accy)
 
pylab.figure(2)
plotData(t,accz)



pylab.show()

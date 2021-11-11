from numpy import *
import operator
from os import listdir
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator 


def file2matrix(filename):
    fr = open(filename)
    numberOfLines = len(fr.readlines())         #get the number of lines in the file
    returnMat = zeros((numberOfLines,3))        #prepare matrix to return
    fr = open(filename)
    index = 0
    for line in fr.readlines():
        line = line.strip()
        listFromLine = line.split(' ')
        returnMat[index,:] = listFromLine[0:3]       
        index += 1
    return returnMat

dataMat = file2matrix("/home/admins/桌面/github/SubstrateDevelopment/config/location.txt")
x=[]
z=[]
for i in range(len(dataMat)):
    x.append(dataMat[i][0])
    z.append(dataMat[i][2])

print(x)
print(z)

plt.ion()#开始交互模式



while 1:
    for j in range(len(dataMat)):
        plt.title("3D-TOF LOCATION") #图标题
        plt.xlabel("x") #X轴标签
        plt.ylabel("z")  #Y轴标签
 
        # fig = plt.figure() 
        # ax = fig.add_subplot(1,1,1) 
        plt.gcf()   # 生成画布的大小
        plt.tick_params(labelsize=10)
        # 绘制刻度网格线
        ax = plt.gca()
        # ax.xaxis.set_major_locator(plt.MultipleLocator())
        # ax.xaxis.set_minor_locator(plt.MultipleLocator())
        # ax.yaxis.set_major_locator(	plt.MultipleLocator(0.05))
        # ax.yaxis.set_minor_locator(	plt.MultipleLocator(0.05))
        # plt.grid(which='major')
        # plt.grid(which='minor')
        
        spacing = 0.05 # This can be your user specified spacing. 
        minorLocator = MultipleLocator(spacing) 
        # Set minor tick locations. 
        ax.yaxis.set_minor_locator(minorLocator) 
        ax.xaxis.set_minor_locator(minorLocator) 
        # Set grid to use minor tick locations. 
        ax.grid(which = 'minor',axis='both', linewidth=0.75, linestyle='-', color='orange') 


        plt.xlim((-1, 1))
        plt.ylim((-1, 1))
        plt.plot(x[0:j], z[0:j],"b--", marker='o', mec='g', mfc='w',linewidth=1)
        plt.show()
        plt.pause(1)
        if j==len(dataMat)-1:
              plt.pause(6)
        plt.clf() # 清图。
        

# from matplotlib import pyplot as plt 
# from matplotlib.ticker import MultipleLocator 
# import numpy as np 

# # Two example plots 
# fig = plt.figure() 
# ax = fig.add_subplot(1,1,1) 
# # ax2 = fig.add_subplot(2,2,2) 

# spacing = 0.5 # This can be your user specified spacing. 
# minorLocator = MultipleLocator(spacing) 
# ax.plot(9 * np.random.rand(10),9 * np.random.rand(10)) 
# # Set minor tick locations. 
# ax.yaxis.set_minor_locator(minorLocator) 
# ax.xaxis.set_minor_locator(minorLocator) 
# # Set grid to use minor tick locations. 
# ax.grid(which = 'minor') 



# plt.show() 












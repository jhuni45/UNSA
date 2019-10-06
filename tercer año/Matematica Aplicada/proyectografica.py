# Matematica Aplicada a la Computación
# Autores:
# Basurco Cayllahua Eduardo
# Chavez Cruz Jhunior

from __future__ import division
from numpy import matrix
import numpy as np
import matplotlib.pyplot as plt
import math


matrizT=input("ingresa numero de variables de T")
def matrixH1(k):
    H1 = []
    for m in range(int(k)): 
        row = []               
        for n in range(2):
            x=input("valor: ")
            float(x)
            row.append(x)
            
        H1.append(row)
    return H1
#pprint.pprint(matrixH1(matrizT))
#T=matrix(matrixH1(matrizT)).astype('float')
    
#T=matrix([[math.cos(math.pi/2),math.sin(math.pi/2)],[math.cos(math.pi/2),math.sin(math.pi/2)]])
#T=matrix([[np.sin(),np.cos()],[np.cos(),np.sin()]])
T=matrix([[-3/5,4/5],[4/5,3/5]])
plt.ion()

#creamos los puntos
p1=matrix([[0],[0]]).astype('float')
p2=matrix([[0],[2]]).astype('float')
p3=matrix([[3],[0]]).astype('float')
p4=matrix([[3],[2]]).astype('float')
p5=matrix([[0],[0]]).astype('float')
p6=matrix([[0],[0]]).astype('float')
p7=matrix([[0],[0]]).astype('float')
p8=matrix([[0],[0]]).astype('float')
p9=matrix([[0],[0]]).astype('float')
p10=matrix([[0],[0]]).astype('float')

p1Y=matrix(p1).astype('float')
p2Y=matrix(p2).astype('float')
p3Y=matrix(p3).astype('float')
p4Y=matrix(p4).astype('float')
p5Y=matrix(p5).astype('float')
p6Y=matrix(p6).astype('float')
p7Y=matrix(p7).astype('float')
p8Y=matrix(p8).astype('float')
p9Y=matrix(p9).astype('float')
p10Y=matrix(p10).astype('float')

p1X=T*p1
p2X=T*p2
p3X=T*p3
p4X=T*p4
p5X=T*p5
p6X=T*p6
p7X=T*p7
p8X=T*p8
p9X=T*p9
p10X=T*p10

aux=0
tope=100
while aux!=tope:
    plt.clf()
    p1Y=matrix([[p1Y.item(0,0)+((p1X.item(0,0)-p1.item(0,0))/tope)],[p1Y.item(1,0)+((p1X.item(1,0)-p1.item(1,0))/tope)]])
    p2Y=matrix([[p2Y.item(0,0)+((p2X.item(0,0)-p2.item(0,0))/tope)],[p2Y.item(1,0)+((p2X.item(1,0)-p2.item(1,0))/tope)]])
    p3Y=matrix([[p3Y.item(0,0)+((p3X.item(0,0)-p3.item(0,0))/tope)],[p3Y.item(1,0)+((p3X.item(1,0)-p3.item(1,0))/tope)]])
    p4Y=matrix([[p4Y.item(0,0)+((p4X.item(0,0)-p4.item(0,0))/tope)],[p4Y.item(1,0)+((p4X.item(1,0)-p4.item(1,0))/tope)]])
    p5Y=matrix([[p5Y.item(0,0)+((p5X.item(0,0)-p5.item(0,0))/tope)],[p5Y.item(1,0)+((p5X.item(1,0)-p5.item(1,0))/tope)]])
    p6Y=matrix([[p6Y.item(0,0)+((p6X.item(0,0)-p6.item(0,0))/tope)],[p6Y.item(1,0)+((p6X.item(1,0)-p6.item(1,0))/tope)]])
    p7Y=matrix([[p7Y.item(0,0)+((p7X.item(0,0)-p7.item(0,0))/tope)],[p7Y.item(1,0)+((p7X.item(1,0)-p7.item(1,0))/tope)]])
    p8Y=matrix([[p8Y.item(0,0)+((p8X.item(0,0)-p8.item(0,0))/tope)],[p8Y.item(1,0)+((p8X.item(1,0)-p8.item(1,0))/tope)]])
    p9Y=matrix([[p9Y.item(0,0)+((p9X.item(0,0)-p9.item(0,0))/tope)],[p9Y.item(1,0)+((p9X.item(1,0)-p9.item(1,0))/tope)]])
    p10Y=matrix([[p10Y.item(0,0)+((p10X.item(0,0)-p10.item(0,0))/tope)],[p10Y.item(1,0)+((p10X.item(1,0)-p10.item(1,0))/tope)]])
    aux+=1      
    #list_of_lists = [[p1X.item(0),p1X.item(1)],p2X,p3X,p4X,p5X,p6X,p7X,p8X,p9X,p10X,p1X]    
    #x_list = [x for [x, y] in list_of_lists]
    #y_list = [y for [x, y] in list_of_lists]
    #plt.plot(x_list, y_list,"red")
    list_of_lists1 = [[p1Y.item(0),p1Y.item(1)],p2Y,p3Y,p4Y,p5Y,p6Y,p7Y,p8Y,p9Y,p10Y,p1Y]    
    x_list1 = [x for [x, y] in list_of_lists1]
    y_list1 = [y for [x, y] in list_of_lists1]
    plt.plot(x_list1, y_list1,"green")

    plt.axis([0,10,0,10])
    plt.show()
    plt.pause(0.05)
    
while True:
    plt.pause(0.05)




import matplotlib.pyplot as plt
from numpy.random import rand
#from numpy import square, sqrt
import pandas as pd
from itertools import cycle
import numpy as np
def graficar(C,num):
    fig = plt.figure()
    cycol = cycle('bgrwykm')
    for cluster in C:
        col =[rand(1),rand(1),rand(1)]      
        #print (cluster)       
        plt.scatter([i[1] for i in cluster],[i[2] for i in cluster], c=next(cycol))
    #plt.show()
    file = 'imgdbscan/imgdbc' + str(num) + '.png'
    fig.savefig(file, dpi=fig.dpi)

def regionQuery(P, eps, D): 
    neighbourPts = []
    for point in D:
        #print point        
        if np.sqrt(np.square(P[1] - point[1]) + np.square(P[2] - point[2]))<eps:
            neighbourPts.append(point)
    return neighbourPts

def DBSCAN(D, eps, MinPts):
    noise = []
    visited = []
    C = []
    c_n = -1
    n=0
    for point in D:
        visited.append(point) #marking point as visited
    #   print point     
        neighbourPts = regionQuery(point, eps, D)
        if len(neighbourPts) < MinPts:
            noise.append(point)
        else:
            C.append([])            
            c_n+=1
            expandCluster(point, neighbourPts, C, c_n,eps, MinPts, D, visited)
        if n%20==0:
            graficar(C,n)
        n+=1
    graficar(C,n)
   # print "no. of clusters: " , len(C)  
    #print "length of noise:", len(noise)
            

def expandCluster(P, neighbourPts, C, c_n,eps, MinPts, D, visited):
    
    C[c_n].append(P)
    for point in neighbourPts:
        if point not in visited:
            visited.append(point) 
            neighbourPts_2 = regionQuery(point, eps, D)
            if len(neighbourPts_2) >= MinPts:
                neighbourPts += neighbourPts_2
        if point not in (i for i in C):
            C[c_n].append(point)
 
#eps = input("enter eps")
archivo = pd.read_csv('iris.csv', header = None)

archivoTam = len(archivo)
axisX = archivo.values[:archivoTam]

#axisX= np.insert(axisX, 0, 1,axis=1).astype('float64')
entrenarCarac = axisX[:,:-1]
sd  = axisX[:,-1]

a=axisX[:,:-3] #primera contra segunda
b=axisX[:,1:3] #segunda contra tercera
c=axisX[:,2:4] #tercera contra cuarta

X=c
Y=sd
l=[]
for i in range(len(X)):
    l.append([i,X[i][0],X[i][1]])
DBSCAN(l,1.9,4)
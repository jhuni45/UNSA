from math import log
import sys
import numpy as np
import random
import pandas as pd

df=pd.read_csv("iris.csv")

"""def dtheta():
    pass
def theta(x,thet):
    return np.dot(theta,x)
def S(x,thet):
    return(1/(1+np.exp(-1*theta(x,thet))))

def error(s,y):
    pass 
theta0=random.randint(1,100)
theta1=random.randint(1,100)
umbral= 0.05
error =0
alfa = 0.5
while(error<umbral):
    theta0 = theta0 - alfa*dtheta0
    theta1 = theta1 - alfa*dtheta1
    theta2 = theta2 - alfa*dtheta2]"""
class rl:
    x = np.array(df[['SepalLength','SepalWidth','PetalLength']])
    y = np.array(df[['TrainingClass']])
    alfa = 0.5
    umbral= 0.01
    thetas = []
    def __init__(self,filename):
         nombre = filename
    def h(self,vc):
        return sum(e[0]*e[1] for e in zip(self.thetas,vc))
    def s(self,vc):
        return(1/(1+np.exp(-1*h(vc) )))

regresion = rl(df)
n=len(rl.x)
error = -1/(n)*(rl.y[0]*log(rl.s(rl.thetas,rl.x),10) + (1-rl.y[0]*log(rl.s(rl.thetas,rl.x),10)))
while(error>rl.umbral):
    pass
    #error = error+0
    #rl.thetas[] 
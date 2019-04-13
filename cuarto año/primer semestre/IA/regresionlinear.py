from random import randint
import pandas as pd
from math import *
from decimal import *
import matplotlib.pyplot as plt
import numpy as np

from sklearn import preprocessing, svm
from sklearn.linear_model  import LinearRegression
from sklearn import datasets, linear_model 
from sklearn.model_selection import train_test_split

def sumError(theta1,theta2,X,Y):
	res=0;
	for i in range (0,len(X)):
		res+=pow((theta1+theta2*X[i])-Y[i],2)
	return res

def calcularError(theta1,theta2,X,Y):
	h=sumError(theta1,theta2,X,Y)
	return Decimal(h)/Decimal(2*len(X))	

def derivada(theta1,theta2,X,Y,index):
	res=0
	for i in range(0,len(X)):
		if index==0:
			res+=((theta1+theta2*X[i])-Y[i])*(1)
		else:
			res+=((theta1+theta2*X[i])-Y[i])*X[i]
	return Decimal(res)/Decimal(len(X))

def graficar(theta1,theta2, X, Y, num):
	tx = np.arange(Decimal(0.0),Decimal(5.0),Decimal(0.1))
	ty = tx * theta2 + theta1
	fig = plt.figure()
	plt.plot(X,Y,'ro',tx,ty)
	file = 'imgLineal/img' + str(num) + '.png'
	fig.savefig(file, dpi=fig.dpi)

def regression(X,Y,umbral):
	theta1=1
	theta2=1
	error=calcularError(theta1,theta2,X,Y)
	num=0
	graficar(theta1,theta2,X,Y,num)
	num+=1
	while Decimal(error)>Decimal(umbral):
		theta1=theta1-(Decimal(0.1)* derivada(theta1,theta2,X,Y,0))
		theta2=theta2-(Decimal(0.1)* derivada(theta1,theta2,X,Y,1))
		error=calcularError(theta1,theta2,X,Y)
		graficar(theta1,theta2,X,Y,num)	
		num+=1
pointsX=[]
pointsY=[]
aux=randint(1,30)
# while 0 < aux:
# 	pointsX.append(randint(0,aux))
# 	pointsY.append(randint(0,aux))
# 	aux-=1
aux=1
while aux < 6:
	pointsX.append(aux)
	pointsY.append(aux)
	aux+=1
print pointsY
print pointsX
df=pd.read_csv("forestfires.csv")

X_train, X_test, y_train, y_test=train_test_split(pointsX,pointsY,test_size=0.3, random_state=10)

#regression(pointsX,pointsY,Decimal(0.00001))
import numpy as np
import matplotlib.pyplot as plt
from random import randint
from decimal import *
from math import *

def multi(A,B):
	res = [0] * len(B[0])
	for i in range(0,1):
		for j in range(0,len(B[0])):
			for k in range(0,len(A)):
				res[j] += A[k] * B[k][j];
	return res

def calcularError(thetas,X,Y):
	h=multi(thetas,X)
	suma=0
	for i in range(0, len(h)):
		suma+= pow(h[i]-Y[i],2) 
	return Decimal(suma)/Decimal(2*len(h))	

def derivada(thetas,X,Y,index):
	h=multi(thetas,X)
	res=0
	for i in range(0,len(h)):
		if index==0:
			res+=((h[i]-Y[i]))*1
		else:
			res+=((h[i]-Y[i]))*X[index][i]
	return Decimal(res)/Decimal(len(h))

def graficar(thetas, X, Y, num):
	tx = np.arange(Decimal(0.0),Decimal(5.0),Decimal(0.1))
	ty = tx * thetas[1] + thetas[0]
	fig = plt.figure()
	plt.plot(X[1],Y,'ro',tx,ty)
	file = 'imgLineal/img' + str(num) + '.png'
	fig.savefig(file, dpi=fig.dpi)

def llenarthetas(thetas):
	for i in range (0,len(thetas)):
		thetas[i]=randint(0,10);

def regression(X,Y,umbral):
	thetas=[0]*len(X)
	llenarthetas(thetas)
	error=calcularError(thetas,X,Y)
	num=0
	graficar(thetas,X,Y,num)
	num+=1
	while Decimal(error)>Decimal(umbral):
		temp=[0]* len(thetas)
		temp[0] = thetas[0] - Decimal(0.1) * derivada(thetas, X, Y, 0)
		for i in range(0,len(thetas)):
			temp[i]=thetas[i]-Decimal(0.1)* derivada(thetas,X,Y,i)
		thetas=temp
		error=calcularError(thetas,X,Y)
		#graficar(thetas,X,Y,num)	
		num+=1
		print ("error", error)
	graficar(thetas,X,Y,num)


getcontext().prec = 20
X=[[1,1,1,1,1],[1,2,3,4,5]]
Y=[1,2,3,4,5]
regression(X,Y,0.00001)
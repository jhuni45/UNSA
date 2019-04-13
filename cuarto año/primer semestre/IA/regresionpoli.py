from random import randint
from math import *
from decimal import *
import matplotlib.pyplot as plt
import numpy as np

regV=1000
alfa =0.1

def graficar(theta, X, Y, num):
	tx = np.arange(0.0,5.0,0.1)
	ty = tx * theta[0]+ theta[1]+theta[2]+ theta[3]
	fig = plt.figure()
	plt.plot(X,Y,'ro',tx,ty)
	file = 'imgPoli/img' + str(num) + '.png'
	fig.savefig(file, dpi=fig.dpi)

def llenarRandom(theta):
	for i in range(0,len(theta)):
		theta[i] = 1;

def regularizacion(theta):
	res=0
	for i in range(1,len(theta)):
		res+=theta[i]
	return Decimal(regV*res)/2*Decimal(len(theta))

def sumError(theta,X,Y):
	res=0;
	for i in range (0,len(X)):
		aux=0
		for j in range(0, len(theta)):
			aux+=theta[j]*Decimal(pow(X[i],j))
		res+=Decimal(pow(aux-Y[i],2))
		#print "aaaaaaaaa", res
	return res

def calculator (theta, X):
	sum=theta[0]
	for i  in range (1,len(theta)):
		sum+=theta[i]*(X**i)
	return sum

def sumaErrorDeri(theta,X,Y,index):
	res=0;
	for i in range (0,len(X)):
		# aux=0
		# for j in range(0, len(theta)):
		# 	aux+=theta[j]*Decimal(pow(X[i],j))
		res+=calculator(theta, X[i])-Y[i]
		res=pow(res,2)
		if index != 0:
			res*=X[i]
	return Decimal(res)/Decimal(len(X))

def calcularError(theta,X,Y):
	h=sumError(theta,X,Y)
	return Decimal(h)/Decimal(2*len(X))

def derivada(theta,X,Y,index):
	res=0
	for i in range(0,len(X)):		
		res+=(sumaErrorDeri(theta,X,Y,i)*Decimal(pow(X[i],index)))/Decimal(len(X))
	return Decimal(res)+((regV*theta[index])/Decimal(len(theta)))

def regression(X,Y,umbral):
	theta=[0]*len(X)
	llenarRandom(theta)
	error=calcularError(theta,X,Y)+regularizacion(theta)
	num=0
	print 'error ',error
	print 'umbral ',umbral
	graficar(theta,X,Y,num)
	num+=1
	while Decimal(error)>Decimal(umbral):
		print 'error ',error
		print 'umbral ',umbral
		for i in range(0,len(theta)):
			theta[i]=theta[i]-(Decimal(alfa)*Decimal(derivada(theta,X,Y,i)))
		error=calcularError(theta,X,Y)+regularizacion(theta)
		graficar(theta,X,Y,num)
		num+=1

pointsX=[1,2,3,4,5]
pointsY=[1,2,3,2,1]
aux=randint(1,30)
# while 0 < aux:
# 	pointsX.append(randint(0,aux))
# 	pointsY.append(randint(0,aux))
# 	aux-=1

aux=6
while aux < 6:
	pointsX.append(aux)
	pointsY.append(aux)
	aux+=1
print pointsY
print pointsX
theta=[1,2,3]
print calculator(theta,5)

# A=range(0,100)
# B=range(0,100)
# for i in range(0,len(B)):
# 	B[i]=calculator(theta,B[i])
# plt.plot(A,B)
#plt.show()

#regression(pointsX,pointsY,Decimal(0.00001))







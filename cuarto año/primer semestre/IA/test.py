from random import randint
from math import *
from decimal import *
import matplotlib.pyplot as plt
import numpy as np

def multiply(A,B):
	res = [0] * len(B[0])
	for i in range(0,1):
		for j in range(0,len(B[0])):
			for k in range(0,len(A)):
				res[j] += A[k] * B[k][j];
	return res

def llenarRandom(O):
	for i in range(0,len(O)):
		O[i] = randint(0,10);

def calcularError(O, X, Y):
	h = multiply(O,X)
	suma = 0
	for i in range(0,len(h)):
		suma += pow( h[i]-Y[i],2)
	return Decimal(suma) / Decimal(2 * len(h))

def derivada(O, X, Y, index):
	h = multiply(O,X)
	suma = 0
	for i in range(0,len(h)):
		if index == 0:
			suma += ( h[i]-Y[i] ) * 1
		else:
			suma += ( h[i]-Y[i]) * (X[index][i] * 1)
	return Decimal(suma) / Decimal(len(h))


def graficar(O, X, Y, num):
	tx = np.arange(Decimal(0.0),Decimal(5.0),Decimal(0.1))
	ty = tx * O[1] + O[0]
	fig = plt.figure()
	plt.plot(X[1],Y,'ro',tx,ty)
	file = ''
	if num < 10:
		file = 'img00' + str(num) + '.png'
	elif num < 100:
		file = 'img0' + str(num) + '.png'
	else:
		file = 'img' + str(num) + '.png'
	fig.savefig(file, dpi=fig.dpi)


def regresion(X, Y, umbral):
	t = [0] * len(X)
	llenarRandom(t)
	error = calcularError(t, X, Y)
	numGraf = 0;
	graficar(t, X, Y,numGraf)
	numGraf += 1
	while Decimal(error) > Decimal(umbral):
		temp = [0] * len(t)
		temp[0] = t[0] - Decimal(0.1) * derivada(t, X, Y, 0)
		for i in range(0,len(t)):
			print("error", error)
		 	temp[i] = t[i] - Decimal(0.1) * derivada(t, X, Y, i)
		t= temp
		error = calcularError(t, X, Y)
		#graficar(O, X, Y,numGraf)
		#numGraf += 1
		#print numGraf



getcontext().prec = 20
X = [[1,1,1,1,1],[1,2,3,4,5]]
Y = [1,2,3,4,5]
t = [0] * len(X)
regresion(X,Y,0.00001)
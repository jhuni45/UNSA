import numpy as np
from random import randint
from decimal import Decimal

def aumento(x):
	aux=np.zeros((len(x),3))
	for i in range (0,len(x)):
		aux[i][int(x[i])]=1
	return aux

def sigmoid(x):
	return 1.0/((1.0)+np.exp(-x))

def activation(x):
	aux=np.full((1,len(x[0])),1.0)
	for i in range(0,len(x[0])):
		aux[0][i]=sigmoid(x[0][i])
	return aux

#CREAMOS UNA CAPA CON N NEURONAS Y K PESOS AGREGANDO FILA B (valores 1)
def create_hidden(n,k):
	aux=np.full((k,n),1)
	for i in range (0,k):
		for j in range(0,n):
			aux[i][j]=randint(0,5)
	return aux

def sh(I,H):
	return np.dot(I,H)

def so(FSH,output):
	return np.dot(FSH,output)	

def sigmoidDer(A):
	return A * (1-A) 

def delta(so,sd):
	return (so-sd)*sigmoidDer(so)

def create_output(n,k):
	aux=np.full((k,n),1)
	for i in range (0,k):
		for j in range(0,n):
			aux[i][j]=randint(0,5)
	return aux

def error (s0,s1):
	return np.sum((np.square(s0-s1))/2.0)

def forward(WIH,WHO,input):
	#multiplicamos la entrada con la capa hidden - hallamos la funcion de activacion de SH
	FSH=activation(sh(input,WIH))
	FSH1=np.insert(FSH,0,1.0,axis=1)
	#multiplicamos FSH con las salidas - halamos la funcion de activacion de SO
	FSO=activation(so(FSH1,WHO))
	return FSH, FSO

def backward(I,sd,so,FSH1,output1,a1,alfa):
	deltaO=delta(so,sd)
	output1=output1-alfa*np.dot(deltaO.T,FSH1).T
	a1=a1-alfa*np.dot((np.dot(deltaO,output1.T)*sigmoidDer(FSH1)).T,I)

def train(input,Y,capas,alfa,iter):
	input1=np.insert(input,0,1.0,axis=1)

	WIH=create_hidden(capas,len(input1))
	WIH1=np.insert(WIH,0,1.0,axis=0) #esta se usa
	
	WHO=create_output(3,len(input))
	WHO1=np.insert(WHO,0,1.0,axis=0)
	
	umbral =0.01
	#error=errorF()
	while iter:
		#for i in range(0,len(input1)):
		FSH1, output=forward(WIH,WHO1,input1)
		backward(input,Y,output,FSH1,WIH1,alfa)
		error=errorF(Y)

alfa=0.01
capas=4

with open('irisfullshuf.csv', 'r') as f:
    l = np.array([[Decimal(num) for num in line.split(',')] for line in f if line.strip() != "" ])
#***********Entrenamiento************#
size=int(len(l)*0.7) #sacamos 70% del Data Set
xtrain=np.array(l[:size:,:4])
xtrain=xtrain.astype('float64')
#agregamos columna de 1
xtrain1=np.insert(xtrain,0,1.0,axis=1)

ytrain=np.array(l[:size:,4])

ytrain1=aumento(ytrain)
#************************************#
#*************Testing****************#
y_test=np.array(l[size:,4])
x_test=np.array(l[size:,:4])

#train(xtrain,ytrain1,4,0.01,100000)

#input=np.array([[1,2,3]])
#input1=np.insert(input,0,1.0,axis=1)

a=create_hidden(capas,len(xtrain[0]))
a1=np.insert(a,0,1.0,axis=0)

SH=sh(xtrain1,a1)
FSH=activation(SH)
FSH1=np.insert(FSH,0,1.0,axis=1)

output=create_output(3,capas)
output1=np.insert(output,0,1.0,axis=0)

SO=activation(so(FSH1,output1))
#SO1=np.insert(SO,0,1.0,axis=1)

deltaO=delta(SO,ytrain1)
output1=output1-alfa*np.dot(deltaO.T,FSH1).T
a1=a1-alfa*np.dot((np.dot(deltaO,output1.T)*sigmoidDer(FSH1)).T,input)
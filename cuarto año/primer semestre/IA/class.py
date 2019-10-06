from math import log,exp
import numpy as np
from random import randint
from decimal import Decimal
import matplotlib.pyplot as plt

#FUNCION PARA GRAFICAR
def graficar(thetas, X, Y):
    H=h(thetas,x)
    S=s(H)
    tx = np.arange(Decimal(0.0),Decimal(5.0),Decimal(0.1))
    ty = ((tx * thetas[1]) + thetas[0])/-thetas[2]
    #ty=Decimal(1.0)/(Decimal(1.0)+np.exp(Decimal(-1.0)*thetas[1]*(tx-thetas[0]))) 
    fig = plt.figure()
    
    classX=[]
    classY=[]
    class2X=[]
    class2Y=[]
    #SE GRAFICA CON COLORES PARA DIFERENCIAR LAS CLASES
    for i in range(len(X)):
        if Y[i]!=Y[0]:
            classX.append(X[i][1]) 
            classY.append(X[i][2])
        else:
            class2X.append(X[i][1])
            class2Y.append(X[i][2])
    plt.plot(classX,classY,'ro',class2X, class2Y,'g^', tx,ty)
    #file = 'imgV2' + str(num) + '.png'
    plt.show()
    #fig.savefig(file, dpi=fig.dpi)

def h_(V1,V2):
    return sum([e[0]*e[1] for e in zip(V1,V2)])

def h(thetas,X):
    return [h_(thetas,e) for e in X]

#FUNCION SIGNOIDEA
def s(H):
    return [Decimal(1.0) / Decimal(Decimal(1.0) + Decimal(exp(Decimal(-1.0) *e))) for e in H]

#FUNCION PARA CALCULAR EL ERROR
def errorf(x,y,thetas):
    H = h(thetas,x)
    S = s(H)
    acum=0
    #auxiliar=Decimal(s(x,thetas))
    for i in range(1,len(y)):
        a1=0
        a2=0
        if S[i]!=0:
            a1=Decimal(log(S[i]))
        if (1-S[i])!=0:
            a2 += Decimal(log(1-S[i]))  
        acum+=Decimal(y[i])* a1+ ((1-y[i])*a2)
    return Decimal(acum)*Decimal(-1.0/len(H))

def changethetas(x,y,thetas,alfa):
    H = h(thetas,x)
    S = s(H)
    temp=[0]*len(thetas)
    for j in range (0, len(thetas)):
        temp[j]=Decimal(sum([Decimal(alfa) * (S[i] - y[i]) * x[i][j] for i in range(0,len(y))])) / Decimal(len(H))
    return [thetas[i]-temp[i] for i in range (0,len(thetas))]


def matriz_confusion(thetas_train,x_test,y_test):
    H = h(thetas_train,x_test)
    S = s(H)
    clase_1_SI=0
    clase_2_SI=0
    clase_1_NO=0
    clase_2_NO=0
    for i in range(0,len(H)):
        if S[i]>=0.9:
            S[i]=1
        else:
            S[i]=0

    for i in range(0,len(H)):
        S[i]=int(S[i])
        if y_test[i]==S[i]:
            if S[i]==0:
                clase_1_SI+=1
            else:
                clase_2_SI+=1
        else:
            if y_test[i]==0:
                clase_1_NO+=1
            else:
                clase_2_NO+=1

    totalclase1=clase_1_NO+clase_1_SI
    totalclase2=clase_2_NO+clase_2_SI
    print "********Matriz Valores*******\n              Clase1              Clase2\n"
    print "Clase1       ",clase_1_SI,"              ",clase_1_NO,"\n"
    print "Clase2       ",clase_2_NO,"              ",clase_2_SI,"\n"
    print "*****************************"

    print "********Matriz Difusion*******\n             Clase1              Clase2\n"
    print "Clase1       ",(clase_1_SI*100)/round(Decimal(totalclase1)),"            ",(clase_1_NO*100)/round(Decimal(totalclase1)),"\n"
    print "Clase2       ",(clase_2_NO*100)/round(Decimal(totalclase2)),"            ",(clase_2_SI*100)/round(Decimal(totalclase2))   ,"\n"
    print "*****************************"

    print "Eficiencia= ", ((clase_1_SI*100)/totalclase1+((clase_2_SI*100)/totalclase2))/2.0
    print "*****************************"
    

def train(x,y,thetas):
    print ("THETAS",thetas)
    alfa=0.3
    umbral=0.17
    num=0
    error=errorf(x,y,thetas)
    tempError = error
    #print ("Error Inicial",error)
    #graficar(thetas,x,y,num)
    print "Calculando ..."
    while error>umbral: #and tempError >= error :
        tempError = error
        thetas=changethetas(x,y,thetas,alfa)
        error=errorf(x,y,thetas)
        #graficar(thetas,x,y,num)
        num=num+1
        #print error
    #print ("Error Final", error)
    #graficar(thetas,x,y,num)
    #print ("Y Final", y)
    return thetas

#***********
#Entrenamiento con las Dos primeras Clases (No se considera pues da 100% de eficiencia)
#with open('irisshuf.csv', 'r') as f:
#*****
#Usamos DataSet de las dos ultimas Clases de Flor (Encontraremos eficiencia distinta de 100%)
with open('irisshuf2.csv', 'r') as f:
    l = np.array([[Decimal(num) for num in line.split(',')] for line in f if line.strip() != "" ])

#***********Entrenamiento************#
size=int(len(l)*0.6) #sacamos 60% del Data Set
x=np.array(l[:size:,:4])
y=np.array(l[:size:,4])
#************************************#

#*************Testing****************#
y_test=np.array(l[size:,4])
x_test=np.array(l[size:,:4])
#************************************#
#*********Vector de Thetas***********#
#thetas=np.array([0,3,4,9])
thetas =np.array([randint(1,7),randint(1,7) ,randint(1,7) ,randint(1,7) ])

#*********Entrenamos el 60%**********#
thetas_train=train(x,y,thetas)

#******Predecimos con el 40%*********#
#*******Hallamos Datos de Matriz de Confusion******#
matriz_confusion(thetas_train,x_test,y_test)
#*****Graficamos el resultado de nuestro entrenamiento****#
graficar(thetas_train,x,y)

import numpy as np 
from matplotlib import pyplot as plt 
import random 
import math
import pandas as pd

def graficar(cluster,cluster1,cluster2,cluster3,nuevocentro,num):
    cluster1 = np.array(cluster1)
    cluster2 = np.array(cluster2)
    cluster3 = np.array(cluster3)
    fig = plt.figure()
    plt.scatter(cluster1[:,0], cluster1[:,1], color='red', s=20)
    plt.scatter(cluster2[:,0], cluster2[:,1], color='black',s=10)
    plt.scatter(cluster3[:,0], cluster3[:,1], color='blue',s=3)
    plt.scatter(nuevocentro[:,0], nuevocentro[:,1], marker='*', c='g', s=150)
    
    file = 'imgkmeans/imgcc' + str(num) + '.png'
    fig.savefig(file, dpi=fig.dpi)
    #plt.show()     

archivo = pd.read_csv('iris.csv', header = None)

archivoTam = len(archivo)
axisX = archivo.values[:archivoTam]

#axisX= np.insert(axisX, 0, 1,axis=1).astype('float64')
entrenarCarac = axisX[:,:-1]
sd  = axisX[:,-1]

a=axisX[:,:-3] #primera contra segunda
b=axisX[:,1:3] #segunda contra tercera
c=axisX[:,2:4] #tercera contra cuarta

#le cambias los puntos aleatorios por el iris y ya
number_cluster =3#  2 el numero de cluster en iris serian 3
centros = np.zeros((3,2))  #   2,2 primer 2 filas segundo 2 columnas primer 2 numeros de clusters segundo 2 #caracteristicas
puntosprueba = c #np.random.randn(200, 2) #el 2 son las caracteristicas
aux = np.zeros((3,1))#guardara la resta de puntos

for i in range(number_cluster):
    centros[i] = random.choice(puntosprueba)#estamos elijiendo random 2 centros en el iris serian 3
#cluster1 = np.array(centros[0])
#cluster2 = np.array(centros[1])
cluster1 = [centros[0]]
cluster2 = [centros[1]]
cluster3 = [centros[2]]
#plt.scatter(puntosprueba[:,0],puntosprueba[:,1],s=7)

#plt.scatter(centros[:,0], centros[:,1], marker='*', c='g', s=150)

nuevocentro = centros#elnuevo centro se ira actualizando en el bucle
antiguocentro  = np.zeros([number_cluster,2]) #primero son caracteristicas el segundo es el # de clusters
error = np.zeros([number_cluster,1])#el error 
for i in range(len(error)):
    error[i] = np.linalg.norm(nuevocentro[i]-antiguocentro[i])
n=0
while(error[0]>0.0000000001 or error[1]>0.0000000001 or error[2]>0.0000000001):
    #todo se realiza mientras el error != 0 
    for i in range(len(puntosprueba)):
        for j in range(len(centros)):
            
            #calcular la distancia minima entre x y los 2 centroides 
            aux[j] = np.linalg.norm(puntosprueba[i]-nuevocentro[j])
        #los meto en sus clusters respectivos
        minimo = min(aux)
        if(minimo==aux[0]):
            cluster1.append(puntosprueba[i])
        
        elif(minimo==aux[1]):
            cluster2.append(puntosprueba[i])

        elif(minimo==aux[2]):
            cluster3.append(puntosprueba[i])
                
    # por cada cluster calculo el promedio y actulizamos los centros y se repite
    cluster = [cluster1,cluster2,cluster3]
    graficar(cluster,cluster1,cluster2,cluster3,nuevocentro,n)
    n+=1
    mean = 100000
    nuevocentroaux = 0
    for i in range(len(antiguocentro)):
        antiguocentro[i] = nuevocentro[i]

    for i in range(len(cluster)):
        for j in range(len(cluster[i])):
            distancia = cluster[i][j]
            promedio =0
            for k in range(len(cluster[i])):
                for l in range(len(distancia)):
                    promedio = promedio + ((distancia[l]-cluster[i][k][l])*(distancia[l]-cluster[i][k][l]))
                #sqrt((xa-xb)^2 + (ya-yb)^2 + (za-zb)^2)
            promedio = promedio/len(cluster[i])
            
            if(promedio<mean):
                mean = promedio
                nuevocentroaux = distancia
        nuevocentro[i] = nuevocentroaux
    for i in range(len(error)):
        error[i] = np.linalg.norm(nuevocentro[i]-antiguocentro[i])
    cluster1 = [nuevocentro[0]]
    cluster2 = [nuevocentro[1]]
    cluster3 = [nuevocentro[2]]

#re calculo los puntos de cada centroide
for i in range(len(puntosprueba)):
    for j in range(len(centros)):
        aux[j] = np.linalg.norm(puntosprueba[i]-nuevocentro[j])
    #los meto en sus clusters respectivos
    minimo = min(aux)
    if(minimo==aux[0]):
        cluster1.append(puntosprueba[i])
    
    elif(minimo==aux[1]):
        cluster2.append(puntosprueba[i]) 
    
    elif (minimo==aux[2]):
        cluster3.append(puntosprueba[i])

cluster = [cluster1,cluster2,cluster3]
#se grafica
graficar(cluster,cluster1,cluster2,cluster3,nuevocentro,n)
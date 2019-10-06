import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

import random
 
STOP_THRESHOLD = 0.0004
CLUSTER_THRESHOLD = 0.1
KERNEL =0.22
def graficar(cluster,cluster1,cluster2,cluster3,nuevocentro,num):
    cluster1 = np.array(cluster1)
    cluster2 = np.array(cluster2)
    cluster3 = np.array(cluster3)
    fig = plt.figure()
    plt.scatter(cluster1[:,0], cluster1[:,1], color='red', s=20)
    plt.scatter(cluster2[:,0], cluster2[:,1], color='black',s=10)
    plt.scatter(cluster3[:,0], cluster3[:,1], color='blue',s=3)
    plt.scatter(nuevocentro[:,0], nuevocentro[:,1], marker='*', c='g', s=150)
    
    file = 'imgkmeans/imgc' + str(num) + '.png'
    fig.savefig(file, dpi=fig.dpi)
    #plt.show()     


def colors(n):
  ret = []
  for i in range(n):
    ret.append((random.uniform(0, 1), random.uniform(0, 1), random.uniform(0, 1)))
  return ret

def dist_euc(a,b):
  return np.linalg.norm(np.array(a) - np.array(b))

def F_kernel(distancia, ancho):
  val = (1/(ancho*np.sqrt(2*np.pi))) * np.exp(-0.5*((distancia / ancho))**2)
  return val

def mean_shift(X,kernel):
  puntos_S=np.array(X)
  V_cambio=[True] * X.shape[0]
  while True:
    dist_max=0
    for i in range(0, len(puntos_S)):
      if not V_cambio[i]:
        continue
      P_cambiantes = puntos_S[i].copy()
      puntos_S[i] = F_shift(puntos_S[i], X, kernel)
      dist = dist_euc(puntos_S[i], P_cambiantes)
      dist_max = max(dist_max, dist)
      V_cambio[i] = dist > STOP_THRESHOLD

    if(dist_max < STOP_THRESHOLD):
      break
  cluster_i,CENTER = P_cluster(puntos_S.tolist())
  return puntos_S, cluster_i,CENTER
def F_shift(punto, X, kernel):
  shift_x = 0.0
  shift_y = 0.0
  aux = 0.0
  for p in X:
    dist = dist_euc(punto, p)
    peso = F_kernel(dist, kernel)
    shift_x += p[0] * peso
    shift_y += p[1] * peso
    aux += peso
  shift_x = shift_x / aux
  shift_y = shift_y / aux
  return [shift_x, shift_y]

def P_cluster(puntos):
  id_cluster = []
  ID = 0
  centroide_cluster = []
  #print "centroide cluster",centroide_cluster
  print ("puntos",puntos)
  for i, punto in enumerate(puntos):
    if(len(id_cluster) == 0):
      print("id",ID)
      id_cluster.append(ID)
      centroide_cluster.append(punto)
      ID += 1
    else:
      print("id",ID)
      for center in centroide_cluster:
        dist = dist_euc(punto, center)
        if(dist < CLUSTER_THRESHOLD):
          id_cluster.append(centroide_cluster.index(center))
      if(len(id_cluster) < i+1):
        id_cluster.append(ID)
        centroide_cluster.append(punto)
        ID += 1

  #print "centroide cluster for",centroide_cluster
  return id_cluster, centroide_cluster

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
#mean_shifter = MeanShift()

Y, resultado,CENTER = mean_shift(X, KERNEL)
CENTER=np.array(CENTER)
#print(resultado)
color = colors(np.unique(resultado).size)


plt.scatter(CENTER[:,0],CENTER[:,1],marker='*',color='red',s=100)
for i in range(len(resultado)):
  plt.scatter(X[i, 0], X[i, 1],color = color[resultado[i]])# color ='red',size=20)
plt.show()
'''
#Para probar que se clasifica bien
cluster1=[]
cluster2=[]
cluster3=[]
clusterotro=[]
for i in range(len(X)):
  if(resultado[i]==0):
    cluster1.append(X[i])
  elif(resultado[i]==1):
    cluster2.append(X[i]) 
  elif (resultado[i]==2):
    cluster3.append(X[i])
  elif (resultado[i]>2):
    clusterotro.append(X[i])
cluster1 = np.array(cluster1)
cluster2 = np.array(cluster2)
cluster3 = np.array(cluster3)
clusterotro=np.array(clusterotro)
print(CENTER)

plt.scatter(cluster1[:,0], cluster1[:,1], color='red', s=20)
plt.scatter(cluster2[:,0], cluster2[:,1], color='black',s=20)
plt.scatter(cluster3[:,0], cluster3[:,1], color='blue',s=20)
plt.scatter(clusterotro[:,0],clusterotro[:,1], color='pink',s=20)
plt.scatter(CENTER[:,0], CENTER[:,1], marker='*', c='g', s=50)
plt.show() '''
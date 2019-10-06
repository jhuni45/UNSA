import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import train_test_split

from utils import matriz_confusion

def myclassvec(id, n):
	a = np.zeros(n)
	a[int(id)] = 1
	return a

def myvector(vector, n_classes):
	res = []
	for i in vector:
		res.append(myclassvec(i,n_classes))
	return np.array(res)

class backpropagation:
	def __init__(self, filename, classes, neuronas, salidas, alfa, testeo, activation = 'sigmoideal', shuffle = False):
		archivo = pd.read_csv(filename, header = None)
		self.neuronas = neuronas
		self.salidas = salidas
		self.alfa = alfa

		#for class_id, class_name in classes.items():
		#	archivo = archivo.replace(class_name, class_id)
		#n_classes = len(classes)
		
		if shuffle == True:
			train, test = train_test_split(archivo.values, testeo = (testeo/100))
		else:
			archivoTam = len(archivo)
			testeo = testeo / 100
			limit = archivoTam - int(archivoTam * testeo)
			train, test = archivo.values[:limit], archivo.values[limit:]

		train, test   = np.insert(train, 0, 1,axis=1).astype('float64'), np.insert(test, 0, 1,axis=1).astype('float64')
		
		self.entrenarCarac = train[:,:-1] 
		sd  = train[:,-1]
		self.test_Carac  = test[:,:-1]
		test_targets   = test[:,-1]

		self.aux = test_targets.astype('int64')
		self.sd	= myvector(sd, 3)
		self.test_targets	= myvector(test_targets, 3)		
		self.tamCarac  = len(self.entrenarCarac[0])

		self.capasHidden   = np.random.rand(self.tamCarac, self.neuronas)
		self.capaSalida	= np.random.rand(self.neuronas + 1, self.salidas)
		self.activation = lambda X: 1 / ( 1 + np.exp(-X))
	
	def forward(self):
		WIH = self.entrenarCarac @ self.capasHidden 
		WHO = self.activation(WIH) 
		self.WHO =  np.insert(WHO,0,1,axis=1)
		output_net = self.WHO @ self.capaSalida
		self.SO = self.activation(output_net)

	def backward(self):
		delta_1	= self.SO - self.sd
		delta_2	= self.SO * (1 - self.SO)
		delta_3	= self.WHO

		delta	= delta_1 * delta_2	
		self.delta = delta
		chain	= (delta.T @ self.WHO).T
		self.capaSalida -= self.alfa * (chain)
		cadena = ((delta * ((self.WHO * (1 - self.WHO)) @ self.capaSalida)).T @ self.entrenarCarac).T
		self.capasHidden -= self.alfa * cadena
	def get_error(self):
		return ((self.SO - self.sd)**2)/2

	def fit(self, iterations):
		for i in range(iterations):
			self.forward()
			self.backward()

	def evaluate(self, input):
		WIH = input @ self.capasHidden
		WHO = self.activation(WIH)
		WHO = np.insert(WHO, 0, 1, axis = 1)
		output_net = WHO @ self.capaSalida
		SO = self.activation(output_net)
		return SO

	def test(self):
		evaluation	= self.evaluate(self.test_Carac)
		maximums	= np.amax(evaluation,axis=1)[None].T
		indexes		= np.where(evaluation == maximums)[1]

		self.indexes	= indexes
		diff	= indexes == self.aux
		exito	= diff.sum()
		fallo	= len(diff) - exito
		print("success:\t", exito)
		print("failed: \t", fallo)

#EXISTE UNA HERRAMIENTA PARA HACER MATRIZ DE CONFUSION
	def matriz_confusion(self, save=True, names = {}, title = 'Matriz Confusion', filename='temp'):
		if hasattr(self, 'indexes'):
			plt.rcParams["figure.figsize"] = (7,7)
			matriz_confusion(self.aux, self.indexes, title = title, names = names)
			if save:
				plt.savefig(filename+'.png',dpi=300)

#MANDAMOS LOS DATOS ALFA Y NUMERO DE NEURONAS EN LA CAPA HIDDEN
classes = {
	0: 'Setosa',
	1: 'Versicolor',
	2: 'Virginica',
}

neuronas	= [4, 6, 8, 10, 12]
alfas		= [0.01, 0.04, 0.07, 0.1, 0.5]

for neuron in neuronas:
	for alfa in alfas:
		prueba = backpropagation('irisfullshuf.csv', 3, 3, 3, 0.1,30)
		#np.set_printoptions(precision=5, suppress=True)
		prueba.fit(100000)
		print('-------------------------')
		print("Test - neurons:",neuron,"alfa:", alfa )
		prueba.test()
		prueba.matriz_confusion(names=classes, title='', filename='test_'+str(neuron)+'_'+str(alfa))
		#print("Score:\t\t", np.trace(cf_matrix))
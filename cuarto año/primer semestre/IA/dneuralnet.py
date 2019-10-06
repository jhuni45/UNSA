import numpy as np

X = np.array(([2, 9], [1, 5], [3, 6]), dtype=float) #faktor penentu kualitas misal : a,b
y = np.array(([92], [86], [89]), dtype=float) #value / kualitas

X = X/np.amax(X, axis=0) #nilai maksimum array ke x
y = y/100 #maksimum bernilai 100

class Neural_Network(object):
  def __init__(self): #buat objek paramater, input - hidden - outpu
    self.inputSize = 2
    self.outputSize = 1
    self.hiddenSize = 3

    #bobot
    self.W1 = np.random.randn(self.inputSize, self.hiddenSize) #bobot untuk input ke hidden layer
    self.W2 = np.random.randn(self.hiddenSize, self.outputSize) #bobot untuk hidden layer ke keluaran

  def forward(self, X):
    #forward pass / forward propagate
    self.z = np.dot(X, self.W1)
    self.z2 = self.sigmoid(self.z) #fungsi aktivasi
    self.z3 = np.dot(self.z2, self.W2)
    o = self.sigmoid(self.z3)
    return o 

  def sigmoid(self, s):
    return 1/(1+np.exp(-s)) #fungsi aktivasi menggunakan sigmoid (anggap keluaran berniali 0-1)

  def sigmoidPrime(self, s):
    return s * (1 - s)

  def backward(self, X, y, o):
    #backward pass / backward propagate
    self.o_error = y - o 
    self.o_delta = self.o_error*self.sigmoidPrime(o) 

    self.z2_error = self.o_delta.dot(self.W2.T) #seberapa banyak nilai error yang keluar
    self.z2_delta = self.z2_error*self.sigmoidPrime(self.z2)

    self.W1 += X.T.dot(self.z2_delta)
    self.W2 += self.z2.T.dot(self.o_delta) 

  def train (self, X, y):
    o = self.forward(X)
    self.backward(X, y, o)

NN = Neural_Network()
for i in range(1000):
  print ("Input: ")
  x = input().format(x) #error nya disini, bisa melakukan input namun tidak ke prediksi
  print ("Keluaran : \n". format(y))
  print ("Prediksi Keluaran: \n", format(NN.forward(X))) 
  print ("Nilai Loss: \n", format(np.mean(np.square(y - NN.forward(X)))))
  print ("\n")
NN.train(X, y)
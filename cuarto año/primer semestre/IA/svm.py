import numpy as np
import matplotlib.pyplot as plt

from cvxopt import matrix, solvers
from scipy.spatial import ConvexHull

#Click izquierdo (1), click derecho (-1)
#tecla "a" para ejecutar el SVM

# Utilizando el problema de la dualidad de Lagrange:
# Referencias : http://members.cbio.mines-paristech.fr/~thocking/mines-course/2011-04-01-svm/svm-qp.pdf  ( pag. 2 )
#              https://cel.archives-ouvertes.fr/cel-01003007/file/Lecture2_Linear_SVM_Dual.pdf  (pag. 26 / 38
# Guia de la implementacion de lagrange resuelto como problema cuadratico:
#              [1]https://courses.csail.mit.edu/6.867/wiki/images/a/a7/Qp-cvxopt.pdf

class SVM:
    # X [[1,3],[4,5]]
    # Y [1,-1]  matriz
    x = []
    y = []

    xtemp = []
    xtemp2 = []
    ytemp = []
    ytemp2 = []

    umbral = 0.0001

    xFila = None
    xCol = None

    w = np.array([0,0])
    b = None

    alphas = []  # multiplicadores de lagrange

    #GRAFICO
    fig = None
    ax = None
    cid = None

    #Variables auxiliares para el graficos
    twoDXmin = None
    twoDXmax = None

    # ======================== CONSTRUCTOR ====================== #
    def __init__(self):
        #Generar los graficos en caso de ser 2D o 3D
        self.genGraf()

    #Generamos la estructura del ploteo y asignamos los eventos
    #onClick = Insertar puntos
    #on_key = Ejecutar SVM
    def genGraf(self):
        #------------------------ 2D --------------------#
        self.fig = plt.figure('Support Vector Machine    Tecla "a" para correr')

        # plt.axis([self.twoDXmin[1] , self.twoDXmax[1]+3, self.twoDXmin[2], self.twoDXmax[2]+3])
        plt.axis([0 , 25, 0, 25])

        #Mouseclick
        self.ax = self.fig.add_subplot(111)
        self.cid = self.fig.canvas.mpl_connect('button_press_event', self.onclick)
        self.cid = self.fig.canvas.mpl_connect('key_press_event', self.on_key)

    #Adecuamos el arreglo de puntos para un correcto uso dentro de los algoritmos y librerias.
    def transformarMatriz(self):
        # self.x = (np.array(self.x))
        # self.y = (np.array(self.y))
        self.xtemp = (np.array(self.xtemp))
        self.xtemp2 = (np.array(self.xtemp2))
        self.ytemp = (np.array(self.ytemp))
        self.ytemp2 = (np.array(self.ytemp2))
        # print("X:",self.x)
        # print("Y:",self.y)

    #Funcion encargada de dibujar los puntos a clasificar.
    def onclick(self, event):

        if(event.button == 1):
            plt.plot(event.xdata, event.ydata, 'c^',markersize=8)
            self.xtemp.append([event.xdata, event.ydata])
            self.ytemp.append(1.0)
            # self.x.append([event.xdata, event.ydata])
            # self.y.append(1.0)

        if(event.button == 3):
            plt.plot(event.xdata, event.ydata, 'mv',markersize=8)
            self.xtemp2.append([event.xdata, event.ydata])
            self.ytemp2.append(-1.0)
            # self.x.append([event.xdata,event.ydata])
            # self.y.append(-1.0)

        self.fig.canvas.draw()
        # print(self.x)
        # print(self.y)

    #Al apretar la tecla "a", se ejecutara la busqueda del mejor ajuste.
    def on_key(self,event):
        # print('you pressed', event.key, event.xdata, event.ydata)
        if(event.key == 'a'):
            print("X:",self.x)
            print("Y:",self.y)
            self.SVMachine()
            # self.entrenado = True

    #ConvexHull utilizado para eliminar los puntos no utiles.
    def Convex_Hull(self):

        xt = []
        yt = []

        print("Convex:")

        hull1 = np.arange(len(self.xtemp))
        #Hace ConvexHull cuando tiene mas de 2 elementos
        if(len(self.xtemp)>2 ):
            hull1 = ConvexHull(self.xtemp)
            print("Hull1:",hull1.vertices)
            hull1 = hull1.vertices

        #Copia los puntos en las posiciones del hull
        for i in hull1:
            xt.append([self.xtemp[i][0],self.xtemp[i][1]])
            yt.append(self.ytemp[i])

        hull2 = np.arange(len(self.xtemp2))
        #Hace ConvexHull cuando tiene mas de 2 elementos
        if(len(self.xtemp2)>2 ):
            hull2 = ConvexHull(self.xtemp2)
            print("Hull2:",hull2.vertices)
            hull2 = hull2.vertices

        #Copia los puntos en las posiciones del hull
        for i in hull2:
            xt.append([self.xtemp2[i][0],self.xtemp2[i][1]])
            yt.append(self.ytemp2[i])

        print("X append:",xt)
        print("Y append:",yt)
        self.x = np.array(xt)
        self.y = np.array(yt)
        self.xFila = self.x.shape[0]
        self.xCol = self.x.shape[1]
        print("X array:",self.x)
        print("Y array:",self.y)

    # Obtencion de los multiplicadores de Lagrange utilizando la dualidad de Lagrange.
    # Leer referencia numero[1]
    def getAlphas(self):

        K = self.y[:, None] * self.x  # Transpuesta de Y por X
        P = matrix(np.dot(K, K.T)) # Hacemos producto punto de las X para volver simetrico a K
        q = matrix(-np.ones((self.xFila, 1))) # Matriz de -1
        G = matrix(-np.eye(self.xFila)) # Matriz identidad con -1 (volver negativos los alfa)
        h = matrix(np.zeros(self.xFila)) # Matriz de 0s (cumple inecuacion)

        A = matrix(self.y.reshape(1, -1)) # Inversa de y para la sumatoria
        b = matrix(np.zeros(1)) # Matriz b con un cero para igualdad

        solvers.options['show_progress'] = False
        sol = solvers.qp(P, q, G, h, A, b)
        # print("SOl:",sol)
        alphas = np.array(sol['x'])
        print("Alphas:",alphas)
        self.alphas = alphas

    #Obtenemos el alfa mayor para dibujar correctamente las rectas
    def mayorAlpha(self,uno):
        mayor = -99
        posMayor = None
        print("X___",self.x)
        print("Y___",self.y)
        print("alphas___",self.alphas)
        for i in range(0, len(self.x)):
            if((self.alphas[i] > mayor) and (self.y[i] == uno)):
                mayor = self.alphas[i]
                posMayor = i

        print ("posMayor____: ",posMayor)
        return posMayor


    #Ya con los valores de W y B obtenidos, dibujamos las rectas del mejor ajuste.
    def dibujarLinea(self):
        if (self.xCol == 2):
            ex = np.linspace(-99,99)
            y1 = (-self.w[0] * ex - self.b) / self.w[1]

            posMayorIz = self.mayorAlpha(1.0)
            posMayorDer = self.mayorAlpha(-1.0)

            y2 = (-self.w[0]/self.w[1]) * (ex - self.x[posMayorIz][0]) + self.x[posMayorIz][1]
            y3 = (-self.w[0]/self.w[1]) * (ex - self.x[posMayorDer][0]) + self.x[posMayorDer][1]

            linea1, = plt.plot(ex,y1,'-b',linewidth=2)        #Mejor ajuste
            linea2, = plt.plot(ex,y2,'--k',linewidth=1)        # + 1 izquierda
            linea3, = plt.plot(ex,y3,'--k',linewidth=1)        #  -1  derecha

            self.fig.canvas.draw()

            # linea, = plt.plot(ex,(-1.0*self.tethas[0][0]- 1.0*self.tethas[1][0]*ex)/self.tethas[2][0])
            # self.fig.canvas.draw()

    #Obtenemos el W utilizando la formula teorica.
    def getW(self):
        # self.w = sum (np.array ([self.alphas * self.y * self.x]) )
        self.w = sum(np.array([self.alphas[i] * self.y[i] * self.x[i] for i in range (0,len(self.alphas))]))
        print("W:",self.w)


    #Obtenemos los SVMs que cumplen la condicion del umbral.
    def getSVMs(self):
        alphatemp = []
        svms = []
        for i in range(0,len(self.x)):
            if (self.alphas[i] > self.umbral):
                svms.append(self.x[i])
                alphatemp.append(self.alphas[i])

        self.alphas = np.array(alphatemp)
        self.x = np.array(svms)
        print("Nuevas alphas:",self.alphas)
        return svms

    #Obtenemos la clasificacion (Y) de los SVMs que cumplen con el umbral.
    def getSVMsY(self):
        svmsy = []
        for i in range(0,len(self.y)):
            if (self.alphas[i] > self.umbral):
                svmsy.append(self.y[i])
        self.y = np.array(svmsy)
        return svmsy

    #Obtenemos el valor de B mediante teoria (ecuacion de primer grado)
    def getB(self):
        self.b = self.getSVMsY() - np.dot(self.getSVMs(), self.w)
        print("B original:",self.b)
        self.b = np.average(self.b)
        print("B:",self.b)

    #Funcion procedimental encargada de ejecutar paso a paso el algortimo del SVM.
    def SVMachine(self):
        self.transformarMatriz()
        self.Convex_Hull()
        self.getAlphas()
        self.getW()
        self.getB()
        self.dibujarLinea()

obj = SVM()
plt.show()
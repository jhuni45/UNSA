from mpl_toolkits.mplot3d import Axes3D
from sklearn import linear_model
import matplotlib.pyplot as plt
import numpy as np

def function(A,theta):

	return A.dot(theta)



A=[]
B=[]
for i in range(0,50):
	A.append([i,i])
	B.append(i)

A=np.array(A)

reg = linear_model.LinearRegression()
reg.fit(A,B)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(A[:,0],A[:,1],B)

ax.plot_wireframe(A[:,0],A[:,1],function(A,reg.coef_))
#ax = plt.gca()
ax.hold(True)

plt.show()


#print reg.coef_
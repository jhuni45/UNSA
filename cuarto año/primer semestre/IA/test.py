from random import randint
import pandas as pd
from math import *
from decimal import *
import matplotlib.pyplot as plt
import numpy as np

from sklearn import preprocessing, svm
from sklearn.linear_model  import LinearRegression
from sklearn import datasets, linear_model 
from sklearn.model_selection import train_test_split

from sklearn.metrics import mean_squared_error, r2_score

df=pd.read_csv("forestfires.csv")

X=np.array(df[['X','Y']])
Y=np.array(df[['area']])

X_train, X_test, y_train, y_test=train_test_split(X,Y,test_size=0.3, random_state=10)

reg= linear_model.LinearRegression()
reg.fit(X_train,y_train)
pred=reg.predict(X_test)

plt.scatter(X_test,y_train,color='black')
plt.plot(X_test,pred,color="blue",linewidth=3)
plt.xticks(())
plt.yticks(())

plt.show()
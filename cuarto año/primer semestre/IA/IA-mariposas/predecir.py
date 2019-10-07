#from keras.models import load_model
import keras
from keras.preprocessing.image import load_img, img_to_array
from keras.utils import CustomObjectScope
from keras.initializers import glorot_uniform
import numpy as np
import tensorflow as tf
import os


model = 'modelButter/modelButter.h5'
model_weight = 'modelButter/weights.h5'
butter = tf.keras.models.load_model(model)
butter.load_weights(model_weight)

def predict(file):
	x = load_img(file, target_size=(150, 150))
	x = img_to_array(x)
	x = np.expand_dims(x, axis=0)
	array = butter.predict(x)
	result = array[0]
	answer = np.argmax(result)
	print("================================\n|\timage\t: "+file+"\t|\n|\tespecie(prediccion):\t|")
	if answer == 0:
		print("|\tDanaus plexippus\t|")
	elif answer == 1:
		print("|\tHeliconius charitonius\t|")
	elif answer == 2:
		print("|\tHeliconius erato\t|")
	elif answer== 3:
		print("|\tJunonia coenia\t|")
	elif answer== 4:
		print("|\tLycaena phlaeas\t|")
	elif answer== 5:
		print("|\tNymphalis antiopa\t|")
	elif answer== 6:
		print("|\tPapilio cresphontes\t|")	
	elif answer== 7:
		print("|\tPieris rapae\t|")
	elif answer== 8:
		print("|\tVanessa atalanta\t|")
	elif answer== 9:
		print("|\tVanessa cardui\t|")
	print("================================\n")
	return answer


for i in range (0,10):
	image='00'+str(i)+'.png'
	predict(image)


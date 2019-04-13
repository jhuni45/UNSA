from decimal import *
def fun(ta,fm,am):
	return (Decimal)(ta*((1-fm)+(fm/am)))

for i in range (1, 20):
	print ("valor ",i,fun(20,0.9,i))


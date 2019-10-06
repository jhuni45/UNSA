import math
import pprint
def matrixH0(k):
    H0 = []
    for m in range(k):
        # create a new row 
        row = []               
        for n in range(k):
            x=input("valor")
            row.append(x)
            
        H0.append(row)
    return H0
pprint.pprint(matrixH0(4))
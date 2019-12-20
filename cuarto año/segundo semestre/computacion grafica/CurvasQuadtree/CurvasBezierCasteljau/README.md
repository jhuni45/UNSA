# CREACIÓN DE CURVAS
### Creación de curvas por algoritmos de Bezier y Casteljau
  - Se insertan puntos y se va generando curvas
  - Se puede mover los puntos para ver como se altera
### 1. Funciones importantes
 - Esta determinado por la siguiente porción de código (Bezier)
 ```cpp
void bern(){
	double t;
	int i;
	for(t=0;t<=1.0;t=t+0.01){
		currentX=0;
		currentY=0;
		for(i=0;i<=NO_POINTS;i++){
			double Ci = (double)fact(NO_POINTS)/(double)(fact(NO_POINTS-i)*fact(i));
			double Cj = (double)(pow((1-t),NO_POINTS-i))*pow(t,i); 	
			currentX += Ci * Cj * x[i];
			currentY += Ci * Cj * y[i];
		}
		drawLine(oldX,500-oldY,currentX,500-currentY);
		oldX=currentX;
		oldY=currentY;
	}
}
```
 - Esta determinado por la siguiente porción de código (Casteljau)
  ```cpp
void deCas(){
	double t;
	for(t=0;t<=1.0;t=t+0.001){
		currentX=(1-t)*((1-t)*((1-t)*x[0]+t*x[1])+t*((1-t)*x[1]+t*x[2]))+t*((1-t)*((1-t)*x[1]+t*x[2])+t*((1-t)*x[2]+t*x[3]));
		currentY=(1-t)*((1-t)*((1-t)*y[0]+t*y[1])+t*((1-t)*y[1]+t*y[2]))+t*((1-t)*((1-t)*y[1]+t*y[2])+t*((1-t)*y[2]+t*y[3]));
		drawLine(oldX,720-oldY,currentX,720-currentY);
		oldX=currentX;
		oldY=currentY;
	}
}
```


### Pruebas
#### Prueba (inserción y mover puntos)

![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/CurvasQuadtree/imagesGifts/beziermoviendo.gif)

#### Pruebas con distintos puntos

![alt text](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/CurvasQuadtree/imagesGifts/pruebasbezier.png)

### Referencias
* [Manejo de ratón] https://www.opengl.org/resources/libraries/glut/spec3/node54.html

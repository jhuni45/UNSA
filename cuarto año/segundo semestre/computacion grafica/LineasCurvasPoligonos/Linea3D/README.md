LINEA 3D

Referencias
* https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html#zz-2.

Para dibujar una linea en 3D se ha implementado el siguiente algoritmo

```cpp
for (x=x0; x<=x1;x+=0.1){
   y=(y0+m*(x-x0));
   glVertex3f(x,y,x);
}
```
El cual crea puntos proyectados en el plano XY
* Test1

![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/LineasCurvasPoligonos/Linea3D/test1.gif)

* Test 2

![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/LineasCurvasPoligonos/Linea3D/test2.gif)

SIN EMBARGO: Dibujar una linea en 3D implica la creación de un plano
```cpp
for (z=z0; z<=z1; z+=0.1){
   for (x=x0; x<=x1;x+=0.1){
      y=(y0+m*(x-x0));
      glVertex3f(x,y,z);
   }
}
```

* Test Linea 3D

![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/LineasCurvasPoligonos/Linea3D/test3.gif)

# QUADTREE
## Preliminares
- Realizar el algoritmo QuadTree para la segmentación de imágenes
  - Pruebas con una imagen de caricatura
  - Pruebas con una imagen de paisaje
### Compilación y ejecución de código

```terminal
$ g++ BMPdisplay.cpp BMPload.cpp quadtree.cpp -o test -lGL -lGLU  -lglut -lm
$ ./test <image> <porcentaje de segmentación (epsilon)>
```
Ejemplo
```terminal
$ ./test bugs.bmp 10
```

## Pruebas
### Imagen de caricatura
#### Archivo de entrada
![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/CurvasQuadtree/QuadTree/bugs2.bmp)
#### Salida
![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/CurvasQuadtree/imagesGifts/bugsgift.gif)

### Imagen de paisaje
![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/CurvasQuadtree/QuadTree/paisaje.bmp)
#### Salida
![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/CurvasQuadtree/imagesGifts/paisaje.gif)
## Referencias 
[Manejo teclado y ratón] https://www.opengl.org/resources/libraries/glut/spec3/node54.html

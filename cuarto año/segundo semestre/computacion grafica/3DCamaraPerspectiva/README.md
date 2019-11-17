# VISUALIZACIÓN (PERSPECTIVA Y ORTOGONAL)
## EJERCICIOS:

### 1. Mover la camara con el mouse
  - Esta determinado por la siguiente porción de código
```cpp
case GLUT_KEY_F3:
    cout<<"Mover camara con mouse"<<endl;
    glutPassiveMotionFunc(MouseMotion);
    LOCAL_MyCamera->camMovimiento = CAM_PASEAR;
    LOCAL_MyCamera->camAtY = 0;
    LOCAL_MyCamera->camViewY = 0;
    SetDependentParametersCamera( LOCAL_MyCamera );
    break;
}
```
#### 1.1 Test1

![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/3DCamaraPerspectiva/images/moverCamara.gif)

#### 1.2 Test 2

![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/3DCamaraPerspectiva/images/moverCamara2.gif)

### 2. Mover el objeto en la proyección
  - Esta determinado por la siguiente porción de código
```cpp
case GLUT_KEY_F2:
    cout<<"Mover objeto en proyeccion"<<endl;
    glutPassiveMotionFunc(Examinar);
    LOCAL_MyCamera->camMovimiento = CAM_EXAMINAR;
    break;
```
#### 2.1 Test
![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/3DCamaraPerspectiva/images/moverObjeto.gif)

### 3. Cambiar de perspectiva de la cámara (con el teclado)
  - Esta determinado por la siguiente porción de código
```cpp
case GLUT_KEY_F4:
    cout<<"Cambio de vista"<<endl;
		if(LOCAL_MyCamera->camProjection == CAM_CONIC){
		LOCAL_MyCamera->x1=-3;
		LOCAL_MyCamera->x2=3;
		LOCAL_MyCamera->y1=-3;
		LOCAL_MyCamera->y2=3;
		LOCAL_MyCamera->z1=-5;
		LOCAL_MyCamera->z2=5;
		LOCAL_MyCamera->camProjection = CAM_PARALLEL;
		cout<<"Proyección Ortogonal"<<endl;
		}else{
			cout<<"Proyección Perspectiva"<<endl;	
			LOCAL_MyCamera->camProjection = CAM_CONIC;
		}
		break;  
```
#### 3.1 Test 
![](https://github.com/jhuni45/UNSA/blob/master/cuarto%20a%C3%B1o/segundo%20semestre/computacion%20grafica/3DCamaraPerspectiva/images/cambiarPerspectiva.gif)


### Referencias
* [Material enviado por profesor] ![]()
* [Manejo de teclado y ratón] https://www.opengl.org/resources/libraries/glut/spec3/node54.html
* [Modelo solido de ejemplo] https://www.opengl.org/resources/libraries/glut/spec3/node85.html#SECTION000125000000000000000
  ```cpp
  glutWireDodecahedron();
  //glutWireIcosahedron();
  //glutWireTorus(0.5,1,20,20);
  ```

#include <GL/glut.h>
#include <iostream>

using namespace std;

/*
void write_pixel3d(int x, int y, int z){
	glBegin(GL_LINES);
  		glVertex3f(0.0f, 0.0f, 0.0f);
  		glVertex3f(50.0f, 50.0f, 50.0f);
	glEnd();
}
*/

//********FUNCIONES PARA TRAZADO DE CIRCUNFERENCIA*******//
//CONFIGURACIONES DE VENTANA 2D
void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200.0,200.0,-200.0,200.0);
}

//FUNCION PARA PINTAR UN PIXEL
void write_pixel(int x, int y){
	//glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();

}

//ALGORITMO BASICO INCREMENTAL PARA DIBUJO DE LINEAS
void basic_incremental_alg (int x1, int y1, int x2, int y2){
    double x=0,y=0,valor;
	float m;
	m=(y2-y1)/(x2-x1);
	for(x=x1;x<=x2;x++){
		y=( y1 + m * ( x - x1) );
		write_pixel(x,y);
	}
}

//ALGORITMO PUNTO MEDIO PARA DIBUJO DE LINEAS
void mid_point_alg(int x1,int y1, int x2, int y2){
	int dx,dy,incE,incNE,d,x,y;
	dx=x2-x1;
	dy=y2-y1;
	d=2*dy-dx; 
	incE=2*dy; 
	incNE=2*(dy-dx);
	x=x1;
	y=y1;
	write_pixel(x,y);
	while (x < x2){
		if(d <=0){
			d=d+incE;
			x=x+1;
		}else{
		   d=d+incNE;
		   x=x+1;
		   y=y+1;
		}
		write_pixel(x,y);
	}
}

//********FUNCIONES PARA TRAZADO DE CIRCUNFERENCIA*******//
//FUNCION PARA PINTAR PIXELES EN LOS CUADRANTES (45 GRADOS CADA CUADRANTE)
void circle_point(int x, int y){
	write_pixel(x,y);
	write_pixel(x,-y);
	write_pixel(-x,y);
	write_pixel(-x,-y);

	write_pixel(y,x);
	write_pixel(y,-x);
	write_pixel(-y,x);
	write_pixel(-y,-x);
}

//FUNCION PARA DIBUJAR UN CIRCULO (PRIMERA ORDEN)
void circle(int r){
	float x, y, p;
    float d;
    //p = 0.01;
    x = 0.0;
    y = r;// /p;
    d = 5.0/4.0 - r;
    //d = 1.0 - r;    //para hacer por enteros
	circle_point(x,y);
    while (y > x){
        if (d < 0.0){// Para E
            d = d + 2 * x + 3;
        }
        else{// Para SE
            d = d + 2 * (x - y) + 5;
            y -= 1.0;
        }
        x += 1.0;   
        circle_point(x,y);
    }
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(3);
    ///PARA LINEAS
    basic_incremental_alg(45,45,145,145);
    glColor3f(0.18,0.2,0.65);
    mid_point_alg(20,20,146,94);
    ///PARA CIRCUNFERENCIA
    glColor3f(0.18,0.67,0.65);
    circle(50);
    glFlush();
}

int main (int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(50,100);
    glutCreateWindow("Creando lineas y circunferencias");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
	return 0;
}
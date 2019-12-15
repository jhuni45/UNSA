#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define NO_POINTS 2

int x[100], y[100];
int q=0, k=0;
double oldX, oldY, currentX, currentY;

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);	
	glFlush();
}

int fact(int x){
	if(x == 0)
		return 1;
	int facto=1;
	for(; x > 0; x = x-1){
		facto=facto*(x);
	}
	return facto;
}

void init(void){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	gluOrtho2D(0,500,0,500);
}

void drawLine(float l,float m, float j, float i){
	glBegin(GL_LINES);
	glVertex2f(l,m);
	glVertex2f(j,i);
	glEnd();
	glFlush();
}

void drawDot(int l, int m){
	glBegin(GL_POINTS);
	glVertex2i(l,m);
	glEnd();
	glFlush();
}

void bern(){
	double t;
	int i;
	for(t=0; t<=1.0; t=t+0.0001){
		currentX=0;
		currentY=0;
		for(i=0; i<=NO_POINTS; i++){			
			currentX=currentX+double((double)fact(NO_POINTS)/(double)(fact(NO_POINTS-i)*fact(i)))*(pow((1-t),NO_POINTS-i))*pow(t,i)*x[i];
			currentY=currentY+double((double)fact(NO_POINTS)/(double)(fact(NO_POINTS-i)*fact(i)))*(pow((1-t),NO_POINTS-i))*pow(t,i)*y[i];
		}
		drawLine(oldX,500-oldY,currentX,500-currentY);
		oldX=currentX;
		oldY=currentY;
	}
}

void placeDots(int button, int state, int i, int j){
	if(state==GLUT_DOWN){
		if(button==GLUT_LEFT_BUTTON){
			if(q <= NO_POINTS){
				x[q]=(int)i;
				y[k]=(int)j;
				drawDot(x[q],500-y[k]);
				if(q==0)
					oldX=x[q];
				if(q==0)
					oldY=y[q];
				q++;
				k++;
			}
			else if(q == NO_POINTS+1){
				bern();
				q++;
			}
		}	
	}
}	

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Curva por Bezier");
	glutMouseFunc(placeDots);
 	glutDisplayFunc(display);
 	init();
	glutMainLoop();
	return 0;
}
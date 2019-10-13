#include <GL/glut.h>

float angleline= 0.0;

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST); 
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);   
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}

void linea3D(int x0, int y0, int z0, int x1, int y1, int z1){
   glBegin(GL_POINTS);
   float m, x, y, z, dx, dy;
   dx=x1-x0;
   dy=y1,y0;
   m=dy/dx;
   //PARA GRAFICAR LA LINEA , SOLO SON PUNTOS MAS NO UN  PLANO (QUE DEBERIA SER EN 3D)
//   for (z=z0; z<=z1; z+=0.1){
      for (x=x0; x<=x1;x+=0.1){
         y=(y0+m*(x-x0));
         glVertex3f(x,y,x);
      }
  // }
   glEnd();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   glMatrixMode(GL_MODELVIEW);
 
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -10.0f);
   glPointSize(5);
    
   glColor3f(0.18,0.67,0.65);
   glRotatef(angleline, 1.0f, 1.0f, 1.0f);
   linea3D(1,0,0,4,6,7);
   
   //PARA GRAFICAR LAS COORDENADAS
   glColor3f(1.0f, 0.0f, 0.0f);
   glBegin(GL_LINES);
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(5.0f,0.0f,0.0f);
   glEnd();

   glColor3f(0.0f, 1.0f, 0.0f);
   glBegin(GL_LINES);
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(0.0f,5.0f,0.0f);
   glEnd();

   glColor3f(0.0f, 0.0f, 1.0f);
   glBegin(GL_LINES);
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(0.0f,0.0f,5.0f);
   glEnd();
  
   glFlush();
   angleline -= 0.15f;
   glutSwapBuffers(); 
}

void timer(int value) {
   glutPostRedisplay();
   glutTimerFunc(15, timer, 0);
}

void reshape(GLsizei width, GLsizei height){
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)  height;

   glViewport(0, 0, width, height);
 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);            
   glutInitDisplayMode(GLUT_DOUBLE); 
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("linea en 3D"); 
   glutDisplayFunc(display);  
   glutReshapeFunc(reshape);
   initGL();
   glutTimerFunc(0, timer, 0);
   glutMainLoop();
   return 0;
}
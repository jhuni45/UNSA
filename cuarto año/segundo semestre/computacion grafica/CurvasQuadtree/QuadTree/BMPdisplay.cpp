#include "quadtree.h"

using namespace std;
#include <GL/glut.h>

const int EscapeKey = 27;
typedef unsigned char byte;
int ScreenWidth  = 1024;
int ScreenHeight =  768;
byte* BMPimage;
byte* image; 
int nrows, ncols;
quadtree q;
bool space = false;
byte fudge;

void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void mouse(int button, int state, int x, int y);

void initOpenGL( const char *filename, int nrows, int ncols );
bool LoadBmpFile( const char* filename, int &nrows, int &ncols, byte* &image );
void displayColor( int x, int y, int w, int h, byte *image );
void displayMonochrome( int x, int y, int w, int h, byte *image );
void drawText(char *string, int x, int y);
void drawLine(float x1, float y1, float x2, float y2);

int main( int argc, char *argv[] ){
    if ( argc < 3 ){
        cerr << "US: quadtree imagen.bmo rango\n";
        return -1;
    }
    if ( !LoadBmpFile( argv[1], nrows, ncols, BMPimage ) ){
        cerr << "Error: no se puede cargar " << argv[1] << endl;
        return -1;
    }
    cerr << "reading " << argv[1] << ": " << nrows << " x " << ncols << endl;
    image = new byte [nrows * ncols ];
    byte* BMPptr = BMPimage, *imageptr = image;
    cerr << (nrows*ncols) << " 8-bit pixels in image (" <<(nrows*ncols)<< " bytes).\n";
    for ( int row = 1; row <= nrows; row++ )
        for ( int col = 0; col < ncols; col++ ){
	  *imageptr++ = 0.30 * BMPptr[0] + 0.59 * BMPptr[1] + 0.11 * BMPptr[2] + 0.5;
	  BMPptr += 3;
    }
    fudge = stoi(argv[2]);
    q.tree(image, nrows, ncols, fudge);

    glutInit( &argc, argv );
    initOpenGL( argv[1], nrows, ncols );
    glutMainLoop();

    return 0;

}

void initOpenGL( const char *filename, int nrows, int ncols ){
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE );

    ScreenWidth = 2 * ncols;
    ScreenHeight = nrows+40;
    glutInitWindowSize( ScreenWidth, ScreenHeight);
    glutInitWindowPosition( 100, 50 );
    glutCreateWindow( filename );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glutDisplayFunc( display );				
    glutReshapeFunc( reshape );				
    glutKeyboardFunc( keyboard );			
    glutMouseFunc( mouse );
}

void mouse(int button, int state, int x, int y) {
  if(button == 3 && state == 1) {
    if(fudge < 255) {
      fudge++;
      q.tree(image, nrows, ncols, fudge);
      glutPostRedisplay();
    }
  } else if(button == 4 && state == 1) {
    if(fudge > 0) {
      fudge--;
      q.tree(image, nrows, ncols, fudge);
      glutPostRedisplay();
    }
  } else if(button == 1 && state == 1) {
    space = !space;
    glutPostRedisplay();
  }  
}

void display( void ){
    glClear( GL_COLOR_BUFFER_BIT );
    displayMonochrome( 0, 0, ncols, nrows, image );
    if(space == false) 
      displayMonochrome( ncols, 0, ncols, nrows, q.getLinesImg() );
    else {
      displayMonochrome( ncols, 0, ncols, nrows, q.getNewImg() );
      drawLine(ncols, 0, ncols, nrows);
    }
    drawText((char*)"Imagen original", (ncols/3)+20, (nrows+8));
    drawText((char*)"Imagen QuadTreeQuadtree Image (spacebar toggles quads)", ((ncols/3) + ncols)-20, (nrows + 20));
    drawText((char*)"Rueda de mouse o  teclas +/- pra cambiar epsilon", ((ncols/3) + ncols)-10, (nrows + 5));
    glFlush();
}

void reshape( int w, int h ){
    ScreenWidth = w;
    ScreenHeight = h;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );
}

void keyboard( unsigned char key, int x, int y ){
    switch ( key ){
      case EscapeKey:
	exit( 0 );
	break;
      case 32: 
	space = !space;
	glutPostRedisplay();
	break;
      case 43:
	if(fudge < 255) {
	  fudge++;
	  q.tree(image, nrows, ncols, fudge);
	  glutPostRedisplay();
	}
	break;
      case 45:
	if(fudge > 0) {
	  fudge--;
	  q.tree(image, nrows, ncols, fudge);
	  glutPostRedisplay();
	}
	break;
      default:
	glutPostRedisplay();
	break;
    }
}

void displayColor( int x, int y, int w, int h, byte* image ){
    glRasterPos2i( x, y );
    glDrawPixels( w, h, GL_RGB, GL_UNSIGNED_BYTE, BMPimage );
}

void displayMonochrome( int x, int y, int w, int h, byte* image ){
    glRasterPos2i( x, y );
    glDrawPixels( w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE, image );
}

void drawText( char *str, int x, int y ) {
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2i( x, y );
  while ( *str )
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *str++ );
}

void drawLine(float x1, float y1, float x2, float y2) {
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
  glFlush();
}

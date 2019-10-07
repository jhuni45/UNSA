#ifndef LINEA_H
#define LINEA_H

class Linea{
public:
    void basic_incremental_alg(int x0,int y0, int xf, int yf);
    void mid_point_alg(int x0,int y0, int xf, int yf);
    void linea();
    void dibujar(int x0,int y0, int xf, int yf);
    void dibujar_linea(int x0,int y0, int xf, int yf);
    void write_pixel(int x,int y);
    Linea(){;}
};

void Linea::write_pixel(int x,int y){
    glColor3f(0.18,0.67,0.65);
    glPointSize(5);
	glBegin(GL_POINTS);
	   glVertex2i(x,y);
	glEnd();
}

void Linea:: basic_incremental_alg(int x1, int y1, int x2, int y2){
	double x=0,y=0,valor;
    float m;
    m=(y2-y1)/(x2-x1);
    for(x=x1;x<=x2;x++){
        y=( y1 + m * ( x - x1) );
        write_pixel(x,y);
    }
}

void Linea:: mid_point_alg(int x1,int y1, int x2, int y2){
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

void Linea::dibujar_linea(int x1,int y1, int x2, int y2){
	glBegin(GL_LINES);
    glColor3f(0.18,0.2,0.65);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glEnd();
}

void Linea::linea(){
	glClear(GL_COLOR_BUFFER_BIT);
	int x0=-5,y0=-5,xf=150,yf=150;
	dibujar_linea(x0,y0,xf,yf);
	basic_incremental_alg( x0, y0,  xf,  yf);
	//mid_point_alg( x0, y0,  xf,  yf);
	glFlush();
}

void Linea::dibujar(int x1,int y1, int x2, int y2){
	glClear(GL_COLOR_BUFFER_BIT);
	dibujar_linea(x1,y1,x2,y2);
	//basic_incremental_alg( x0, y0,  xf,  yf);
	mid_point_alg(x1,y1,x2,y2);
	glFlush();
}
#endif

#include <cstdio>
#include <GL/glut.h>

using namespace std;
typedef unsigned char byte;
byte* BMPimage;
byte* image; 
int nrows, ncols;
int ScreenWidth  = 1024;
int ScreenHeight =  768;


bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
static short readShort( FILE* infile );
static int readLong( FILE* infile );
static void skipChars( FILE* infile, int numChars );
static inline int GetNumBytesPerRow( int NumCols );


bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr ){
    FILE* infile = fopen( filename, "rb" );     // open binary BMP file for reading
    if ( !infile ){
        fprintf( stderr, "Unable to open file: %s\n", filename );
        return false;
    }

    bool fileFormatOK = false;
    int bChar = fgetc( infile );
    int mChar = fgetc( infile );
    if ( bChar == 'B' && mChar == 'M' ){
        skipChars( infile, 4 + 2 + 2 + 4 + 4 );
        NumCols = readLong( infile );
        NumRows = readLong( infile );
        skipChars( infile, 2 ); 
        int bitsPerPixel = readShort( infile );
        skipChars( infile, 4 + 4 + 4 + 4 + 4 + 4 );
        if ( NumCols > 0 && NumCols <= 100000 && NumRows > 0 && NumRows <= 100000
                && bitsPerPixel == 24 && !feof( infile )){
            fileFormatOK = true;
        }
    }

    if ( !fileFormatOK ){
        fclose ( infile );
        fprintf( stderr, "Archivo invalido: %s.\n", filename );
        return false;
    }
    ImagePtr = new unsigned char[ NumRows * GetNumBytesPerRow( NumCols ) ];
    if ( !ImagePtr ){
        fclose ( infile );
        fprintf( stderr, "Muy grande %i x %i bitmap: %s.\n",
                 NumRows, NumCols, filename );
        return false;
    }
    unsigned char* cPtr = ImagePtr;
    for ( int i = 0; i < NumRows; i++ ){
        int j;
        for ( j = 0; j < NumCols; j++ ){
            *( cPtr + 2 ) = fgetc( infile );
            *( cPtr + 1 ) = fgetc( infile );
            *cPtr = fgetc( infile );
            cPtr += 3;
        }
        int k = 3 * NumCols;
        for ( ; k < GetNumBytesPerRow( NumCols ); k++ ){
            fgetc( infile );
            *( cPtr++ ) = 0;
        }
    }
    if ( feof( infile ) ){
        fclose ( infile );
        fprintf( stderr, "Error: %s.\n", filename );
        return false;
    }
    fclose( infile );
    return true;
}

static inline int GetNumBytesPerRow( int NumCols ){
    return ( ( 3 * NumCols + 3 ) >> 2 ) << 2;
}

short readShort( FILE* infile ){
    unsigned char lowByte, hiByte;
    lowByte = fgetc( infile );
    hiByte = fgetc( infile );

    short ret = hiByte;
    ret <<= 8;
    ret |= lowByte;
    return ret;
}

int readLong( FILE* infile ){
    unsigned char byte0, byte1, byte2, byte3;
    byte0 = fgetc( infile );
    byte1 = fgetc( infile );
    byte2 = fgetc( infile );
    byte3 = fgetc( infile );

    int ret = byte3;
    ret <<= 8;
    ret |= byte2;
    ret <<= 8;
    ret |= byte1;
    ret <<= 8;
    ret |= byte0;
    return ret;
}

void skipChars( FILE* infile, int numChars ){
    for ( int i = 0; i < numChars; i++ ){
        fgetc( infile );
    }
}
void reshape( int w, int h ){
    ScreenWidth = w;
    ScreenHeight = h;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );
}
void initOpenGL( const char *filename, int nrows, int ncols ){
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE );
    ScreenWidth = 2 * ncols;
    ScreenHeight = nrows+40;
    glutInitWindowSize( ScreenWidth, ScreenHeight);
    glutInitWindowPosition( 100, 50 );
    glutCreateWindow( filename );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
     
}


int main( int argc, char *argv[] ){
    glutInit( &argc, argv );
    initOpenGL( argv[1], nrows, ncols );
    glutMainLoop();
    return 0;
}
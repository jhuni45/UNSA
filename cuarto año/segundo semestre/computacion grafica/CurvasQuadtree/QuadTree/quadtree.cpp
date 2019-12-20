#include "quadtree.h"

using namespace std;
quadtree::quadtree() {

}

void quadtree::tree(byte *inImg, int nrows, int ncols, int f) {
  fudge = f;
  count = 0;
  leafcount = 0;
  root = new node;
  root->minX = 0;
  root->minY = 0;
  root->maxX = ncols;
  root->maxY = nrows;

  image = new byte*[ncols];     
  newImg = new byte[ncols*nrows]; 
  linesImg = new byte[ncols*nrows];    
  temp = new byte*[ncols];        
  for( int i = 0 ; i < ncols ; i++ ) {
    image[i] = new byte[nrows];
    temp[i] = new byte[ncols];
  }
  if(image == nullptr || temp == nullptr || newImg == nullptr || linesImg == nullptr) {
    cout << "Unable to dynamically allocate memory.\n";
    exit(2);
  }
  for(int i = 0; i < (nrows*ncols);i++)
    image[(i%ncols)][(nrows-(i/ncols))-1] = inImg[i];
  traverse(root);
  decompress(root);
  convertQuad();
  whiteLines(root);
  convertLines();

  cerr << count << " nodes and " << leafcount << " leaves in quadtree (" << leafcount*2 << " bytes).\n";
  cerr << "The quadtree size is about ";
  cerr << ceil( ( (float)(leafcount*2)/(float)(nrows*ncols)) * 100 );
  cerr << "% of the uncompressed image size.\n";
}
quadtree::~quadtree() {
  deleteTree(root);
}

void quadtree::deleteTree(node *&tree) {
  if (tree->NW != nullptr) {
    deleteTree(tree->NW);
  }
  if (tree->SW != nullptr) {
    deleteTree(tree->SW);
  }
  if (tree->NE != nullptr) {
    deleteTree(tree->NE);
  }
  if (tree->SE != nullptr) {
    deleteTree(tree->SE);
  }
  delete tree;
}

void quadtree::divide(node *&tree) {
  count += 4;
  tree->NW = new node;
  tree->NE = new node;
  tree->SW = new node;
  tree->SE = new node;
  // NW node
  tree->NW->minX = tree->minX;
  tree->NW->maxX = ((tree->maxX+tree->minX)/2);
  tree->NW->minY = tree->minY;
  tree->NW->maxY = ((tree->maxY+tree->minY)/2);
  // NE node
  tree->NE->minX = ((tree->maxX+tree->minX)/2);
  tree->NE->maxX = tree->maxX;
  tree->NE->minY = tree->minY;
  tree->NE->maxY = ((tree->maxY+tree->minY)/2);
  // SW node
  tree->SW->minX = tree->minX;
  tree->SW->maxX = ((tree->maxX+tree->minX)/2);
  tree->SW->minY = ((tree->maxY+tree->minY)/2);
  tree->SW->maxY = tree->maxY;
  // SE node
  tree->SE->minX = ((tree->maxX+tree->minX)/2);
  tree->SE->maxX = tree->maxX;
  tree->SE->minY = ((tree->maxY+tree->minY)/2);
  tree->SE->maxY = tree->maxY;
}

byte quadtree::getMean(node *&quadrant) {
  double avg = 0;
  for(int i = quadrant->minY; i < quadrant->maxY; i++ ) {
    for(int j = quadrant->minX; j < quadrant->maxX; j++) {
      avg += image[j][i];
    }
  }
  avg = avg/(double)((quadrant->maxX - quadrant->minX) * (quadrant->maxY - quadrant->minY));
  return ceil(avg);
}

void quadtree::traverse(node *&quadrant) {
  int avg = getMean(quadrant);
  for(int y = quadrant->minY; y < quadrant->maxY;y++) {
    for(int x = quadrant->minX; x < quadrant->maxX;x++) {
      if(abs(image[x][y] - avg) > fudge) {
	divide(quadrant);
	traverse(quadrant->NW);
	traverse(quadrant->NE);
	traverse(quadrant->SE);
	traverse(quadrant->SW);
	return;
      }
    }
  }
  quadrant->leaf = true;
  leafcount++;
  quadrant->color = avg;
}
int quadtree::getCount() {
  return count;
}

int quadtree::getLeafs() {
  return leafcount;
}

void quadtree::decompress(node *tree) {
  if(tree->leaf == true) {
    for(int y = tree->minY; y < tree->maxY; y++ ) {
      for(int x = tree->minX; x< tree->maxX; x++ ) {
	temp[x][y] = tree->color;
      }
    }
  } else {
    decompress(tree->NW);
    decompress(tree->NE);
    decompress(tree->SE);
    decompress(tree->SW);
  }
}

void quadtree::whiteLines(node *tree) {
  if(tree->leaf == true) {
    for(int x = tree->minX; x < tree->maxX; x++ ) {
      image[x][tree->minY] = 255; 
      if(tree->maxY != root->maxY)
	image[x][tree->maxY] = 255;
      else
	image[x][tree->maxY-1] = 255;
    }
    for(int y = tree->minY; y < tree->maxY; y++ ) {
      image[tree->minX][y] = 255; 
      if(tree->maxX != root->maxX)
	image[tree->maxX][y] = 255;
      else
	image[tree->maxX-1][y] = 255;
    }
  } else {
    whiteLines(tree->NW);
    whiteLines(tree->NE);
    whiteLines(tree->SE);
    whiteLines(tree->SW);
  }
}

byte* quadtree::getNewImg() {
  return newImg;
}

byte* quadtree::getLinesImg() {
  return linesImg;
}

void quadtree::convertQuad() {
  for(int i = 0; i < (root->maxX * root->maxY);i++) {
    newImg[i] = temp[(i%root->maxX)][(root->maxY-(i/root->maxX))-1];
  }
}
void quadtree::convertLines() {
  for(int i = 0; i < (root->maxX * root->maxY);i++) {
    linesImg[i] = image[(i%root->maxX)][(root->maxY-(i/root->maxX))-1];
  }
}

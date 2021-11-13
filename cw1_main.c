// gcc -Wall -Wextra -Wconversion cw1_main.c -o comp_cw1
// ./comp_cw1 gridSize

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void averageEntireGrid(int, float[]);
void outputGrid(int, float[]);
void outputNonSquareGrid(int, int, float[]);
void getThreeRows(int, int, float[], float[]);
void avgNonSquareGrid(int, float[], float[]);
void avgSomeThreeRows(int, int, float[], float[]);
void avgSomeThreeRowsInPlace(int, int, float[]);
void outputFinalGrid(int, float[]);


int main(int argc, char *argv[]){
  int gridSize = 4;
  if (argc == 2){
    gridSize = (int)strtol(argv[1], NULL,10);
  }

/*  // Create grid of size gridSize
  float grid[gridSize][gridSize];
  // Fill top row with 1.0
  for ( int i = 0; i < gridSize; ++i) {
    grid[0][i] = 1.0;
  }
  // Fill each row with 0.0's other than first element, which is assigned 1.0
  for ( int i = 1; i < gridSize; ++i) {
    grid[i][0] = 1.0;
    for ( int j = 1; j < gridSize; ++j) {
      grid[i][j] = 0.0;
    }
  }*/

  int gridWithCopiesSize = gridSize+(gridSize)-2;
  float grid[gridWithCopiesSize][gridSize];
  // Fill top row with 1.0
  for (int i = 0; i < gridSize; ++i) {
    grid[0][i] = 1.0f;
  }
  printf("here1\n");


  // Fill each row with 0.0's other than first element, which is assigned 1.0
  for (int i = 1; i <= 2*gridSize-2; i++) {
    grid[i][0] = 1.0f;
    for (int j = 1; j < gridSize; j++) {
      grid[i][j] = 0.0f;
    }
  }


  /*grid[gridWithCopiesSize-1][0]   = 1.0f;
  for (int j = 1; j < gridSize; j++) {
    grid[gridWithCopiesSize-1][j] = 0.0f;
  }*/
//  printf("here3\n");
  printf("before: ==============\n");
  outputNonSquareGrid(gridSize, gridWithCopiesSize, *grid);

//  outputGrid(gridSize, *grid);

//  printf("before: %f \n", grid[1][1]);
//
//  averageEntireGrid(gridSize, *grid);
//
//  printf("after: %f \n", grid[1][1]);
//
//  outputGrid(gridSize, *grid);

/*  float threeRows[3][gridSize];
  getThreeRows(gridSize, 0, *grid, *threeRows);

  printf("before: \n");
  outputNonSquareGrid(gridSize, 3, *threeRows);

  float avgd[1][gridSize];
//  avgNonSquareGrid(gridSize, *threeRows, *avgd);
  avgSomeThreeRows(gridSize,1, *grid, *avgd);
  printf("after: \n");
  outputNonSquareGrid(gridSize, 1, *avgd);*/

//  outputFinalGrid(gridSize, grid);
  for (int i = 1; i <= gridWithCopiesSize-2; i=(i+2)) {
    avgSomeThreeRowsInPlace(gridSize, i, *grid);
  }


  printf("after: ==============\n");
  outputNonSquareGrid(gridSize, gridWithCopiesSize, *grid);
  return 0;

}

void averageEntireGrid(int gridSize, float g[]) {
  for (int y = 1; y < gridSize-1; y++){
    for (int x = 1; x < gridSize-1; x++){
//      printf("up %f | l %f | r %f | d %f \n", g[x + (y-1)*gridSize], g[x-1 + (y)*gridSize], g[x+1 + y*gridSize], g[x + (y+1)*gridSize]);
      g[x + y*gridSize] = (g[x + (y-1)*gridSize] +
             g[x-1 + (y)*gridSize] + g[x+1 + y*gridSize] +
			                    g[x + (y+1)*gridSize]) / 4 ;
    }
  }
}

void avgSomeThreeRows(int gridSize, int yStart, float g[], float averaged[]){
  int y = yStart;
  averaged[0] = g[gridSize];
  averaged[gridSize-1] = g[2*(gridSize-1)];
  for (int x = 1; x < gridSize-1; x++){
    averaged[x] = (g[x + (y-1)*gridSize] +
                   g[x-1 + (y)*gridSize] + g[x+1 + y*gridSize] +
                   g[x + (y+1)*gridSize]) / 4 ;
  }
}

void avgSomeThreeRowsInPlace(int gridSize, int yStart, float g[]){
  int y = yStart;
  for (int x = 1; x < gridSize-1; x++){
    g[x + yStart*gridSize] = (g[x + (y-1)*gridSize] +
                   g[x-1 + (y+1)*gridSize] + g[x+1 + (y+1)*gridSize] +
                              g[x + (y+1)*gridSize]) / 4 ;
  }
}

void avgNonSquareGrid(int gridSize, float g[], float averaged[]){
  int y = 1;
  averaged[0] = g[gridSize];
  averaged[gridSize-1] = g[2*(gridSize-1)];
  for (int x = 1; x < gridSize-1; x++){
    averaged[x] = (g[x + (y-1)*gridSize] +
            g[x-1 + (y)*gridSize] + g[x+1 + y*gridSize] +
                         g[x + (y+1)*gridSize]) / 4 ;
  }
}

void getThreeRows(int s, int startRow, float g[], float output[]) {
  for (int y = startRow; y < startRow+3; y++){
    for (int x = 0; x < s; x++){
      output[x + s*(y-startRow)] = g[x + s*y];
    }
  }
}

void outputGrid(int s, float grid[]) {
  printf("\n----- CURRENT GRID -----\n");
  for (int y = 0; y < s; y++){
    for (int x = 0; x < s; x++) {
      printf("%f ", grid[x + y*s]);
    }
    printf("\n");
  }
  printf("------------------------\n");
}

void outputNonSquareGrid(int w, int h, float grid[]) {
//  printf("\n----- CURRENT GRID -----\n");
  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++) {
      printf("%f ", grid[x + y*w]);
    }
    printf("\n");
  }
//  printf("------------------------\n");
}

void outputFinalGrid(int s, float grid[]) {
  printf("FINAL\n");
  int h = s*2-1;
  int w = s;
  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++) {
      printf("%f ", grid[x + y*w]);
    }
    printf("\n");
  }
}
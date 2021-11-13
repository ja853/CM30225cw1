#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void averageEntireGrid(int, float[]);
void outputGrid(int, float[]);
void outputNonSquareGrid(int, int, float[]);


int main(void){

  int gridSize = 10; //// grab this value from cmd args
  float grid[gridSize][gridSize];

  // create grid of size gridSize
  // fill top row with 1.0
  for ( int i = 0; i < gridSize; ++i) {
    grid[0][i] = 1.0;
  }
  // fill each row with 0.0 other than first element, which is assigned 1.0
  for ( int i = 1; i < gridSize; ++i) {
    grid[i][0] = 1.0;
    for ( int j = 1; j < gridSize; ++j) {
      grid[i][j] = 0.0;
    }
  }

  outputGrid(gridSize, *grid);

  printf("before: %f \n", grid[1][1]);

  averageEntireGrid(gridSize, *grid);

  printf("after: %f \n", grid[1][1]);

  outputGrid(gridSize, *grid);


  return 0;

}

void averageEntireGrid(int gridSize, float g[]) {
  //float tempGrid[gridSize][gridSize];
  float test = 1.0;
  float *newGrid = malloc((int)(sizeof(test))*gridSize*gridSize);
  memcpy(newGrid, g, (int)sizeof(test)*gridSize*gridSize);
  for (int y = 1; y < gridSize-1; y++){
    for (int x = 1; x < gridSize-1; x++){
//      printf("up %f | l %f | r %f | d %f \n", g[x + (y-1)*gridSize], g[x-1 + (y)*gridSize], g[x+1 + y*gridSize], g[x + (y+1)*gridSize]);
      g[x + y*gridSize] = (g[x + (y-1)*gridSize] +
             g[x-1 + (y)*gridSize] + g[x+1 + y*gridSize] +
			                    g[x + (y+1)*gridSize]) / 4 ;
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
  printf("\n----- CURRENT GRID -----\n");
  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++) {
      printf("%f ", grid[x + y*w]);
    }
    printf("\n");
  }
  printf("------------------------\n");
}
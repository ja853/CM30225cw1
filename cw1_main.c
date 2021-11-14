// gcc -Wall -Wextra -Wconversion cw1_main.c -o comp_cw1
// ./comp_cw1 gridSize

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copyDataToRowBelow(int, double[]);
void averageEntireGrid(int, double[]);
void outputGrid(int, double[]);
void outputNonSquareGrid(int, int, double[]);
void getThreeRows(int, int, double[], double[]);
void avgNonSquareGrid(int, double[], double[]);
void avgSomeThreeRows(int, int, double[], double[]);
void avgSomeThreeRowsInPlace(int, int, double[]);
void outputGridWithoutCopies(int, double[]);


int main(int argc, char *argv[]){
  // Get grid size from the cmd arguments.
  int gridSize;
  if (argc == 2){
    gridSize = (int)strtol(argv[1], NULL,10);
  } else {
    // If no size is specified, exit.
    printf("Grid size not specified, exiting \n");
    return 1;
  }

  // Create array variable of width gridSize and height gridSize+(gridSize)-2.
  //  this allows for space for the
  int gridWithCopiesSize = gridSize+(gridSize)-2;
  double grid[gridWithCopiesSize][gridSize];
  // Fill top row of the grid with 1.0s
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

  // Output the starting grid.
  printf("before avg: ==============\n");
  outputNonSquareGrid(gridSize, gridWithCopiesSize, *grid);

  // For each row that is not a copy, top row or bottom row, perform averaging function.
  for (int i = 1; i <= gridWithCopiesSize-2; i=(i+2)) {
    avgSomeThreeRowsInPlace(gridSize, i, *grid);
  }

  // Output the grid after one iteration of averaging.
  printf("after avg: ==============\n");
  outputNonSquareGrid(gridSize, gridWithCopiesSize, *grid);

  printf("after cpy to below: ==============\n");
  copyDataToRowBelow(gridSize, *grid);
  outputNonSquareGrid(gridSize, gridWithCopiesSize, *grid);

  printf("FINAL\n");
  outputGridWithoutCopies(gridSize, *grid);
  return 0;

}

void copyDataToRowBelow(int s, double grid[]) {
  for (int y = 1; y < s-1; y++){
    for (int x = 0; x < s; x++){
      grid[x + (y*2)*s] = grid[x + (y*2-1)*s];
    }
  }
}

void averageEntireGrid(int gridSize, double g[]) {
  for (int y = 1; y < gridSize-1; y++){
    for (int x = 1; x < gridSize-1; x++){
      g[x + y*gridSize] = (g[x + (y-1)*gridSize] +
             g[x-1 + (y)*gridSize] + g[x+1 + y*gridSize] +
			                    g[x + (y+1)*gridSize]) / 4 ;
    }
  }
}

void avgSomeThreeRows(int gridSize, int yStart, double grid[], double averaged[]){
  int y = yStart;
  averaged[0] = grid[gridSize];
  averaged[gridSize-1] = grid[2*(gridSize-1)];
  for (int x = 1; x < gridSize-1; x++){
    averaged[x] = (grid[x + (y-1)*gridSize] +
            grid[x-1 + (y)*gridSize] + grid[x+1 + y*gridSize] +
            grid[x + (y+1)*gridSize]) / 4 ;
  }
}

void avgSomeThreeRowsInPlace(int gridSize, int yStart, double grid[]){
  int y = yStart;
  for (int x = 1; x < gridSize-1; x++){
    grid[x + yStart*gridSize] = (grid[x + (y-1)*gridSize] +
            grid[x-1 + (y+1)*gridSize] + grid[x+1 + (y+1)*gridSize] +
            grid[x + (y+1)*gridSize]) / 4 ;
  }
}

void avgNonSquareGrid(int gridSize, double grid[], double averaged[]){
  int y = 1;
  averaged[0] = grid[gridSize];
  averaged[gridSize-1] = grid[2*(gridSize-1)];
  for (int x = 1; x < gridSize-1; x++){
    averaged[x] = (grid[x + (y-1)*gridSize] +
            grid[x-1 + (y)*gridSize] + grid[x+1 + y*gridSize] +
            grid[x + (y+1)*gridSize]) / 4 ;
  }
}

void getThreeRows(int s, int startRow, double grid[], double output[]) {
  for (int y = startRow; y < startRow+3; y++){
    for (int x = 0; x < s; x++){
      output[x + s*(y-startRow)] = grid[x + s*y];
    }
  }
}

void outputGrid(int s, double grid[]) {
  printf("\n----- CURRENT GRID -----\n");
  for (int y = 0; y < s; y++){
    for (int x = 0; x < s; x++) {
      printf("%f ", grid[x + y*s]);
    }
    printf("\n");
  }
  printf("------------------------\n");
}

void outputNonSquareGrid(int w, int h, double grid[]) {
//  printf("\n----- CURRENT GRID -----\n");
  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++) {
      printf("%f ", grid[x + y*w]);
    }
    printf("\n");
  }
//  printf("------------------------\n");
}

void outputGridWithoutCopies(int s, double grid[]) {
  for (int x = 0; x < s; x++) {
    printf("%f ", grid[x]);
  }
  printf("\n");
  for (int y = 1; y < s; y++){
    for (int x = 0; x < s; x++) {
      printf("%f ", grid[x + (y*2-1)*s]);
    }
    printf("\n");
  }
}
#include <stdio.h>

void average(int,int,float[]);

int main(void){
  printf("stuffs \n");
  //int gridHeight = 4;
  //int gridWidth = 4; 
  //float grid [gridHeight][gridWidth] = {
  float grid [4][4] = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0, 0.0}};
  printf("before: %f \n", grid[1][1]);

  average(4, 4, *grid);

  printf("after: %f \n", grid[1][1]);

  return 0;

}

void average(int gridH, int gridW, float g[]) {
  //  float tempGrid[gridH][gridW];
  for (int y = 1; y < gridH-1; y++){
    for (int x = 1; x < gridW-1; x++){
      printf("up %f | l %f | r %f | d %f \n", g[x + (y-1)*gridH], g[x-1 + (y)*gridH], g[x+1 + y*gridH], g[x + (y+1)*gridH]);
      g[x + y*gridH] = (g[x + (y-1)*gridH] + 
             g[x-1 + (y)*gridH] + g[x+1 + y*gridH] + 
			g[x + (y+1)*gridH]) / 4 ;
    }
  }
  
}

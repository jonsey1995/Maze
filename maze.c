#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXMAZE 100
#define MAZESIZE 10

void scanmap(char mazerow[MAXMAZE][MAXMAZE]);
void printmaze(char mazerow[MAXMAZE][MAXMAZE], int height);
void startpos(char mazerow[MAXMAZE][MAXMAZE], int rows, int cols, int *sx, int *sy);
void exitpos(char mazerow[MAXMAZE][MAXMAZE], int rows, int cols, int *ex, int *ey);
int explore(int y, int x, char mazerow[MAXMAZE][MAXMAZE],int rows, int cols);

int main() {
   char mazerow[MAXMAZE][MAXMAZE];
   scanmap(mazerow);
   printmaze(mazerow, MAZESIZE);
   int startx, starty, exitx, exity;

   startpos(mazerow, MAZESIZE, MAZESIZE, &startx, &starty);
   //printf("START = %d %d \n", starty, startx);
   exitpos(mazerow, MAZESIZE, MAZESIZE, &exitx, &exity);
   //printf("END = %d %d \n", exity, exitx);

   explore(starty, startx, mazerow, MAZESIZE, MAZESIZE);

   return 0;
}
void scanmap(char mazerow[MAXMAZE][MAXMAZE]){
   char c;
   int i = 0;
   int j = 0;
   FILE *fp;
   char str[20];
   fp = fopen("maze.txt", "r");
   if (fp == NULL) {
     printf("could not open file\n");
     return;
   }
   while (fgets(str, 20, fp) != NULL) {
      strcpy(mazerow[i], str);
      i++;
   }
   fclose(fp);
}
void printmaze(char mazerow[MAXMAZE][MAXMAZE], int height) {
   int i;
   for (i = 0; i <= height; i++) {
      printf("%s", mazerow[i]);
   }
}
void startpos(char mazerow[MAXMAZE][MAXMAZE], int rows, int cols, int *sx, int *sy) {
   int i, j;
   for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
         if (mazerow[i][j] == 'S') {
            *sy = i;
            *sx = j;
         }
      }
   }
}
void exitpos(char mazerow[MAXMAZE][MAXMAZE], int rows, int cols, int *ex, int *ey) {
   int i, j;
   for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
         if (mazerow[i][j] == 'E') {
            *ey = i;
            *ex = j;
         }
      }
   }
}
int explore(int y, int x, char mazerow[MAXMAZE][MAXMAZE],int rows, int cols) {
   system("clear");
   mazerow[y][x] = '.';
   printmaze(mazerow, MAZESIZE);
   sleep(1);
   /*BASE CASES###################################################*/
   /*if at exit*/
   if (mazerow[y][x] == 'E') {
      return 1;
   }
   /*if outside maze*/
   if(x < 0 || x > rows-1 || y < 0 || y > cols-1) {
      printf("Out of Bounds\n");
      return 0;
   }
   /*wall*/
   if (mazerow[x][y] == '#') {
      printf("Wall Reached!\n");
   }
   //go north
   if (mazerow[y+1][x] == ' ' || mazerow[y+1][x] == 'E') {
      explore(y+1, x,mazerow, MAZESIZE, MAZESIZE);
   }
   //go south
   if (mazerow[y-1][x] == ' ' || mazerow[y-1][x] == 'E') {
      explore(y-1, x,mazerow, MAZESIZE, MAZESIZE);
   }
   //go east
   if (mazerow[y][x+1] == ' ' || mazerow[y][x+1] == 'E') {
      explore(y, x+1,mazerow, MAZESIZE, MAZESIZE);
   }
   //go west
   if (mazerow[y][x-1] == ' ' || mazerow[y][x-1] == 'E') {
      explore(y, x-1,mazerow, MAZESIZE, MAZESIZE);
   }
   printf("Yay You finished!\n");
}

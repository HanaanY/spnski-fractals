#define BRD_W 27
#define BRD_H 27
#define LIMIT 9
#define LIMITSIDE 3
#define MIDDLE 5
#define GRIDSIZE BRD_H * BRD_W
#define ON '.'
#define OFF ' '

#include <stdio.h>
#include <stdlib.h>

typedef struct square{
   int x1, x2, y1, y2;
} Square;


void init_vertices(Square *sq0);
void deleteSquare(char board[][BRD_W], Square *sq0);
void resetBoard(char board[][BRD_W]);
int  sCarpet(char board[][BRD_W], Square *sq0);
void printBoard(char board[][BRD_W]);
void drawSquare(char board[][BRD_W], Square *sq0, Square *sq1);


int main(void){
   char board[BRD_H][BRD_W];
   Square sq0;

   init_vertices(&sq0);
   printBoard(board);
   drawSquare(board, &sq0, &sq0);
   sCarpet(board, &sq0);

   return 0;
}

void init_vertices(Square *sq0){
   sq0->x1 = 0;
   sq0->x2 = BRD_W;
   sq0->y1 = 0;
   sq0->y2 = BRD_H;
}

void drawSquare(char board[][BRD_W], Square *sq0, Square *sq1){
   int i, j;
   for(i = sq0->y1; i < sq0->y2; i++){
      for(j = sq0->x1; j < sq0->x2; j++){
         board[i][j] = OFF;
      }
   }
   for(i = sq1->y1; i < sq1->y2; i++){
         for(j = sq1->x1; j < sq1->x2; j++){
         board[i][j] = ON;
      }
   }

}

void deleteSquare(char board[][BRD_W], Square *sq0){
   int i, j;
   for(i = sq0->y1; i < sq0->y2; i++){
      for(j = sq0->x1; j < sq0->x2; j++){
         board[i][j] = OFF;
      }
   }
}

int sCarpet(char board[][BRD_W], Square *sq0){
   Square a[LIMIT];
   int i, j, size, index = 0;
   size = sq0->x2 - sq0->x1;

   /* base case*/
   if(size < LIMIT){
      return 1;
   }

   /* Split squares into 9 */
   for(i = 0; i < LIMITSIDE; i++){
      for(j = 0; j < LIMITSIDE; j++, index = 3 * i + j){
         a[index].x1 = sq0->x1 + j * size/3;
         a[index].x2 = sq0->x1 + (j + 1) * size/3;
         a[index].y1 = sq0->y1 + i * size/3;
         a[index].y2 = sq0->y1 + (i + 1) * size/3;
      }
   }

   deleteSquare(board, &(a[MIDDLE - 1]));
   printBoard(board);

   for(i = 0; i < LIMIT; i++){
      sCarpet(board, &(a[i]));
   }
   return 0;
}


void printBoard(char board[][BRD_W]){
   int i, j;
   printf("\n");
   for(i = 0; i < BRD_H; i++){
      for(j = 0; j < BRD_W; j++){
         printf("%c", board[i][j]);
      }
   printf("\n");
   }
   printf("\n");
}

#define BRD_W 64
#define BRD_H 64
#define LIMIT 8
#define GRIDSIZE BRD_H * BRD_W
#define ON '.'
#define OFF ' '
#define MILLISECONDDELAY
#define RED 255
#define GREEN 0
#define BLUE 0



#include <stdio.h>
#include <stdlib.h>
#include "neillsdl2.h"

typedef struct square{
   int x1, x2, y1, y2;
} Square;

void init_vertices(Square *sq0);
void drawSquare(char board[][BRD_W], Square *sq0, Square *sq1);
void resetBoard(char board[][BRD_W]);
int  sTriangle(char board[][BRD_W], Square *sq0);
void printBoard(char board[][BRD_W]);
void setupColour(SDL_Simplewin *sw);


int main(void){
   char board[BRD_H][BRD_W];
   Square sq0;
   SDL_Simplewin sw;

   init_vertices(&sq0);
   Neill_SDL_Init(&sw);

   resetBoard(board);
   drawSquare(board, &sq0, &sq0);
   sTriangle(board, &sq0);
   printBoard(board);

   return 0;
}

void init_vertices(Square *sq0){
   sq0->x1 = 0;
   sq0->x2 = BRD_W;
   sq0->y1 = 0;
   sq0->y2 = BRD_H;
}

void setupColour(SDL_Simplewin *sw){
  Neill_SDL_SetDrawColour(sw, RED, GREEN, BLUE);
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

void resetBoard(char board[][BRD_W]){
   int i, j;
   for(i = 0; i < BRD_H; i++){
      for(j = 0; j < BRD_W; j++){
         board[i][j] = OFF;
      }
   }
}

int sTriangle(char board[][BRD_W], Square *sq0){
   int midx, midy, oqx, tqx;
   Square sq1, sq2, sq3;
   /* base case*/
   if(sq0->x2 - sq0->x1 < LIMIT){
      return 1;
   }

   /* Find midpoints */
   midx = sq0->x1 + (sq0->x2 - sq0->x1) / 2;
   midy = sq0->y1 + (sq0->y2 - sq0->y1) / 2;
   oqx = sq0->x1 + (sq0->x2 - sq0->x1) / 4;
   tqx =  midx + (sq0->x2 - sq0->x1) / 4;
   /* Set up three new squares if possible */
   sq1.x1 = oqx;
   sq1.x2 = tqx;
   sq1.y1 = sq0->y1;
   sq1.y2 = midy;
   /* Now sq2 */
   sq2.x1 = sq0->x1;
   sq2.x2 = midx;
   sq2.y1 = midy;
   sq2.y2 = sq0->y2;
   /* Now sq3 */
   sq3.x1 = midx;
   sq3.x2 = sq0->x2;
   sq3.y1 = midy;
   sq3.y2 = sq0->y2;

   drawSquare(board, sq0, &sq1);
   drawSquare(board, &sq2, &sq2);
   drawSquare(board, &sq3, &sq3);
   sTriangle(board, &sq1);
   sTriangle(board, &sq2);
   sTriangle(board, &sq3);
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

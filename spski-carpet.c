#include <stdio.h>
#include <stdlib.h>
#include "neillsdl2.h"
#define LIMIT 9
#define LIMITSIDE 3
#define MIDDLE 5
#define MILLISECONDDELAY 5
#define GRIDSIZE WWIDTH * WHEIGHT
#define RED 255
#define GREEN 0
#define BLUE 0

typedef SDL_Rect Square;

void init(Square *sq0);
int  sCarpet(SDL_Simplewin *sw, Square *sq0);
void drawSquare(SDL_Simplewin *sw, Square *x);
void clearSquare(SDL_Simplewin *sw, Square *x);

int main(void){
   SDL_Simplewin sw;
   Square sq0;

   init(&sq0);
   Neill_SDL_Init(&sw);
   drawSquare(&sw, &sq0);
   sCarpet(&sw, &sq0);

   return 0;
}

void init(Square *sq0){
   sq0->x = 0;
   sq0->y = 0;
   sq0->w = WWIDTH;
   sq0->h = WHEIGHT;
}

void drawSquare(SDL_Simplewin *sw, Square *x){
   Neill_SDL_SetDrawColour(sw, RED, GREEN, BLUE);
   SDL_RenderFillRect(sw->renderer, x);
   SDL_RenderPresent(sw->renderer);
   SDL_UpdateWindowSurface(sw->win);
}

void deleteSquare(SDL_Simplewin *sw, Square *x){
   Neill_SDL_SetDrawColour(sw, 0, 0, 0);
   SDL_RenderFillRect(sw->renderer, x);
   SDL_RenderPresent(sw->renderer);
   SDL_UpdateWindowSurface(sw->win);
}

int sCarpet(SDL_Simplewin *sw, Square *sq0){
   Square a[LIMIT];
   int i, j, new_w, new_h, index = 0;

   /* base case*/
   if(sq0->w < LIMIT){
      return 1;
   }

   /* make new squares 1/3 of the size */
   new_w = sq0->w / 3;
   new_h = sq0->h / 3;

   /* Split squares into 9 */
   for(i = 0; i < LIMITSIDE; i++){
      for(j = 0; j < LIMITSIDE; j++, index = 3 * i + j){
         a[index].x = sq0->x + j * sq0->w /3;
         a[index].w = new_w;
         a[index].y = sq0->y + i * sq0->h /3;
         a[index].h = new_h;
      }
   }
   Neill_SDL_Events(sw);
   deleteSquare(sw, &(a[MIDDLE - 1]));
   SDL_Delay(MILLISECONDDELAY);
   if(sw->finished){
     exit(EXIT_SUCCESS);
     /* Clear up graphics subsystem */
     atexit(SDL_Quit);
   }
   for(i = 0; i < LIMIT; i++){
      sCarpet(sw, &(a[i]));
   }
   return 0;
}

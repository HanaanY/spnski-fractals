#include <stdio.h>
#include <stdlib.h>
#include "neillsdl2.h"

#define LIMIT 8
#define GRIDSIZE WWIDTH * WHEIGHT
#define MILLISECONDDELAY 5
#define RED 255
#define GREEN 0
#define BLUE 0


typedef SDL_Rect Square;

void init(Square *sq0);
void drawSquare(SDL_Simplewin *sw, Square *sq1);
int  sTriangle(SDL_Simplewin *sw, Square *sq0);
void clearSquare(SDL_Simplewin *sw, Square *x);

int main(void){
   SDL_Simplewin sw;
   Square sq0;

   init(&sq0);
   Neill_SDL_Init(&sw);
   drawSquare(&sw, &sq0);
   sTriangle(&sw, &sq0);

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

void clearSquare(SDL_Simplewin *sw, Square *x){
   Neill_SDL_SetDrawColour(sw, 0, 0, 0);
   SDL_RenderFillRect(sw->renderer, x);
   SDL_RenderPresent(sw->renderer);
   SDL_UpdateWindowSurface(sw->win);
}

int sTriangle(SDL_Simplewin *sw, Square *sq0){
   int midx, midy, oqx, new_w, new_h;
   Square sq1, sq2, sq3;
   /* base case*/
   if(sq0->w < LIMIT){
      return 1;
   }
   /* make new squares half the size */
   new_w = sq0->w / 2;
   new_h = sq0->h / 2;

   /* Find midpoints */
   midx = sq0->x + sq0->w / 2;
   midy = sq0->y + sq0->h / 2;
   oqx = sq0->x + sq0->w / 4;
   /* Set up three new squares if possible */
   sq1.x = oqx;
   sq1.w = new_w;
   sq1.y = sq0->y;
   sq1.h = new_h;
   /* Now sq2 */
   sq2.x = sq0->x;
   sq2.w = new_w;
   sq2.y = midy;
   sq2.h = new_h;
   /* Now sq3 */
   sq3.x = midx;
   sq3.w = new_w;
   sq3.y = midy;
   sq3.h = new_h;

   Neill_SDL_Events(sw);
   clearSquare(sw, sq0);
   SDL_Delay(MILLISECONDDELAY);
   drawSquare(sw, &sq1);
   SDL_Delay(MILLISECONDDELAY);
   drawSquare(sw, &sq2);
   SDL_Delay(MILLISECONDDELAY);
   drawSquare(sw, &sq3);
   SDL_Delay(MILLISECONDDELAY);
   if(sw->finished){
     exit(EXIT_SUCCESS);
     /* Clear up graphics subsystem */
     atexit(SDL_Quit);
   }
   sTriangle(sw, &sq1);
   sTriangle(sw, &sq2);
   sTriangle(sw, &sq3);

   return 0;
}

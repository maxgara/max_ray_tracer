//compile with gcc <filename>.c -lSDL2 -lSDL2_image
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "color.c"


int quick_display_canvas(Canvas *canvas){
  SDL_Init( SDL_INIT_VIDEO );
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(100, 100, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0,255,0, 255);

  for(int i=0;i<100;i++){
    for(int j=0;j<100;j++){
      Color pixel = canvas->pixels[i][j];
      // SDL_SetRenderDrawColor(renderer,pixel.r , pixel.g, pixel.b, 255);
      SDL_RenderDrawPoint(renderer, j, i); //Renders on middle of screen.
    }
    SDL_RenderPresent(renderer);
  }
  SDL_Delay(10000);
}

int main(){
  Canvas can = {100,100};
  for(int i=0;i<100;i++){
    for(int j=0;j<100;j++){
      Color color = new_Color(i,j,j-i);
      correct_color(&color);
      write_pixel(&can, i, j, color);

    }
  }
  quick_display_canvas(&can);
}

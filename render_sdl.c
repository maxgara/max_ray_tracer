#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//render a Canvas in a new window
int render_sdl(Canvas *can, int canvas_x_size, int canvas_y_size){
  if (SDL_Init( SDL_INIT_VIDEO) != 0)
  {
    printf("failed init\n");
    return 1;
  }
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  // Uint32 pixels[1024][768];
  void *pixels;
  SDL_CreateWindowAndRenderer(canvas_x_size, canvas_y_size, 0, &window, &renderer);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, canvas_x_size, canvas_y_size);
  if(texture == NULL){
    printf("failed texture creation\n");
    return 1;
  }
  else{
    printf("texture:%p\n",texture);
  }

  SDL_RenderClear(renderer);
  int pitch; //hopefully this doesn't do anything?
  if( SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0){
    printf("bad lock\n");
    return 1;
  };

  printf("pitch:%d\n",pitch);
  int blue = 255;
  int green = 255<<8;
  int red = 255<<16;
  for(int i=0;i<canvas_x_size * canvas_y_size;i++){
    //pixel color specified in format SDL_PIXELFORMAT_ARGB8888
    *(int *)pixels = can->pixels[i/canvas_y_size][i%canvas_x_size];
    pixels = (int *)pixels + 1;
  }
  SDL_UnlockTexture(texture);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(5000);



  SDL_Quit();
  printf("done\n");
  return 0;

}

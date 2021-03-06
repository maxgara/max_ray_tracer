#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//this program creates a window, renderer and texture, locks the texture then draws directly to the pixel integers and renders the texture
int main(){
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
  SDL_CreateWindowAndRenderer(1024, 768, 0, &window, &renderer);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1024, 768);
  if(texture == NULL){
    printf("failed texture creation\n");
    return 1;
  }
  else{
    printf("texture:%p\n",texture);
  }

  SDL_RenderClear(renderer);
  int pitch;
  if( SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0){
    printf("bad lock\n");
    return 1;
  };

  // memset(pixels, 255, 1024 * 768);
  printf("pitch:%d\n",pitch);
  int blue = 255;
  int green = 255<<8;
  int red = 255<<16;
  for(int i=0;i<1024 * 768;i++){
    //pixel color specified in format SDL_PIXELFORMAT_ARGB8888
    *(int *)pixels = green;
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

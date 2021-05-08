//compile with gcc sdl_graphics_test.c -lSDL2 -lSDL2_image
#include "sdl_graphics.c"

int main(int argc, char *argv[]){
  char *image_path = "ppm_out.ppm";

  printf("initializing window\n");
    if ( init_sdl_window() ){
      printf("window initialized\n");
      printf("trying to load media %s\n",image_path);
      if ( loadMedia(image_path) ){
        printf("loaded media\n");
        SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
        SDL_UpdateWindowSurface( gWindow );
        SDL_Delay( 5000 );
        close_SDL();
      }
    }
    printf("hello sdl\n");
return 0;
}

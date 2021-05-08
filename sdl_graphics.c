//compile with gcc <filename>.c -lSDL2 -lSDL2_image
#ifndef SDL_GRAPHICS_SEEN
#define SDL_GRAPHICS_SEEN
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//Starts up SDL and creates window
bool init_sdl_window();
//Loads media
bool loadMedia(char *filename);
//Frees media and shuts down SDL
void close_SDL();

bool init_sdl_window(){
    bool success = true;
    SDL_Surface* screenSurface = NULL;
    //Initialize SDL

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success=false;
    }
    else{
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success=false;
        }
        else{
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    return success;
}

bool loadMedia(char *filename){
    bool success = true;
    gHelloWorld = IMG_Load(filename);
    if ( gHelloWorld == NULL){
      printf("unable to load image file %s\n",filename);
      success = false;
    }
    //SDL_SaveBMP(gHelloWorld,"bmp_out.bmp");
    return success;
}

void close_SDL(){
  SDL_FreeSurface( gHelloWorld );
  gHelloWorld = NULL;
  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  //Quit SDL subsystems
  SDL_Quit();
}

bool quick_display_file(char *image_path){
  //printf("initializing window\n");
    if ( init_sdl_window() ){
      // printf("window initialized\n");
      // printf("trying to load media %s\n",image_path);
      if ( loadMedia(image_path) ){
        // printf("loaded media\n");
        SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
        SDL_UpdateWindowSurface( gWindow );
        SDL_Delay( 5000 );
        close_SDL();
      }
    }
return 0;
}
#endif

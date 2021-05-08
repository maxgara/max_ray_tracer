#include <SDL2/SDL.h>
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
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close_SDL();

int main(int argc, char *argv[]){

    if ( init() ){
      if ( loadMedia() ){
        SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
        SDL_UpdateWindowSurface( gWindow );
        SDL_Delay( 2000 );
        close_SDL();
      }
    }
    printf("hello sdl\n");

return 0;
}

bool init(){
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

bool loadMedia(){
    bool success = true;
    gHelloWorld = SDL_LoadBMP("01.bmp");
    if ( gHelloWorld == NULL){
      printf("unable to load bmp %s\n","01.bmp");
      success = false;
    }
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

#include "ray.c"
#include "color.c"
#include "render_sdl.c"
#include <time.h>
#define SIZE 50


int main(){
  Ray ray;
  Color color_arr[SIZE][SIZE];
  char display[SIZE][SIZE];
  Color green = new_Color(0,0,255,0);
  Color blue = new_Color(0,0,0,255);
  Canvas can = {CANVAS_X_SIZE,CANVAS_Y_SIZE};
  init_sdl(CANVAS_X_SIZE,CANVAS_Y_SIZE);
  for(int t=0;t<100;t++){
  struct timespec sleeptime = {0,59999999};
  // nanosleep(&sleeptime,NULL);
  float time = t;
  Sphere sphere = new_Sphere();
  sphere=transform_sphere(sphere, get_scale(SIZE/5,SIZE/5,SIZE/5));
  sphere = transform_sphere(sphere, get_translation(-time,time,0));
  Intersection intersection1;
  Intersection intersection2;
  for(int i=0;i<CANVAS_X_SIZE;i++){
    printf("\n");
    for(int j=0;j<CANVAS_Y_SIZE;j++){
      // printf("got into loop\n");
      Tuple origin, direction;
      origin = new_Point(j,i,0);
      direction = new_Vector(0,0,1);
      ray = new_Ray(origin,direction);
      // print_tup(ray_arr[i][j].origin);
      // print_tup(ray_arr[i][j].direction);
      if(get_ray_sphere_intersections(ray, sphere, &intersection1, &intersection2)==0){
        can.pixels[i][j] = green;
      }
      else{
        can.pixels[i][j] = blue;
      }
    }
  }
  render_existing_sdl(&can, CANVAS_X_SIZE, CANVAS_Y_SIZE);
}
  SDL_Quit();
  // render_sdl(&can, CANVAS_X_SIZE, CANVAS_Y_SIZE);
}

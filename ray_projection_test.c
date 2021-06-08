#include "ray.c"
#include "color.c"
#include "render_sdl.c"
#include <time.h>
#define SIZE 50
#ifndef CANVAS_X_SIZE
#define CANVAS_X_SIZE 500
#endif
#ifndef CANVAS_Y_SIZE
#define CANVAS_Y_SIZE 500
#endif

int main(){
  Ray ray_arr[SIZE][SIZE];
  Color color_arr[SIZE][SIZE];
  char display[SIZE][SIZE];
  Color green = new_Color(0,0,255,0);
  Color blue = new_Color(0,0,0,255);
  Canvas can = {CANVAS_X_SIZE,CANVAS_Y_SIZE};
    struct timespec sleeptime = {0,59999999};
    nanosleep(&sleeptime,NULL);
    float time = t/4;
  Sphere sphere = new_Sphere();
  sphere=transform_sphere(sphere, get_scale(SIZE/5,SIZE/5,SIZE/5));
  sphere = transform_sphere(sphere, get_translation(-time,time,0));
  Intersection intersection1;
  Intersection intersection2;
  for(int i=0;i<SIZE;i++){
    printf("\n");
    for(int j=0;j<SIZE;j++){
      // printf("got into loop\n");
      Tuple origin, direction;
      origin = new_Point(j,i,0);
      direction = new_Vector(0,0,1);
      ray_arr[i][j] = new_Ray(origin,direction);
      // print_tup(ray_arr[i][j].origin);
      // print_tup(ray_arr[i][j].direction);
      if(get_ray_sphere_intersections(ray_arr[i][j], sphere, &intersection1, &intersection2)==0){
        can.pixels[i][j] = green;
      }
      else{
        can.pixels[i][j] = blue;
      }
    }
  }
  render_sdl(&can, CANVAS_X_SIZE, CANVAS_Y_SIZE);
}

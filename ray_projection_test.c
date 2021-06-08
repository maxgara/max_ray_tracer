#include "ray.c"
#include "color.c"
#include "render_sdl.c"
#include <time.h>
#define SIZE 50


int main(){
  Ray ray;
  Color color_arr[SIZE][SIZE];
  char display[SIZE][SIZE];
  Color green = new_Color(0,0,1,0);
  Color blue = new_Color(0,0,0,255);
  Canvas can = {CANVAS_X_SIZE,CANVAS_Y_SIZE};
  init_sdl(CANVAS_X_SIZE,CANVAS_Y_SIZE);
  for(int t=0;t<100;t++){
  struct timespec sleeptime = {0,59999999};
  // nanosleep(&sleeptime,NULL);
  float time = t;
  Sphere sphere = new_Sphere();
  M3 sphere_scale = get_scale(SIZE,SIZE,SIZE);
  transform_sphere(&sphere, &sphere_scale);
  Tuple sphere_shift = new_Tuple(time/4,time/4,time/4);
  translate_sphere(&sphere, sphere_shift);
  Intersection intersection1;
  Intersection intersection2;
  for(int i=0;i<CANVAS_X_SIZE;i++){
    printf("\n");
    for(int j=0;j<CANVAS_Y_SIZE;j++){
      // printf("got into loop\n");
      Tuple origin, direction;
      origin = new_Tuple(j,i,0);
      direction = new_Tuple(0,0,1);
      ray = new_Ray(origin,direction);
      // print_tup(ray_arr[i][j].origin);
      // print_tup(ray_arr[i][j].direction);
      if(get_ray_sphere_intersections(&ray, sphere, &intersection1, &intersection2)==0){
        int intensity = intersection1.t/10;
        // printf("intersection1.t:%f\n",intersection2.t);
        can.pixels[i][j] = (green * intensity);
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

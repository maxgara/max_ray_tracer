#include "ray.c"
#include "color.c"
#include <time.h>
#define SIZE 50

int main(){
  Ray ray_arr[SIZE][SIZE];
  Color color_arr[SIZE][SIZE];
  char display[SIZE][SIZE];
  Color green = new_Color(0,0,250/2);
  for(int t=0;t<100;t++){
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
        color_arr[i][j] = green;
        display[i][j] = '-';
      }
      else{
        display[i][j] = '0';
      }
    }
  }
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      printf("%c",display[j][i]);
    }
    printf("\n");
  }
}
}

#include "ray.c"

int main(){
  printf("ray test\n");
  Point o = new_Point(0,4,0);
  Vector d = new_Vector(1,0,0);
  Ray r = new_Ray(o,d);
  printf("point:\n");
  // print_tup(position(r,1));
  Sphere sphere = new_Sphere();
  Sphere sphere2 = new_Sphere();
  // sphere2 = transform_sphere(sphere2,scale_M4(IDENTITY_4,2));
  sphere2 = transform_sphere(sphere2,get_translation(0,4,0));
  printf("sphere (%d,%d) transform:\n",sphere2.transform.R, sphere2.transform.C);

  print_matrix(sphere2.transform);
  printf("inverse:\n");
  print_matrix(inverse_M4(sphere2.transform));

  Intersection intersection1, intersection2;
  if(get_ray_sphere_intersections(r,sphere2,&intersection1,&intersection2)==0){
    printf("tvalue:%f, objectID:%d\n",intersection1.t, intersection1.id);
    printf("intersection_point:");
    print_tup(position(r,intersection1.t));
    printf("tvalue:%f, objectID:%d\n",intersection2.t, intersection2.id);
  };
}

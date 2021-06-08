#ifndef RAY_SEEN
#define RAY_SEEN
#include <stdio.h>
#include <math.h>
#include "tuple.c"
#include "matrix.c"
typedef struct{
  Point origin;
  Vector direction;
}Ray;

typedef struct{
  int id;
  M3 transform;
  Tuple shift;
}Sphere;

typedef struct{
  int id; //id of object intersected by ray
  float t; //t value of ray r=p+vt at intersection
}Intersection;

Sphere new_Sphere(){
  static int id = 0;
  Sphere out;
  out.id = id;
  out.transform = IDENTITY_3;
  out.shift = new_Tuple(0,0,0);
  id++;
  return out;
}
int transform_sphere(Sphere *sphere, M3 *transform){
  sphere->transform = M3_prod(transform,&sphere->transform);
  return 0;
}
int translate_sphere(Sphere *sphere, Tuple translation){
  sphere->shift = add_tup(&sphere->shift, &translation);
  return 0;
}
Ray new_Ray(Tuple origin, Tuple direction){
  Ray out;
  out.origin = origin;
  out.direction = direction;
  return out;
}
Intersection new_Intersection(int id, float t){
  //slightly redundant but whatever
  Intersection out;
  out.id = id;
  out.t = t;
  return out;
}

Tuple position(Ray ray, float t){
  Tuple out;
  out.x = ray.origin.x + (ray.direction.x * t);
  out.y = ray.origin.y + (ray.direction.y * t);
  out.z = ray.origin.z + (ray.direction.z * t);
  return out;
}
int transform_ray(Ray *ray, M3 *matrix){
  ray->origin = mvprod(matrix,&ray->origin);
  ray->direction = mvprod(matrix,&ray->direction);
  return 0;
}
int translate_ray(Ray *ray, Tuple shift){
  ray->origin = add_tup(&ray->origin, &shift);
}

int get_ray_sphere_intersections(Ray *ray, Sphere sphere, Intersection *intersection1, Intersection *intersection2){
  //r = p + vt
  //magnitude(r) = 1
  M3 sphere_transform_inverse = inverse_M3(&sphere.transform);
  if(det_M3(&sphere.transform)==0){
    //inefficient test, recomputing determinant
    printf("failed to invert\n");
    return 1;
  }
  Ray adjusted_ray = *ray;
  transform_ray(&adjusted_ray, &sphere_transform_inverse); // so we can treat sphere as unit sphere
  translate_ray(&adjusted_ray, scale_tup(&sphere.shift,-1));
  // print_tup(adjusted_ray.origin);
  // print_tup(adjusted_ray.direction);
  Vector p = adjusted_ray.origin;
  Vector v = adjusted_ray.direction;
  float discriminant = pow(dot(&p,&v),2)-(dot(&v,&v) * (dot(&p,&p) - 1));
  float denominator = dot(&v,&v);
  if(discriminant < 0){
    return 1; //no intersection
  }
  else if (denominator == 0){
    printf("get_ray_sphere_intersections: zero length vector input\n");
    return 1;
  }
  float t1 = (-dot(&p,&v) + sqrt(discriminant)) / dot(&v,&v);
  float t2 = (-dot(&p,&v) - sqrt(discriminant)) / dot(&v,&v);
  *intersection1 = new_Intersection(sphere.id,t1);

  *intersection2 = new_Intersection(sphere.id,t2);
  return 0;
}

#endif

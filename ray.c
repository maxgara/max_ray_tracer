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
  M4 transform;
}Sphere;

typedef struct{
  int id; //id of object intersected by ray
  float t; //t value of ray r=p+vt at intersection
}Intersection;

Sphere new_Sphere(){
  static int id = 0;
  Sphere out;
  out.id = id;
  out.transform = IDENTITY_4;
  id++;
  return out;
}
Sphere transform_sphere(Sphere sphere, M4 transform){
  sphere.transform = M4_prod(transform,sphere.transform);
  return sphere;
}

Ray new_Ray(Point origin, Vector direction){
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

Point position(Ray ray, float t){
  Point out;
  out.x = ray.origin.x + (ray.direction.x * t);
  out.y = ray.origin.y + (ray.direction.y * t);
  out.z = ray.origin.z + (ray.direction.z * t);
  return out;
}
Ray transform_ray(Ray ray, M4 matrix){
  Ray out;
  out.origin = mvprod(matrix,ray.origin);
  out.direction = mvprod(matrix,ray.direction);
  return out;
}

int get_ray_sphere_intersections(Ray ray, Sphere sphere, Intersection *intersection1, Intersection *intersection2){
  //r = p + vt
  //magnitude(r) = 1
  M4 sphere_transform_inverse = inverse_M4(sphere.transform);
  if(sphere_transform_inverse.R!=4){
    printf("failed to invert\n");
    return 1;
  }
  Ray adjusted_ray = transform_ray(ray, sphere_transform_inverse); // so we can treat sphere as unit sphere
  // print_tup(adjusted_ray.origin);
  // print_tup(adjusted_ray.direction);
  Vector p = adjusted_ray.origin;
  Vector v = adjusted_ray.direction;
  float discriminant = pow(dot(p,v),2)-(dot(v,v) * (dot(p,p) - 1));
  float denominator = dot(v,v);
  if(discriminant < 0){
    return 1; //no intersection
  }
  else if (denominator == 0){
    printf("get_ray_sphere_intersections: zero length vector input\n");
    return 1;
  }
  float t1 = (-dot(p,v) + sqrt(discriminant)) / dot(v,v);
  float t2 = (-dot(p,v) - sqrt(discriminant)) / dot(v,v);
  *intersection1 = new_Intersection(sphere.id,t1);
  *intersection2 = new_Intersection(sphere.id,t2);
  return 0;
}

#endif

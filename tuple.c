#ifndef TUPLE_SEEN
#define TUPLE_SEEN

#include <stdio.h>
#include <math.h>
#define Vector Tuple
#define Point Tuple
#define MIN_SIGNIFICANT_F 0.00001
typedef struct{
  union{
    float x;
    int r;
  };
  union{
    float y;
    int g;
  };
  union{
    float z;
    int b;
  };
  float w;
}Tuple;

Vector new_Vector(float x, float y, float z){
  Tuple out = {x,y,z,0.0};
  return out;
}
Point new_Point(float x, float y, float z){
  Tuple out = {x,y,z,1.0};
  return out;
}
void print_tup(Vector v){
  printf("(%f,%f,%f,%f)\n",v.x,v.y,v.z,v.w);
}

int is_point(Tuple t){
  if(t.w == 1.0){
    return 1;
  }
}
Tuple add_tup(Tuple A, Tuple B){
  Tuple out = {A.x+B.x, A.y+B.y, A.z+B.z, A.w+B.w};
  if(out.w!=1 && out.w!= 0){
    printf("bad tuple add! Result w=%f",out.w);
  }
  return out;
}
Tuple subtract_tup(Tuple A, Tuple B){
  //A-B
  Tuple out = {A.x-B.x, A.y-B.y, A.z-B.z, A.w-B.w};
  if(out.w!=1 && out.w!= 0){
    printf("bad tuple subtract! Result w=%f\n",out.w);
  }

  return out;
}
Tuple scale_tup(Tuple tup, float scale){
  Tuple out = {tup.x*scale, tup.y*scale, tup.z*scale};
  return out;
}
float tup_magnitude(Tuple tup){
  return sqrt(tup.x*tup.x + tup.y*tup.y + tup.z*tup.z);
}
Tuple normalize(Tuple tup){
  float m = tup_magnitude(tup);
  Tuple out = {tup.x/m,tup.y/m,tup.z/m};
  return out;
}
float dot(Tuple A, Tuple B){
  float out = A.x*B.x + A.y*B.y + A.z*B.z;
  return out;
}
Vector cross(Vector A, Vector B){
  float x = A.y * B.z - A.z * B.y;
  float y = A.z * B.x - A.x * B.z;
  float z = A.x * B.y - A.y * B.x;
  Vector out = {x,y,z,0.0};
  return out;
}

int is_equal_tup(Tuple A, Tuple B){
  Tuple diff = subtract_tup(B,A);
  float rough_magnitude = fabs(diff.x) + fabs(diff.y) + fabs(diff.z);
  if(rough_magnitude<MIN_SIGNIFICANT_F){
    return 1;
  }
  return 0;
}
/*
int main(){
  Vector t = new_Vector(1,0,0);
  Point p = new_Point(0,1,0);
  printf("mag:%f\n",tup_magnitude(p));
  Tuple p1 = normalize(p);
  print_tup(p1);
  //print_Point(p);
  Tuple c = cross(t,p);
  print_tup(c);
  return 0;
}*/
#endif

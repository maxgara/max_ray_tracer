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

Vector new_Vector(float x, float y, float z);
Point new_Point(float x, float y, float z);
void print_tup(Vector v);
int is_point(Tuple t);
Tuple add_tup(Tuple A, Tuple B);
Tuple subtract_tup(Tuple A, Tuple B);
Tuple scale_tup(Tuple tup, float scale);
float tup_magnitude(Tuple tup);
Tuple normalize(Tuple tup);
float dot(Tuple A, Tuple B);
Vector cross(Vector A, Vector B);
int is_equal_tup(Tuple A, Tuple B);

#ifndef MATRIX_SEEN
#define MATRIX_SEEN
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define IDENTITY_3 arr_to_M3((float[]){1,0,0,0,1,0,0,0,1})
#include "tuple.c"
#define MAXN 300

typedef struct Matrix_s{
  float index[3][3];
}M3;


int get_matrix_prod_element(M3 *matrix_a, M3 *matrix_b, int result_row, int result_column){
  int prod=0;
  for(int i=0;i<3;i++){
    prod = prod + matrix_a->index[result_row][i] * matrix_b->index[i][result_column];
  }
  return prod;
}
M3 M3_prod(M3 *matrix_a, M3 *matrix_b){
  M3 matrix_out;

  for (int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      matrix_out.index[i][j] = get_matrix_prod_element(matrix_a, matrix_b, i, j);
    }
  }
  return matrix_out;
}
void print_matrix(M3 *matrix){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      printf("%f\t",matrix->index[i][j]);
    }
    printf("\n");
  }
}
M3 d2_arr_to_M3(float arr[3][3]){
  M3 out;
  memcpy(out.index, arr, 9*4);
  return out;
}
M3 arr_to_M3(float *arr){
  M3 out;
  memcpy(out.index, arr, 9*4);
  return out;
}

M3 scale_M3(M3 *matrix, float scalar){
  float arr[9];
  for(int i=0;i<9;i++){
    arr[i] = scalar * matrix->index[i/3][i%3];
  }
  M3 out = arr_to_M3(arr);
  return out;
}
M3 transpose_M3(M3 *matrix){
  float arr_trans[3][3];
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      arr_trans[i][j] = matrix->index[j][i];
    }
  }
  M3 out = arr_to_M3((float *)arr_trans);
  return out;
}
float det_M3(M3 *m){
  float aterm = m->index[0][0] * ((m->index[1][1] * m->index[2][2])-(m->index[1][2] * m->index[2][1]));
  float bterm = m->index[0][1] * ((m->index[1][0] * m->index[2][2])-(m->index[1][2] * m->index[2][0]));
  float cterm = m->index[0][2] * ((m->index[1][0] * m->index[2][1])-(m->index[1][1] * m->index[2][0]));
  return aterm - bterm + cterm;
}
float cofactor_M3(M3 *matrix, int row, int column){
  float sub_matrix[2][2];
  int sub_row=0;
  int sub_column=0;
  for(int i=0;i<3;i++){
    sub_column=0;
    if(i != row){
      for(int j=0;j<3;j++){
        if(j!=column){
          sub_matrix[sub_row][sub_column]=matrix->index[i][j];
          sub_column++;
        }
      }
      sub_row++;
    }
  }
  float cofactor = (sub_matrix[0][0] * sub_matrix[1][1]) - (sub_matrix[0][1] * sub_matrix[1][0]);
  return cofactor;
}
M3 inverse_M3(M3 *matrix){
  M3 out;
  if(det_M3(matrix) == 0){
    printf("failed: no inverse for matrix\n");
    return out;
  }
  float det = det_M3(matrix);
  int sign = 1;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      float cofactor = cofactor_M3(matrix,i,j);
      out.index[j][i] = sign * cofactor/det;
      sign = sign * -1;
    }
  }
  return out;
}
Tuple mvprod(M3 *matrix, Tuple *v){
  Tuple out;
  float new_vec[3];
  for(int i=0;i<3;i++){
    float new_val=0;
    new_val+=matrix->index[i][0]*v->x;
    new_val+=matrix->index[i][1]*v->y;
    new_val+=matrix->index[i][2]*v->z;
    new_vec[i]=new_val;
  }
  Tuple new_vec_out = new_Tuple(new_vec[0],new_vec[1],new_vec[2]);
  return new_vec_out;
}

M3 get_scale(float a,float b,float c){
  float arr[16] = {a,0,0,0,b,0,0,0,c};
  M3 out = arr_to_M3(arr);
  return out;
}

M3 get_x_rotation(float a){
  float arr[] = {1,0,0,0,cos(a),-sin(a),0,sin(a),cos(a)};
  M3 out = arr_to_M3(arr);
  return out;
}
M3 get_y_rotation(float b){
  float arr[] = {cos(b),0,sin(b),0,1,0,-sin(b),0,cos(b)};
  M3 out = arr_to_M3(arr);
  return out;
}
M3 get_z_rotation(float c){
  float arr[] = {cos(c),-sin(c),0,sin(c),cos(c),0,0,0,1};
  M3 out = arr_to_M3(arr);
  return out;
}
M3 get_rotation(float a, float b, float c){
  M3 A = get_x_rotation(a);
  M3 B = get_y_rotation(b);
  M3 C = get_z_rotation(c);
  M3 AB = M3_prod(&A,&B);
  M3 ABC = M3_prod(&AB, &C);
  return ABC;
}
M3 get_shear(float xy,float xz, float yx, float yz, float zx, float zy){
  float arr[] = {1,xy,xz,yx,1,yz,zx,zy,1};
  M3 out = arr_to_M3(arr);
  return out;
}
#endif

#ifndef MATRIX_SEEN
#define MATRIX_SEEN
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define IDENTITY_4 arr_to_M({1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1});
#include "tuple.c"
#define MAXN 300

typedef struct M4_s{
  size_t R, C;
  float index[4][4];
} M4;


int get_matrix_prod_element(M4 matrix_a, M4 matrix_b, int result_row, int result_column){
  int prod=0;
  for(int i=0;i<matrix_a.C;i++){
    prod = prod + matrix_a.index[result_row][i] * matrix_b.index[i][result_column];
    //printf("%d * %d\n",matrix_a.index[result_row][i], matrix_b.index[i][result_column]);
  }
  return prod;
}
M4 M4_prod(M4 matrix_a, M4 matrix_b){
  M4 matrix_out;
  //confirm that dimensions are ok
  if(matrix_a.C != matrix_b.R){
    matrix_out.R=0;
    matrix_out.C=0;
    printf("incompatible sizes\n");
    return matrix_out;
  }

  matrix_out.R = matrix_a.R;
  matrix_out.C = matrix_b.C;

  for (int i=0;i<matrix_out.R;i++){
    for(int j=0;j<matrix_out.C;j++){
      matrix_out.index[i][j] = get_matrix_prod_element(matrix_a, matrix_b, i, j);
    }
  }
  return matrix_out;
}
void print_matrix(M4 matrix){
  for(int i=0;i<matrix.R;i++){
    for(int j=0;j<matrix.C;j++){
      printf("%f\t",matrix.index[i][j]);
    }
    printf("\n");
  }
}
M4 d2_arr_to_M4(float arr[4][4]){
  M4 out;
  out.R=4;
  out.C=4;
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        out.index[i][j] = arr[i][j];
    }
  }
  return out;
}

M4 arr_to_M(float *arr, int N){
  M4 out;
  out.R=N;
  out.C=N;
  for(int i=0;i<N*N;i++){
        out.index[i/N][i%N] = arr[i];
  }
  return out;
}
M4 scale_M4(M4 matrix, float scalar){
  float arr[16];
  for(int i=0;i<16;i++){
    arr[i] = scalar * matrix.index[i/4][i%4];
  }
  M4 out = arr_to_M(arr,4);
  return out;
}
M4 transpose_M4(M4 matrix){
  int R = matrix.R;
  int C = matrix.C;
  float arr_trans[R][C];
  for(int i=0;i<R;i++){
    for(int j=0;j<C;j++){
      arr_trans[i][j] = matrix.index[j][i];
    }
  }
  M4 out = arr_to_M(*arr_trans, R);
  return out;
}
float det_M4(M4 matrix){
  int determinant=0;
  int size = matrix.C;
  if(size == 2){
    determinant= (matrix.index[0][0] * matrix.index[1][1]) - (matrix.index[1][0] * matrix.index[0][1]);
    return determinant;
  }
  for(int i=0;i<size;i++){
    int term_sign = (i%2==0 ? 1 : -1);
    float scalar = matrix.index[0][i] *term_sign;
    M4 sub_matrix;
    sub_matrix.C = size-1;
    for(int j=1;j<size;j++){
      int sub_matrix_column=0;
      for(int k=0;k<size;k++){
        if(k!=i){
          sub_matrix.index[j-1][sub_matrix_column] = matrix.index[j][k];
          sub_matrix_column++;
        }
      }
    }
    determinant += scalar * det_M4(sub_matrix);
  }
  return determinant;
}
float cofactor_M4(M4 matrix, int row, int column){
  M4 sub_matrix;
  sub_matrix.R = matrix.R-1;
  sub_matrix.C = matrix.C-1;
  int sub_row=0;
  int sub_column=0;
  for(int i=0;i<matrix.R;i++){
    sub_column=0;
    if(i != row){
      for(int j=0;j<matrix.C;j++){
        if(j!=column){
          sub_matrix.index[sub_row][sub_column]=matrix.index[i][j];
          sub_column++;
        }
      }
      sub_row++;
    }
  }
  return det_M4(sub_matrix);
}
M4 inverse_M4(M4 matrix){
  M4 out;
  if(det_M4(matrix) == 0){
    printf("failed: no inverse for matrix\n");
    out.R=0;
    out.C=0;
    return out;
  }
  out.R = matrix.R;
  out.C = matrix.C;
  float det = det_M4(matrix);
  for(int i=0;i<matrix.R;i++){
    for(int j=0;j<matrix.C;j++){
      float cofactor = cofactor_M4(matrix,i,j);
      out.index[j][i] = cofactor/det;
    }
  }
  return out;
}
Tuple mvprod(M4 matrix, Tuple v){
  Tuple out;
  if((matrix.R!=matrix.C) || (matrix.R!=4)){
    printf("mvprod called on wrong size matrix (%d,%d)",matrix.R,matrix.C);
    return out;
  }
  float old_vec[4] = {v.x,v.y,v.z,v.w};
  float new_vec[4];
  for(int i=0;i<4;i++){
    float new_val=0;
    for(int j=0;j<4;j++){
      new_val+=matrix.index[i][j]*old_vec[i];
    }
    new_vec[i]=new_val;
  }
  Tuple new_vec_out = {new_vec[0],new_vec[1],new_vec[2],new_vec[3]};
  return new_vec_out;
}

M4 get_scale(float a,float b,float c){
  float arr[16] = {1,0,0,0,0,b,0,0,0,0,c,0,0,0,0,1};
  M4 out = arr_to_M(arr,4);
  return out;
}
M4 get_translation(float a, float b, float c){
  float arr[] = {1,0,0,a,0,1,0,b,0,0,1,c,0,0,0,1};
  M4 out = arr_to_M(arr,4);
  return out;
}

M4 get_x_rotation(float a){
  float arr[] = {1,0,0,0,0,cos(a),-sin(a),0,0,sin(a),cos(a),0,0,0,0,1};
  M4 out = arr_to_M(arr,4);
  return out;
}
M4 get_y_rotation(float b){
  float arr[] = {cos(b),0,sin(b),0,0,1,0,0,-sin(b),0,cos(b),0,0,0,0,1};
  M4 out = arr_to_M(arr,4);
  return out;
}
M4 get_z_rotation(float c){
  float arr[] = {cos(c),-sin(c),0,0,sin(c),cos(c),0,0,0,0,1,0,0,0,0,1};
  M4 out = arr_to_M(arr,4);
  return out;
}
M4 get_rotation(float a, float b, float c){
  M4 A = get_x_rotation(a);
  M4 B = get_y_rotation(b);
  M4 C = get_z_rotation(c);
  M4 AB = M4_prod(A,B);
  M4 ABC = M4_prod(AB, C);
  return ABC;
}
M4 get_shear(float xy,float xz, float yx, float yz, float zx, float zy){
  float arr[] = {1,xy,xz,0,yx,1,yz,0,zx,zy,1,0,0,0,0,1};
  M4 out = arr_to_M(arr,4);
  return out;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#define MAXN 300

typedef struct{
  size_t R, C;
  float *index;
} Matrix;

int get_matrix_prod_element(M4 matrix_a, M4 matrix_b, int result_row, int result_column);
M4 multiply_matrices(M4 matrix_a, M4 matrix_b);
void print_matrix(M4 matrix);

void free_matrix(Matrix matrix){
  free(matrix.index);
}

float get_matrix_array_prod_element(int A_rows, int A_columns, int B_rows, int B_columns, float A[A_rows][A_columns], float B[B_rows][B_columns], int result_row, int result_column){
  float prod=0;
  for(int i=0;i<A_columns;i++){
    prod = prod + A[result_row][i] * B[i][result_column];
    //printf("%d * %d\n",matrix_a.index[result_row][i], matrix_b.index[i][result_column]);
  }
  return prod;
}

Matrix matrix_product(M4 matrix_a, M4 matrix_b){
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
      matrix_out.index[i][j] = get_matrix_prod_element(matrix_a.R, matrix_a.C, matrix_b.R, matrix_b.C, matrix_a.index, matrix_b.index i, j);
    }
  }
  return matrix_out;
}
void print_matrix(M4 matrix){
  for(int i=0;i<matrix.R;i++){
    for(int j=0;j<matrix.C;j++){
      printf("%f\t",matrix.index[i*C + j]);
    }
    printf("\n");
  }
}
Matrix arr_to_matrix(int rows, int columns, float arr[rows][colums]){
  M4 out;
  out.R = rows;
  out.C = colums;
  out.index = arr;
  return out;
}

Matrix scale_matrix(Matrix matrix, float scalar){
  int matrix_size = matrix.R * matrix.C;
  float *arr = malloc(sizeof(float) * matrix_size);
  for(int i=0;i<matrix_size;i++){
    arr[i] = scalar * matrix.index[i];
  }
  Matrix out = arr_to_matrix(arr);
  return out;
}

Matrix transpose_matrix(M4 matrix){
  int matrix_size = matrix.R * matrix.C;
  float * arr_trans = malloc(sizeof(float) * matrix_size);
  for(int i=0;i<matrix_size;i++){
    arr_trans[i] = matrix.index[i%matrix.C][i/matrix.R];
  }
  Matrix out = d2_arr_to_M4(arr_trans);
  return out;
}
float * transpose_matrix_array(int rows, int columns, int array[rows][columns]){
  float array_trans[rows][columns];
  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      array_trans[i][j] = matrix.index[j][i];
    }
  }
}
float det_M4(){

}
float det_arr(int size, float arr[][size]){
  if(size == 2){
    return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
  }
  else{
    float ** submatrix = malloc(sizeof(float) * (size-1)*(size-1));
    submatrix
  }
}
Tuple mvprod(M4 matrix, Tuple v){
  Tuple out;
  if(!(matrix.R==matrix.C==4)){
    printf("mvprod called on wrong size matrix");
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

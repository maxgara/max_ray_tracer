#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRIALS 10000

typedef struct M3_s{
  size_t R, C;
  float index[3][3];
} M3;

typedef struct Matrix_s{
  size_t R, C;
  float **index;
} Matrix;

typedef struct Matrix_void_s{
  size_t R, C;
  void *index;
} Matrix_v;

void fill_M3s(M3 arr[], int N){
  for(int i=0;i<N;i++){
    M3 new_M3;
    for(int j=0;j<3;j++){
      for(int k=0;k<3;k++){
          new_M3.index[j][k] = i;
      }
    }
    arr[i] = new_M3;
  }
}

void fill_matrices(Matrix arr[], int N){
  for(int i=0;i<N;i++){
    Matrix new_matrix;
    new_matrix.index=malloc(sizeof(int *) * 3);
    for(int j=0;j<3;j++){
      new_matrix.index[j]=malloc(sizeof(int) * 3);
      for(int k=0;k<3;k++){
          new_matrix.index[j][k] = i;
      }
    }
    arr[i] = new_matrix;
  }
}

void fill_matrices_v(Matrix_v *arr, int N){
  float *index_block = malloc(sizeof(float) * 9 * N);
  for(int i=0;i<N;i++){
    Matrix_v new_matrix;
    new_matrix.index = (index_block + 9*i);
    for(int j=0;j<9;j++){
      ((float*)new_matrix.index)[j]=i;
    }
    arr[i] = new_matrix;
  }
}

void print_M3(M3 my_m3){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      printf("%f\t",my_m3.index[i][j]);
    }
    printf("\n");
  }
}

void print_matrix(Matrix my_matrix){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      printf("%f\t",my_matrix.index[i][j]);
    }
    printf("\n");
  }
}

int main(){
  clock_t begin;
  clock_t end;
  unsigned clocks_spent;
begin = clock();
M3 arr_M3s[TRIALS];
fill_M3s(arr_M3s,TRIALS);
//print_M3(arr_M3s[1]);
end = clock();
clocks_spent = (unsigned) end - begin;
printf("%d M3 clocks:%d\n",TRIALS,clocks_spent);
// // //
begin = clock();
Matrix_v arr_matrices_v[TRIALS];
Matrix_v test;
fill_matrices_v(arr_matrices_v, TRIALS);
end = clock();
clocks_spent = (unsigned) end - begin;
printf("%d void * Matrix clocks:%d\n",TRIALS,clocks_spent);

begin = clock();
Matrix arr_matrices[TRIALS];
fill_matrices(arr_matrices,TRIALS);
end = clock();
clocks_spent = (unsigned) end - begin;
printf("%d Matrix clocks:%d\n",TRIALS,clocks_spent);


}

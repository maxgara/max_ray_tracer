#include "matrix_new.c"

int test_matrix(M3 *matrix){
  printf("matrix:\n");
  print_matrix(matrix);
  printf("vector:\n");
  Tuple v = new_Tuple(1,2,3);
  print_tup(v);
  printf("mv prod:\n");
  print_tup(mvprod(matrix,&v));
  float det = det_M3(matrix);
  printf("\ndeterminant:%f\n",det);
  printf("transpose\n");
  M3 transpose = transpose_M3(matrix);
  print_matrix(&transpose);
  printf("\ninverse:\n");
  M3 matrix_inverse = inverse_M3(matrix);
  print_matrix(&matrix_inverse);
  printf("matrix prod test:\nmatrix A:\n");
  print_matrix(matrix);
  float B_arr[16] = {1,0,0,0,2,0,0,0,3};
  M3 B_matrix = arr_to_M3(B_arr);
  printf("\nmatrix B:\n");
  print_matrix(&B_matrix);
  printf("\nprod:\n");
  M3 prod = M3_prod(matrix,&B_matrix);
  print_matrix(&prod);
  printf("\nscale test:\nscale matrix:\n");
  M3 scale = get_scale(1,2,3);
  print_matrix(&scale);
  printf("\nvector:\n");
  print_tup(v);
  printf("\nproduct:\n");
  Tuple v_scaled = mvprod(&scale,&v);
  print_tup(v_scaled);


}
int main(){
  // float arr[16] = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
  // M3 C = arr_to_M4(arr);
  // // // print_matrix(C);
  // // // printf("\n");
  // // M4 Ct = transpose_M4(C);
  // // //print_matrix(Ct);
  // // float test_arr[] = {-2,-8,3,5,-3,1,7,3,1,2,-9,6,-6,7,7,-9};
  // // M4 test = arr_to_M4(test_arr);
  // // // test.R=2;
  // // // test.C=2;
  // // // test.index[0][0]=1;
  // // // test.index[0][1]=0;
  // // // test.index[1][0]=0;
  // // // test.index[1][1]=1;
  // // print_matrix(test);
  // // printf("determinant:%f\n",det_M4(test));
  // float arr3[9] = {1,5,1,1,2,3,1,3,3};
  // M4 matrix3 = arr_to_M(arr3,3);
  // print_matrix(matrix3);
  // // printf("transpose:\n");
  // M4 matrix3t = transpose_M4(matrix3);
  // print_matrix(matrix3t);
  // printf("cofactor(0,0):%f\n",cofactor_M4(matrix3,0,0));

  float arr3[] = {1,0,0,0,1,0,0,0,2};
  float arr6[] = {1,2,3,4,5,6,7,8,1};
  float arr4[] = {8,-5,9,2,7,5,6,1,-6,0,9,6,-3,0,-9,-4};
  float arr5[] = {1,0,0,1,0,2,0,0,0,0,3,0,0,0,0,4};
  M3 matrix3 = arr_to_M3(arr3);
  M3 matrix4 = arr_to_M3(arr4);
  M3 matrix5 = arr_to_M3(arr3);
  M3 matrix6 = arr_to_M3(arr6);


  test_matrix(&matrix6);
}

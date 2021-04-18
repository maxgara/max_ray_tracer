#include "M4.c"

int main(){
  // float arr[16] = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
  // M4 C = arr_to_M4(arr);
  // print_matrix(C);
  float arr[2][2] = {1,2,3,4};
  float d = det_arr(2,arr);
  printf("det:%f\n",d);
}

#include <stdio.h>

int main(){
  int arr[3][3];
  printf("arr:\t\t%p\n",arr);
  printf("arr[0]:\t\t%p\n",arr[0]);
  printf("&(arr[0][0]):\t%p\n",&(arr[0][0]));
}

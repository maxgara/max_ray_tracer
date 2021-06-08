#include <stdio.h>
#include <string.h>

int main(){
  int arr[3][3];
  printf("arr:\t\t%p\n",arr);
  printf("arr[0]:\t\t%p\n",arr[0]);
  printf("&(arr[0][0]):\t%p\n",&(arr[0][0]));
  int newarr[] = {1,2,3,4,5,6,7,8,9,10};
  memcpy(arr, newarr, 5*4);
  for(int i=0;i<9;i++){
    printf("%d\n",arr[i/3][i%3]);
  }
}

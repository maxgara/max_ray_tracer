#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
  FILE * fp;
  fp = fopen("C_in_a_nutshell.txt","r");
  printf("fp:%p\n",fp);
  char s[1000];
  while(fscanf(fp,"%s", s)!=EOF){
    printf("%s\n",s); 
  }
  fclose(fp);
  /*size_t MBs = (argc>1? atoi(argv[1]) : 1);
  printf("malloc %ld MBs\n",MBs);
  char * ptr;
  ptr = malloc(1000000 * MBs);
  printf("result:%p\n",ptr);
  char str[100];
  fgets(str,10,stdin);
  for(unsigned i=0;i<1000000 * MBs;i++){
    ptr[i] = 'a';
  }
  printf("reading memory now\n");
  for(unsigned i=0;i<1000000 * MBs;i++){
    if(ptr[i]=='b'){
      return 1;
    }
  }
  printf("done reading\n");
  free(ptr);*/
}

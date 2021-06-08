#include "color.c"
#include "render_sdl.c"

int main(){
  Canvas can = {CANVAS_X_SIZE,CANVAS_Y_SIZE};
  for(int i=0;i<CANVAS_X_SIZE;i++){
    for(int j=0;j<CANVAS_Y_SIZE;j++){
      Color color = new_Color(0,i,j,j-i);
      can.pixels[i][j] = color;
    }
  }
  FILE * fp;
  fp=fopen("ppm_out.ppm","w+");
  render_sdl(&can, CANVAS_X_SIZE, CANVAS_Y_SIZE);
  // canvas_to_ppm(can,fp);
  fclose(fp);
  printf("testing!\n");
}

#include "tuple.h"
#include <stdio.h>
#define Color Tuple
#define CANVAS_X_SIZE 500
#define CANVAS_Y_SIZE 500
typedef struct{
  int x_size;
  int y_size;
  Color pixels[CANVAS_X_SIZE][CANVAS_Y_SIZE];
}Canvas;

Color new_Color(int r, int g, int b){
  Color out;
  out.r = r;
  out.g = g;
  out.b = b;

  return out;
}
Color colorProd(Color a, Color b){
  Color out = new_Color(a.x*b.x, a.y*b.y, a.z*b.z);
  return out;
}
void correct_color(Color *c){
  if(c->r < 0){
    c->r=0;
  }
  else if(c->r > 255){
    c->r = 255;
  }
  if(c->g < 0){
    c->g=0;
  }
  else if(c->g > 255){
    c->g = 255;
  }
  if(c->b < 0){
    c->b=0;
  }
  else if(c->b > 255){
    c->b = 255;
  }
}
void write_pixel(Canvas *canvas, int x, int y, Color color){
  canvas->pixels[x][y] = color;
}
void canvas_to_ppm(Canvas canvas, FILE * fp){
  fprintf(fp,"P3\n%d %d\n255\n",CANVAS_X_SIZE,CANVAS_Y_SIZE);
  int line_length=0;
  for(int i=0;i<canvas.x_size;i++){
    for(int j=0;j<canvas.y_size;j++){
      Color color = canvas.pixels[i][j];
      fprintf(fp,"%d %d %d ",color.r,color.g,color.b);
      line_length = line_length + 3;
      if(line_length>=67){
        fprintf(fp,"\n");
        line_length=0;
      }
    }
  }
}

int main(){
  Canvas can = {CANVAS_X_SIZE,CANVAS_Y_SIZE};
  for(int i=0;i<CANVAS_X_SIZE;i++){
    for(int j=0;j<CANVAS_Y_SIZE;j++){
      Color color = new_Color(i,j,j-i);
      correct_color(&color);
      write_pixel(&can, i, j, color);
    }
  }
  FILE * fp;
  fp=fopen("ppm_out.ppm","w+");
  canvas_to_ppm(can,fp);
  fclose(fp);
}

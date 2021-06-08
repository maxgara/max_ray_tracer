#ifndef COLOR_FOUND
#define COLOR_FOUND
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define Color uint32_t
#define CANVAS_X_SIZE 200
#define CANVAS_Y_SIZE 200
typedef struct{
  int x_size;
  int y_size;
  Color pixels[CANVAS_X_SIZE][CANVAS_Y_SIZE];
}Canvas;
//colors are stored in format SDL_PIXELFORMAT_ARGB8888
Color new_Color(int a, int r, int g, int b){
  Color out = 0;
  out += (a%256)<<24;
  out += (r%256)<<16;
  out += (g%256)<<8;
  out += b%256;
  return out;
}
Color colorProd(Color a, Color b){
  //no idea why this function exists
  int alpha = (a>>24) * (b>>24);
  int red = (a>>16) * (b>>16);
  int green = (a>>8) * (b>>8);
  int blue = a*b;
  Color out = new_Color(alpha,red, green, blue);
  return out;
}

void canvas_to_ppm(Canvas canvas, FILE * fp){
  fprintf(fp,"P3\n%d %d\n255\n",CANVAS_X_SIZE,CANVAS_Y_SIZE);
  int line_length=0;
  for(int i=0;i<canvas.x_size;i++){
    for(int j=0;j<canvas.y_size;j++){
      Color color = canvas.pixels[i][j];
      fprintf(fp,"%d %d %d ",(color>>16)%256, (color>>8)%256, color%256);
      line_length = line_length + 3;
      if(line_length>=67){
        fprintf(fp,"\n");
        line_length=0;
      }
    }
  }
}
#endif

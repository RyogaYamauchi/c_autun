#include<stdio.h>
#include<handy.h>
int changeColor(int,int);
int Grid();
double position[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

int main(){
  double x,y;
  int tileX,tileY;
  int i,j;
  hgevent *event;
  HgOpen(400,400);
  HgSetWidth(1.0);
  HgSetColor(HG_BLACK);

  Grid();    //グリッド線を描画

  HgSetEventMask(HG_MOUSE_DOWN);
  while(1){
    event = HgEvent();
    if(event->type == HG_MOUSE_DOWN){
      x=event->x;
      y=event->y;
      changeColor(x/100,y/100);  //誤差をなくす（float→int）
    }
  }
  return 0;
}

/**　タイルクリック時、色の変更 **/
int changeColor(int x,int y){
  printf("{x,y}={%d,%d}\n",x,y);

  //色が白の時（塗ってない時）
  if(position[x][y]==0){
    HgSetFillColor(HG_BLACK);
    HgBoxFill(x*100,y*100,100,100,1);
    position[x][y] = 1; //色を黒にしたよ〜
  //色が黒の時（塗ってる時）
  }else{
    HgSetFillColor(HG_WHITE);
    HgBoxFill(x*100,y*100,100,100,1);
    position[x][y] = 0;  //色を白にしたよ〜
  }
  return 0;
}

/** 線を描画 **/
int Grid(){
  int i=0;
  for(i=1;i<4;i++){
    HgLine(100*i,0,100*i,400); //たてのライン
    HgLine(0,100*i,400,100*i); //横のライン
  }
  return 0;
}

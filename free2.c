#include<stdio.h>
#include<math.h>
#include<handy.h>
#define WindowSize 500
#define center 250

/**  グローバル変数  **/
float basicAxis = WindowSize/2;
double x[8] = {-30.0, 30.0, 30.0, -30.0,-30.0, 30.0, 30.0, -30.0};
double y[8] = { -40.0, -40.0, 40.0, 40.0,0.0, 0.0, 80.0, 80.0};
int height = 100;      //高さ
double temp[4] = {};
int divide = 8;

/** プロトタイプ宣言 **/
int Spin(void);

/** メイン処理 **/
int main(){
  HgOpen(WindowSize,WindowSize);
  int i =0;              //カウンタ
  int j = 0;

  /** メイン処理 **/
  while(1){
    HgClear();

    Spin(); //計算処理

    /** 描画処理 **/
    for(i=0; i<3; i++) {
      HgLine(x[i] + basicAxis , y[i] + basicAxis , x[i+1] + basicAxis , y[i+1] + basicAxis);
      HgLine(basicAxis , 120.0 + basicAxis , x[i+1] + basicAxis , y[i+1] + basicAxis);
    }
    HgLine(x[0] + basicAxis , y[0] + basicAxis , x[3] + basicAxis , y[3] + basicAxis);
    HgLine(basicAxis , 120.0 + basicAxis , x[0] + basicAxis , y[0] + basicAxis);



    /**基軸の描画**/
    for(i=0;i<500;i+=50){
      HgLine(0,i,500,i);  //X軸
      HgLine(i,0,i,500);      //Y軸
    }
    HgSleep(0.1);    //描画速度
    //HgGetChar();

  }
}

int Spin(){
  int i = 0;
    for(i=0; i<4; i++) {
      temp[i] = x[i];
      x[i] =  x[i]  * cos(M_PI/divide) - y[i] * sin(M_PI/divide);
      y[i] =temp[i] * sin(M_PI/divide) + y[i] * cos(M_PI/divide);
      printf("X[%d] : %f\n",i,x[i]);
      printf("Y[%d] : %f\n",i,y[i]);
    }
return 0;
}

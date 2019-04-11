#include<stdio.h>
#include<math.h>
#include<handy.h>
#define WindowSize 500
#define center 250

/**  グローバル変数  **/
float basicAxis = WindowSize/2;
float X[8] = {-25,20,30,40,10,20,30,40};       //各X軸情報を格納する(描画処理)
float Y[8] = {50,60,70,80,50,60,70,80};       //各Y軸情報を格納する(描画処理)
float angle = 30;       //角度（変動）　　　 (回転)
int radX = 100;        //X軸半径
int radY = 50;         //Y軸半径
int height = 100;      //高さ
int originX = 250;     //固定のX軸（原点の設定）
int originY = 150;     //固定のY軸（原点の設定）
int divide = 4;
double tempX[8] = {};
double tempY[8] = {};

/** プロトタイプ宣言 **/
int Spin(void);

/** メイン処理 **/
int main(){
  HgOpen(WindowSize,WindowSize);
  int i =0;              //カウンタ
  int j = 0;

  /** メイン処理 **/
  while(1){

    Spin();

    /** オブジェクト描画処理 **/
    for(i = 0;i < 7;i++){
      if(i != 3)HgLine(X[i] + 250,Y[i]+ 250,X[i+1]+ 250,Y[i+1]+ 250);              //下,上の1,2,3,1,2,3を描画
      if(i == 0 || i ==4) HgLine(X[i+3]+ 250,Y[i+3]+ 250,X[i]+ 250,Y[i]+ 250);    //下,上の4,4を描画
      if(i < 4)     HgLine(X[i]+ 250,Y[i]+ 250,X[i+4]+ 250,Y[i+4]+ 250);          //縦を描画
    }

    HgSleep(0.1);    //描画速度
    HgClear();

    /**基軸の描画**/
    for(i=0;i<500;i+=50){
      HgLine(0,i,500,i);  //X軸
      HgLine(i,0,i,500);      //Y軸
    }

    HgGetChar();
  }
  return 0;
}

int Spin(){
  int i=0;
  /** X軸Y軸の計算 **/
  for(i = 0;i<4;i++){
    tempX[i] = X[i];
    tempY[i] = X[i];
    X[i] = basicAxis +  X[i] + cos(M_PI/divide) - Y[i] * sin(M_PI/divide);                      //底辺X軸
    Y[i] = basicAxis + Y[i] + sin(M_PI/divide) + Y[i] * cos(M_PI/divide);                      //底辺Y軸
    X[i+4] = basicAxis + tempX[i] + cos(M_PI/divide) - tempY[i] * sin(M_PI/divide);                    //上辺X軸
    Y[i+4] = basicAxis + tempY[i] + (height) + sin(M_PI/divide) + tempY[i] * cos(M_PI/divide);  //底辺Y軸
    printf("X[%d] : %f\n",i,X[i]);
    printf("Y[%d] : %f\n",i,Y[i]);

  }
  angle += 0.1;    //頂点の移動に使う角度
  printf("in a Spin\n");
  return 0;
}

#include <stdio.h>
#include <math.h>
#include <handy.h>
#include<time.h>
#include<stdlib.h>

#define terrianSize 54
#define WindowWidth 1080
#define WindowHeight 720
#define charctorSize 10
#define magnification 20  //倍率

//プロトタイプ宣言
int getRoom();  //部屋の情報を取得
int grid();     //仮のグリッド線を描画
int getRoot();  //部屋と部屋の道を取得
int getRootRight(int,int);  //部屋と部屋の道を取得（横）
int getRootUp(int,int);     //部屋と部屋の道を取得（縦)

//構造体宣言
typedef struct charctor{
  double x;
  double y;
  int hp;
}charctor;

//グローバル変数
int roomX[9]={};  //部屋の大きさX
int roomY[9]={};  //部屋の大きさY
int iniRoomX[9]={}; //部屋の初期いちを少しずらすX
int iniRoomY[9]={}; //部屋の初期いちを少しずらすY
int layerID;           //レイヤーの番号

int main(void){
  doubleLayer layers;    //ダブルバッファ用のデータ
  int i,j;
  int terrian[terrianSize][terrianSize];  //地形情報
  int windowID;          //ウィンドウの番号
  charctor player = {1.5,1.5,10};

  windowID = HgOpen(WindowWidth,WindowHeight);                  //レイヤーをオープン
  layers = HgWAddDoubleLayer(windowID);                      //ダブルバッファを作る
  HgWSetEventMask(layerID,HG_KEY_DOWN);   //ドラッグとクリックを検出
  grid();  //仮のグリッド線を描画

  while(1){  //メイン処理
    layerID = HgLSwitch(&layers);            //表示レイヤを入れ替える
    HgLClear(layerID);                       //描画用レイヤを消去する
    hgevent *event = HgEvent();   //イベントを取得
    getRoom();                               //部屋を取得
    getRoot();                               //道を取得
    if (event->type == HG_KEY_DOWN) {        //イベント判定
      switch (event->ch) {
        case 119: player.y+=1;               //w
                  break;
        case 97:player.x-=1;                 //a
                  break;
        case 115:player.y-=1;                //s
                  break;
        case 100:player.x+=1;                //d
                  break;
        defalut: break;
        }
    }
    HgWSetFillColor(layerID,HG_WHITE);
    HgWCircleFill(layerID,player.x*magnification,player.y*magnification,charctorSize,1);  //プレイヤーを表示
  }
}

//部屋を取得
int getRoom(){
  int i,j,width,height,iniWid,iniHei,temp;
  temp = 0;
  HgWSetFillColor(layerID,HG_GREEN);
  srand(time(NULL));
  for(i=0;i<3;i++){ //部屋の大きさを乱数で設定
    for(j=0;j<3;j++){ //部屋の大きさを乱数で設定
      width = rand()%4+8;  //8から12まで部屋の大きさを決定するX
      height = rand()%2+8;  //8から12まで部屋の大きさを決定するY
      iniHei = rand()%2+1;  //1から２まで部屋の初期いちをずらす
      iniWid = rand()%2+3;  //３から４まで部屋の初期いちをずらす
      HgWBoxFill(layerID,(j*(WindowWidth/3))+(iniWid*magnification), //Xの初期値
      (i*(WindowHeight/3))+(iniHei*magnification),                   //yの初期値
      (width*magnification),(height*magnification),1);               //widthとheightの値
      roomX[temp]=width;        //それぞれの部屋のXの大きさを保持
      roomY[temp]=height;       //それぞれの部屋のYの大きさを保持
      iniRoomX[temp] = iniWid;  //それぞれの部屋のずらした初期いちXの大きさを保持
      iniRoomY[temp] = iniHei;  //それぞれの部屋のずらした初期いちYの大きさを保持
      temp++;
      //printf("部屋%dの大きさは width:%d, height:%d\n",temp,width,height);
    }
  }
  return 0;
}

//道を取得
int getRoot(){
  int i;
  getRootRight(0,1);
  getRootRight(1,2);
  getRootRight(3,4);
  getRootRight(4,5);
  getRootRight(6,7);
  getRootRight(7,8);
  getRootUp(0,3);
  getRootUp(1,4);
  getRootUp(2,5);
  getRootUp(3,6);
  getRootUp(4,7);
  getRootUp(5,8);
  return 0;
}

//横の道をつなぐ
int getRootRight(int first,int second){  //first:左側,second:右側
  int i,rootFirst,rootSecond,height,leftX,leftY,leftWidth,rightX,rightY,rightWidth,rootToRootX;
  HgWSetFillColor(layerID,HG_BLUE);

  //乱数発生(部屋で道が繋げられるところにflag)
  srand(time(NULL));
  rootFirst = rand()%(roomY[first]-1)+iniRoomY[first];
  rootSecond = rand()%(roomY[second]-1)+iniRoomY[second];
  height  = 1*magnification;
  rootToRootX = 16*magnification;

  leftX       = (iniRoomX[first] + roomX[first])*magnification;  //Xの初期値(誤差と大きさを足した)
  leftY       = (1+rootFirst)*magnification;  //Yの初期値(初期値の１と乱数発生の値を足した)
  leftWidth   = (20-(3+iniRoomX[first]+roomX[first]))*magnification;//(全体からXの初期値を引いた)

  rightX      = 16*magnification;           //Xの基準点(基準点から出す値)
  rightY      = (rootSecond)*magnification; //Yの基準点(基本の＋１と乱数発生の値を足した)
  rightWidth  = (2+iniRoomX[second])*magnification;            //右の余分な１８と基準の３に乱数発生を足した)

  //printf("部屋%dから%dの道で、%dと%dで出たい。\n",first,second,rootFirst,rootSecond);


  if(first%2!=0) {  //1-2,4-5,7-8の時は定数たす
    leftX+=18*magnification;
    rightX+=18*magnification;
    rootToRootX += 18*magnification;
  }
  if(first==3){
    leftX-=18*magnification;
    rightX-=18*magnification;
    rootToRootX-=18*magnification;

    leftY+=12*magnification;
    rightY+=12*magnification;
    rootFirst+=12;  //道と道をつなぐ際に必要な要素
    rootSecond+=12; //上に同様
  }
  if(first==4){
    leftX+=18*magnification;
    rightX+=18*magnification;
    rootToRootX+=18*magnification;

    leftY+=12*magnification;
    rightY+=12*magnification;
    rootFirst+=12;  //道と道をつなぐ際に必要な要素、
    rootSecond+=12; //上に同様
  }
  if(first==6 || first==7){
    leftY+=24*magnification;
    rightY+=24*magnification;
    rootFirst+=24;  //道と道をつなぐ際に必要な要素、
    rootSecond+=24; //上に同様
  }
  //左から基準点までの道
  HgWBoxFill(layerID,leftX,leftY,leftWidth,height,1);
  //右から基準点までの道
  HgWBoxFill(layerID,rightX,rightY,rightWidth,height,1);

  if (rootFirst != rootSecond-1){
    if(rootFirst>rootSecond){
      HgWBoxFill(layerID,
                 rootToRootX,
                 rootSecond*magnification,
                 1*magnification,
                 abs(1+rootFirst-rootSecond)*magnification,1);
    }
    else{
      HgWBoxFill(layerID,
                 rootToRootX,
                 (1+rootFirst)*magnification,
                 1*magnification,
                 abs(rootFirst-rootSecond)*magnification,1);
    }
  }
  return 0;
}

//縦の道をつなぐ
int getRootUp(int first, int second){
  int i,rootFirst,rootSecond,height,lowX,lowY,lowHeight,highX,highY,highHeight,width,rootToRootY;
  srand(time(NULL));
  rootFirst = rand()%(roomX[first])+iniRoomX[first];  //firstの部屋のX座標方面大きさを決定,誤差も
  rootSecond = rand()%(roomX[second])+iniRoomX[second];
  height = 12*magnification;
  width = 1*magnification;
  rootToRootY = 11*magnification;

  lowX       = (rootFirst)*magnification;  //Xの初期値(誤差と大きさを足した)
  lowY       = (roomY[first] +iniRoomY[first])*magnification;  //Yの初期値(初期値の１と乱数発生の値を足した)
  lowHeight   = (15-(3+iniRoomY[first]+roomY[first]))*magnification;//(全体からXの初期値を引いた)

  highX      = (rootSecond)*magnification;           //Xの基準点(基準点から出す値)
  highY      = 11*magnification; //Yの基準点(基本の＋１と乱数発生の値を足した)
  highHeight  = (1+iniRoomY[second])*magnification;            //右の余分な１８と基準の３に乱数発生を足した)

  if(first>2) {  //1-2,4-5,7-8の時は定数たす
    lowY+=12*magnification;
    highY+=12*magnification;
    rootToRootY += 12*magnification;
  }
  if(first==1 || first==4){
    lowX+=18*magnification;
    highX+=18*magnification;
    rootFirst+=18;  //道と道をつなぐ際に必要な要素、
    rootSecond+=18; //上に同様
  }
  if(first==2 || first==5){
    lowX+=36*magnification;
    highX+=36*magnification;
    rootFirst+=36;  //道と道をつなぐ際に必要な要素、
    rootSecond+=36; //上に同様
  }

  //下から基準点までの道
  HgWSetFillColor(layerID,HG_RED);
  HgWBoxFill(layerID,lowX,lowY,width,lowHeight,1);
  //上から基準点までの道
  HgWSetFillColor(layerID,HG_GREEN);
  HgWBoxFill(layerID,highX,highY,width,highHeight,1);

  if(rootFirst==rootSecond || rootFirst+1==rootSecond || rootFirst-1==rootSecond){
    //printf("道を引く必要はありません。\n");
  }
  else{
    if(rootFirst>rootSecond){
      HgWBoxFill(layerID,
                 rootSecond*magnification,
                 rootToRootY,
                 abs(1+rootFirst-rootSecond)*magnification,
                 1*magnification,1);
    }
    else{
      HgWBoxFill(layerID,
                 (rootFirst)*magnification,
                 rootToRootY,
                 abs(rootFirst-rootSecond)*magnification,
                 1*magnification,1);
    }
  }
  return 0;
}


int grid(){ //仮のグリッド線を描画
  int i,width,temp;
  temp = WindowWidth / terrianSize;
  for(i=0;i<terrianSize;i++){
    HgWLine(layerID,width,0,width,WindowHeight);
    HgWLine(layerID,0,width,WindowWidth,width);
    width = width + temp;
  }
  return 0;
}

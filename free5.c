#include <stdio.h>
#include <math.h>
#include <handy.h>
#include<time.h>
#include<stdlib.h>

#define terrianSizeX 54     //地形の大きさX
#define terrianSizeY 36     //地形の大きさY
#define WindowWidth 1080    //画面の大きさ
#define WindowHeight 720    //画面の大きさ
#define charctorSize 10     //キャラの大きさ（自分、敵）
#define magnification 20    //倍率

//プロトタイプ宣言
int getRoom();              //部屋の情報を取得
int grid();                 //仮のグリッド線を描画
int getRoot();              //部屋と部屋の道を取得
int write();
int getRootRight(int,int);  //部屋と部屋の道を取得（横）
int getRootUp(int,int);     //部屋と部屋の道を取得（縦)

//構造体宣言
typedef struct charctor{
  double x;                 //座標
  double y;                 //座標
  int hp;                   //体力
}charctor;

//グローバル変数
int roomX[9]={};            //部屋の大きさX
int roomY[9]={};            //部屋の大きさY
int iniRoomX[9]={};         //部屋の初期いちを少しずらすX
int iniRoomY[9]={};         //部屋の初期いちを少しずらすY
int layerID;                //レイヤーの番号
int pubWriteRight[16]={};
int pubWriteUp[16]={};
int pubWriteRoom[9]={};

int main(void){
  doubleLayer layers;       //ダブルバッファ用のデータ
  int i,j;
  int terrian[terrianSizeX][terrianSizeY];    //地形情報
  int windowID;                               //ウィンドウの番号
  charctor player = {1.5,1.5,10};             //プレイヤーの初期値

  windowID = HgOpen(WindowWidth,WindowHeight);    //レイヤーをオープン
  layers = HgWAddDoubleLayer(windowID);           //ダブルバッファを作る
  HgWSetEventMask(layerID,HG_KEY_DOWN);           //ドラッグとクリックを検出
  grid();                                         //仮のグリッド線を描画

/** メイン処理 **/
  while(1){
    layerID = HgLSwitch(&layers);            //表示レイヤを入れ替える
    hgevent *event = HgEvent();              //イベントを取得
    write();
    if (event->type == HG_KEY_DOWN) {        //イベント判定
      switch (event->ch) {
        case 119: player.y+=1;               //w（前に進む)
                  break;
        case 97 :player.x-=1;                 //a(左に進む)
                  break;
        case 115:player.y-=1;                //s(下に進む)
                  break;
        case 100:player.x+=1;                //d(右に進む)
                  break;
        case 108:
                 HgLClear(layerID);                       //描画用レイヤを消去する
                 getRoom();     //l
                 getRoot();
                 break;
        case 32 :printf("攻撃を繰り出した\n");//スペースで攻撃
                 break;
        defalut: break;
        }
    }
    HgWSetFillColor(layerID,HG_WHITE);
    HgWCircleFill(layerID,player.x*magnification,player.y*magnification,charctorSize,1);  //プレイヤーを表示
  }
}

/** 部屋を取得 **/
int getRoom(){
  int i,j,width,height,iniWid,iniHei,temp;
  temp = 0;
  HgWSetFillColor(layerID,HG_GREEN);
  srand(time(NULL));
  for(i=0;i<3;i++){            //部屋の大きさを乱数で設定
    for(j=0;j<3;j++){          //部屋の大きさを乱数で設定
      width = rand()%4+8;      //8から12まで部屋の大きさを決定するX
      height = rand()%2+8;     //8から12まで部屋の大きさを決定するY
      iniHei = rand()%2+1;     //1から２まで部屋の初期いちをずらす
      iniWid = rand()%2+3;     //３から４まで部屋の初期いちをずらす
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

/** 道を取得 **/
int getRoot(){
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
  int rootFirst,rootSecond,height,leftX,leftY,leftWidth,rightX,rightY,rightWidth,rootToRootX;
  HgWSetFillColor(layerID,HG_BLUE);

  //乱数発生(部屋で道が繋げられるところにflag)
  srand(time(NULL));
  rootFirst = rand()%(roomY[first]-1)+iniRoomY[first];     //乱数
  rootSecond = rand()%(roomY[second]-1)+iniRoomY[second];  //乱数
  height  = 1;                               //幅（固定）
  rootToRootX = 16;                          //高さ（固定）

  leftX       = iniRoomX[first] + roomX[first];      //Xの初期値(誤差と大きさを足した)
  leftY       = 1+rootFirst;                         //Yの初期値(初期値の１と乱数発生の値を足した)
  leftWidth   = 20-(3+iniRoomX[first]+roomX[first]); //全体からXの初期値を引いた)

  rightX      = 16;                        //Xの基準点(基準点から出す値)
  rightY      = rootSecond;                //Yの基準点(基本の＋１と乱数発生の値を足した)
  rightWidth  = 2+iniRoomX[second];        //右の余分な１８と基準の３に乱数発生を足した)

  //printf("部屋%dから%dの道で、%dと%dで出たい。\n",first,second,rootFirst,rootSecond);

  //位置調整
  if(first%2!=0) {      //1-2,4-5,7-8の時は定数たす
    leftX+=18;
    rightX+=18;
    rootToRootX += 18;
  }
  if(first==3){
    //デバッグ
    leftX-=18;
    rightX-=18;
    rootToRootX-=18;

    leftY+=12;
    rightY+=12;
    rootFirst+=12;  //道と道をつなぐ際に必要な要素
    rootSecond+=12; //上に同様
  }
  if(first==4){
    //デバッグ
    leftX+=18;
    rightX+=18;
    rootToRootX+=18;

    leftY+=12;
    rightY+=12;
    rootFirst+=12;  //道と道をつなぐ際に必要な要素、
    rootSecond+=12; //上に同様
  }
  if(first==6 || first==7){
    leftY+=24;
    rightY+=24;
    rootFirst+=24;  //道と道をつなぐ際に必要な要素、
    rootSecond+=24; //上に同様
  }
  //左から基準点までの道
  pubWriteRight[0] = leftX*magnification;
  pubWriteRight[1] = leftY*magnification;
  pubWriteRight[2] = leftWidth*magnification;
  pubWriteRight[3] = height*magnification;
  //右から基準点までの道
  pubWriteRight[4] = rightX*magnification;
  pubWriteRight[5] = rightY*magnification;
  pubWriteRight[6] = rightWidth*magnification;
  pubWriteRight[7] = height*magnification;

  if (rootFirst != rootSecond-1){
    if(rootFirst>rootSecond){
      pubWriteRight[8] = rootToRootX*magnification;
      pubWriteRight[9] = rootSecond*magnification;
      pubWriteRight[10] = 1*magnification;
      pubWriteRight[11] = abs(1+rootFirst-rootSecond)*magnification;
    }
    else{
      pubWriteRight[12] = rootToRootX*magnification;
      pubWriteRight[13] = (1+rootFirst)*magnification;
      pubWriteRight[14] = 1*magnification;
      pubWriteRight[15] = abs(rootFirst-rootSecond)*magnification;
    }
  }
  return 0;
}

//縦の道をつなぐ
int getRootUp(int first, int second){
  int rootFirst,rootSecond,height,lowX,lowY,lowHeight,highX,highY,highHeight,width,rootToRootY;
  srand(time(NULL));
  rootFirst = rand()%(roomX[first])+iniRoomX[first];  //firstの部屋のX座標方面大きさを決定,誤差も
  rootSecond = rand()%(roomX[second])+iniRoomX[second];  //secondの部屋のX座標方面大きさを決定、誤差も含む
  height = 12;                             //基準の高さ（固定）
  width = 1;                               //道の広さ（固定）
  rootToRootY = 11;                        //道と道をつなぐ（固定）

  lowX       = (rootFirst);  //Xの初期値(誤差と大きさを足した)
  lowY       = (roomY[first] +iniRoomY[first]);  //Yの初期値(初期値の１と乱数発生の値を足した)
  lowHeight   = (15-(3+iniRoomY[first]+roomY[first]));//(全体からXの初期値を引いた)

  highX      = (rootSecond);           //Xの基準点(基準点から出す値)
  highY      = 11; //Yの基準点(基本の＋１と乱数発生の値を足した)
  highHeight  = (1+iniRoomY[second]);            //右の余分な１８と基準の３に乱数発生を足した)

  if(first>2) {  //1-2,4-5,7-8の時は定数たす
    lowY+=12;
    highY+=12;
    rootToRootY += 12;
  }
  if(first==1 || first==4){
    lowX+=18;
    highX+=18;
    rootFirst+=18;  //道と道をつなぐ際に必要な要素、
    rootSecond+=18; //上に同様
  }
  if(first==2 || first==5){
    lowX+=36;
    highX+=36;
    rootFirst+=36;  //道と道をつなぐ際に必要な要素、
    rootSecond+=36; //上に同様
  }

  //下から基準点までの道
  HgWSetFillColor(layerID,HG_RED);
  pubWriteUp[0] = lowX*magnification;
  pubWriteUp[1] = lowY*magnification;
  pubWriteUp[2] = width*magnification;
  pubWriteUp[3] = height*magnification;
  //上から基準点までの道
  HgWSetFillColor(layerID,HG_GREEN);
  pubWriteUp[4] = highX*magnification;
  pubWriteUp[5] = highY*magnification;
  pubWriteUp[6] = width*magnification;
  pubWriteUp[7] = height*magnification;

  if(rootFirst==rootSecond || rootFirst+1==rootSecond || rootFirst-1==rootSecond){
    //printf("道を引く必要はありません。\n");
  }
  else{
    if(rootFirst>rootSecond){
      pubWriteUp[8] = rootSecond*magnification;
      pubWriteUp[9] = rootToRootY*magnification;
      pubWriteUp[10] = abs(1+rootFirst-rootSecond)*magnification;
      pubWriteUp[11] = 1*magnification;
    }
    else{
      pubWriteUp[12] = rootFirst*magnification;
      pubWriteUp[13] = rootToRootY*magnification;
      pubWriteUp[14] = abs(rootFirst-rootSecond)*magnification;
      pubWriteUp[15] = 1*magnification;
    }
  }
  return 0;
}

int write(){
  int i,j;
  for(i=0;i<16;i+=4){
      HgWBoxFill(layerID,
                 pubWriteRight[i],
                 pubWriteRight[i+1],
                 pubWriteRight[i+2],
                 pubWriteRight[i+3],1);
  }
  for(i=0;i<16;i+=4){
      HgWBoxFill(layerID,
                 pubWriteUp[i],
                 pubWriteUp[i+1],
                 pubWriteUp[i+2],
                 pubWriteUp[i+3],1);
  }
  return 0;
}

int grid(){ //仮のグリッド線を描画
  int i,width,temp;
  temp = WindowWidth / terrianSizeX;
  for(i=0;i<terrianSizeX;i++){
    HgWLine(layerID,width,0,width,WindowHeight);
    HgWLine(layerID,0,width,WindowWidth,width);
    width = width + temp;
  }
  return 0;
}

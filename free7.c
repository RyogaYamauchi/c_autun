#include <stdio.h>
#include <math.h>
#include <handy.h>
#include<time.h>
#include<stdlib.h>

#define terrianSizeX 54
#define terrianSizeY 36
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
int terrian[terrianSizeX][terrianSizeY];  //地形情報
int Room[9][4] = {};
int charctorLayer;
int UILayer;


int main(void){
  doubleLayer layers;    //ダブルバッファ用のデータ
  int i,j;
  int windowID;          //ウィンドウの番号
  int UIID;
  charctor player = {3.5,3.5,10};

  windowID = HgOpen(WindowWidth,WindowHeight);                  //レイヤーをオープン
  layerID = HgWAddLayer(windowID);
  HgWSetEventMask(layerID,HG_KEY_DOWN);   //ドラッグとクリックを検出
  UIID = HgWOpen(1000,800,200,100);
  UILayer = UIID;
  getRoom();                               //部屋を取得
  getRoot();                               //道を取得
  charctorLayer = HgWAddLayer(layerID);

  while(1){  //メイン処理
    hgevent *event = HgEvent();              //イベントを取得
    //layerID = HgLSwitch(&layers);            //表示レイヤを入れ替える

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
        case 108:
                 for(i=0;i<terrianSizeX;i++){
                   for(j=0;j<terrianSizeY;j++){
                     terrian[i][j] = 0;
                   }
                 }
                 HgLClear(layerID);
                 getRoom();                               //部屋を取得
                 getRoot();                               //道を取得
                 break;
        defalut: break;
        }
    }


    for(i=terrianSizeY-1;i>=0;i--){
      for(j=0;j<terrianSizeX;j++){
        printf("%d ",terrian[j][i]);
      }
      printf("\n");
    }
    HgLClear(charctorLayer);
    HgWSetFillColor(charctorLayer,HG_WHITE);
    HgWCircleFill(charctorLayer,player.x*magnification,player.y*magnification,charctorSize,1);  //プレイヤーを表示
  }
}

//部屋を取得
int getRoom(){
  int i,j,k,l,width,height,iniWid,iniHei,temp,X,Y;
  temp = 0;
  HgWSetFillColor(layerID,HG_GREEN);
  srand(time(NULL));
  for(i=0;i<3;i++){ //部屋の大きさを乱数で設定
    for(j=0;j<3;j++){ //部屋の大きさを乱数で設定
      iniHei = rand()%2+1;  //1から２まで部屋の初期いちをずらす
      iniWid = rand()%2+3;  //３から４まで部屋の初期いちをずらす
      width = rand()%4+8;  //8から12まで部屋の大きさを決定するX
      height = rand()%2+8;  //8から12まで部屋の大きさを決定するY

      X = iniWid+(j*18);//Xの初期値
      Y = iniHei+(i*12);//yの初期値

      for(l=Y;l<Y+height;l++){  //地形情報をほじ
        for(k=X;k<X+width;k++){ //
          terrian[k][l] = 1;
        }
      }

      HgWBoxFill(layerID,(X*magnification),(Y*magnification),width*magnification,height*magnification,1);               //widthとheightの値
      roomX[temp]=width;        //それぞれの部屋のXの大きさを保持
      roomY[temp]=height;       //それぞれの部屋のYの大きさを保持
      iniRoomX[temp] = iniWid;  //それぞれの部屋のずらした初期いちXの大きさを保持
      iniRoomY[temp] = iniHei;  //それぞれの部屋のずらした初期いちYの大きさを保持
      temp++;
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
int getRootRight(int first,int second){  //first:左側,second:右側
  int i,rootFirst,rootSecond,height,leftX,leftY,leftWidth,rightX,rightY,rightWidth,rootToRootX;
  HgWSetFillColor(layerID,HG_BLUE);

  //乱数発生(部屋で道が繋げられるところにflag)
  srand(time(NULL));
  rootFirst = rand()%(roomY[first]-1)+iniRoomY[first];
  rootSecond = rand()%(roomY[second]-1)+iniRoomY[second];
  height  = 1;
  rootToRootX = 16;

  leftX       = (iniRoomX[first] + roomX[first]);  //Xの初期値(誤差と大きさを足した)
  leftY       = (1+rootFirst);  //Yの初期値(初期値の１と乱数発生の値を足した)
  leftWidth   = (20-(3+iniRoomX[first]+roomX[first]));//(全体からXの初期値を引いた)

  rightX      = 16;           //Xの基準点(基準点から出す値)
  rightY      = (rootSecond); //Yの基準点(基本の＋１と乱数発生の値を足した)
  rightWidth  = (2+iniRoomX[second]);            //右の余分な１８と基準の３に乱数発生を足した)

  //printf("部屋%dから%dの道で、%dと%dで出たい。\n",first,second,rootFirst,rootSecond);


  if(first%2!=0) {  //1-2,4-5,7-8の時は定数たす
    leftX+=18;
    rightX+=18;
    rootToRootX += 18;
  }
  if(first==3){
    leftX-=18;
    rightX-=18;
    rootToRootX-=18;

    leftY+=12;
    rightY+=12;
    rootFirst+=12;  //道と道をつなぐ際に必要な要素
    rootSecond+=12; //上に同様
  }
  if(first==4){
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
  HgWBoxFill(layerID,leftX*magnification,leftY*magnification,leftWidth*magnification,height*magnification,1);
  //右から基準点までの道
  HgWBoxFill(layerID,rightX*magnification,rightY*magnification,rightWidth*magnification,height*magnification,1);

  //printf("%dから%d width : %d, height : %d\n",leftX,leftY,leftWidth,height);
  //printf("%dから%d width : %d, height : %d\n",rightX,rightY,rightWidth,height);

  for(i=leftX;i<leftX+leftWidth;i++){
    terrian[i][leftY] = 1;
  }
  for(i=rightX;i>rightX-rightWidth;i--){
    terrian[5+i][rightY] = 1;
  }

  if (rootFirst != rootSecond){
    if(rootFirst>rootSecond){
      HgWBoxFill(layerID,
                 rootToRootX*magnification,
                 rootSecond*magnification,
                 1*magnification,
                 abs(1+rootFirst-rootSecond)*magnification,1);
      for(i=rootSecond;i<=rootSecond+abs(1+rootFirst-rootSecond);i++){
        terrian[rootToRootX][i] = 1;
      }
    }
    else{
      HgWBoxFill(layerID,
                 rootToRootX*magnification,
                 (1+rootFirst)*magnification,
                 1*magnification,
                 abs(rootFirst-rootSecond)*magnification,1);
      for(i=rootFirst+1;i<=rootFirst+abs(rootFirst-rootSecond);i++){
        terrian[rootToRootX][i] = 1;
      }
      //printf("rootFirst : %d , height : %d\n",rootFirst,i);

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
  height = 12;
  width = 1;
  rootToRootY = 11;

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
  HgWBoxFill(layerID,lowX*magnification,lowY*magnification,width*magnification,lowHeight*magnification,1);

  for(i=lowY;i<lowHeight+lowY;i++){
    terrian[lowX][i] = 1;
  }
  //上から基準点までの道
  HgWSetFillColor(layerID,HG_GREEN);
  HgWBoxFill(layerID,highX*magnification,highY*magnification,width*magnification,highHeight*magnification,1);

  for(i=highY;i<highHeight+highY;i++){
    terrian[highX][i] = 1;
  }

  if(rootFirst==rootSecond || rootFirst+1==rootSecond || rootFirst-1==rootSecond){
    //printf("道を引く必要はありません。\n");
  }
  else{
    if(rootFirst>rootSecond){
      HgWBoxFill(layerID,
                 rootSecond*magnification,
                 rootToRootY*magnification,
                 abs(1+rootFirst-rootSecond)*magnification,
                 1*magnification,1);
      for(i=rootSecond;i<rootSecond+abs(1+rootFirst-rootSecond);i++){
        terrian[i][rootToRootY] = 1;
        printf("terrian[%d][%d]\n",i,rootToRootY);
      }
    }
    else{
      HgWBoxFill(layerID,
                 rootFirst*magnification,
                 rootToRootY*magnification,
                 abs(rootFirst-rootSecond)*magnification,
                 1*magnification,1);
      for(i=rootFirst;i<=rootFirst + abs(1+rootFirst-rootSecond);i++){
         terrian[i][rootToRootY] = 1;
       }
    }
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

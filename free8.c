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

//構造体宣言
typedef struct charctor{
  int x;
  int y;
  int hp;
}charctor;

//プロトタイプ宣言
int getRoom();  //部屋の情報を取得
int grid();     //仮のグリッド線を描画
int getRoot();  //部屋と部屋の道を取得
int getRootRight(int,int);  //部屋と部屋の道を取得（横）
int getRootUp(int,int);     //部屋と部屋の道を取得（縦)
int CharctorController(charctor);   //キャラクターのアクションを操作
int moveRight(charctor);    //右に移動（キャラクターであれば可能
int moveLeft(charctor);     //左に移動　
int moveUp(charctor);       //上に移動
int moveDown(charctor);     //下に移動
int regulation();           //ダンジョン生成後の位置調整
int UIController();

//グローバル変数
int roomX[9]={};    //部屋の大きさX
int roomY[9]={};    //部屋の大きさY
int iniRoomX[9]={}; //部屋の初期位置を少しずらすX
int iniRoomY[9]={}; //部屋の初期位置を少しずらすY
int layerID;        //ベースレイヤーの番号
int terrian[terrianSizeX][terrianSizeY];  //地形情報
int Room[9][4] = {};  //部屋の情報（X座標,Y座標,横幅,高さ)
int charctorLayer;    //キャラクターを描画するレイヤー
int UILayer;          //別ウィンドウのUIを描画するレイヤー
charctor player = {10,10,10};  //プレイヤーを定義

int main(void){
  doubleLayer layers;    //ダブルバッファ用のデータ
  int i,j;
  int windowID;          //ベースウィンドウの番号
  int UIID;              //UIのウィンドウ番号

  windowID = HgOpen(WindowWidth,WindowHeight);    //ベースレイヤーをオープン
  layerID = HgWAddLayer(windowID);                //ベースレイヤーをオープン
  HgWSetEventMask(layerID,HG_KEY_DOWN);           //ドラッグとクリックを検出
  UIID = HgWOpen(0,1200,150,100);               //UIレイヤーをオープン
  UILayer = UIID;                                 //UIレイヤーをオープン
  getRoom();                                      //部屋を取得
  getRoot();                                      //道を取得
  regulation();                                   //部屋、道を取得後の位置調整
  charctorLayer = HgWAddLayer(layerID);           //キャラクターレイヤーをオープン
  grid();                                         //グリッド線を描画

  while(1){  //メイン処理
    hgevent *event = HgEvent();              //イベントを取得

    if (event->type == HG_KEY_DOWN) {        //イベント判定
      switch (event->ch) {
        case 119: player.y+=moveUp(player);               //w（前に進む）
                  break;
        case 97:  player.x-=moveLeft(player);             //a（左に進む）
                  break;
        case 115: player.y-=moveDown(player);             //s（下に進む）
                  break;
        case 100: player.x += moveRight(player);          //d（右に進む）
                  break;
        case 108:
                 //新しくダンジョン生成の際の初期化
                 for(i=0;i<terrianSizeX;i++){
                   for(j=0;j<terrianSizeY;j++){
                       terrian[i][j] = 0;
                   }
                 }
                 HgLClear(layerID);                       //ベースレイヤーをクリア
                 getRoom();                               //部屋を取得
                 getRoot();                               //道を取得
                 regulation();                            //位置調整
                 grid();                                  //グリッド線の描画
                 for(i=terrianSizeY-1;i>=0;i--){          //ログ
                   for(j=0;j<terrianSizeX;j++){
                     printf("%d ",terrian[j][i]);
                   }
                   printf("\n");
                 }
                 player.hp-=1;
                 break;
        defalut: break;
        }
    }
    CharctorController(player);    //キャラクターのアクションを操作
    UIController();
  }
}

//別ウィンドウのUIを操作
int UIController(){
  int hp = player.hp*10;
  int damage = 100-hp;
  HgLClear(UILayer);
  HgWText(UILayer,10,30,"HP : %d/10",hp/10);
  HgWSetFillColor(UILayer,HG_GREEN);
  HgWBoxFill(UILayer,10,10,hp,20,1);
  HgWSetFillColor(UILayer,HG_RED);
  HgWBoxFill(UILayer,110-damage,10,damage,20,1);

  return 0;
}

/**　キャラクターのアクションを操作 **/
int CharctorController(charctor charctor){
  HgLClear(charctorLayer);
  HgWSetFillColor(charctorLayer,HG_WHITE);
  HgWCircleFill(charctorLayer,charctor.x*magnification-10,charctor.y*magnification-10,charctorSize,1);  //キャラクタを描画
  printf("charctor position:terrian[%d][%d]\n",charctor.x,charctor.y);
  return 0;
}

//キャラクターを右に移動
int moveRight(charctor charctor){
  if(terrian[(charctor.x)+1][charctor.y]==1) {
    return 1;
  }
  else{
    return 0;
  }
}

//キャラクターを左に移動
int moveLeft(charctor charctor){
  if(terrian[(charctor.x)-1][charctor.y]==1) {
    return 1;
  }
  else{
    return 0;
  }
}

//キャラクターを上に移動
int moveUp(charctor charctor){
  if(terrian[(charctor.x)][charctor.y+1]==1) {
    return 1;
  }
  else{
    return 0;
  }
}

//キャラクターを下に移動
int moveDown(charctor charctor){
  if(terrian[(charctor.x)][charctor.y-1]==1) {
    return 1;
  }
  else{
    return 0;
  }
}

/** 部屋を取得
 **
 ** 各部屋を横幅８〜１２、縦８〜１０
 **  初期値 横幅１〜２、　縦１〜２でランダムに部屋を配置
**/
int getRoom(){
  int i,j,k,l,width,height,iniWid,iniHei,temp,X,Y;
  temp = 0;
  srand(time(NULL));
  for(i=0;i<3;i++){         //部屋の大きさを乱数で設定
    for(j=0;j<3;j++){       //部屋の大きさを乱数で設定
      iniHei = rand()%2+1;  //1から２まで部屋の初期いちをずらす
      iniWid = rand()%2+3;  //３から４まで部屋の初期いちをずらす
      width = rand()%4+8;   //8から12まで部屋の大きさを決定するX
      height = rand()%2+8;  //8から12まで部屋の大きさを決定するY

      X = iniWid+(j*18);    //Xの初期値
      Y = iniHei+(i*12);    //yの初期値

      for(l=Y;l<Y+height;l++){  //地形情報を保持
        for(k=X;k<X+width;k++){ //
          terrian[k][l] = 1;    //移動できる場所は1を代入
        }
      }

      HgWSetFillColor(layerID,HG_GREEN);  //部屋は緑色で描画
      HgWBoxFill(layerID,(X*magnification),(Y*magnification),width*magnification,height*magnification,1); //部屋を描画
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

/**
  * 部屋から部屋につなぐ道を計算、描画
  * first:左側,second:右側
  * 例: getRoomRight(0,1)...０番と１番の部屋で道をつなぐ
**/
int getRootRight(int first,int second){
  int i,rootFirst,rootSecond,height,leftX,leftY,leftWidth,rightX,rightY,rightWidth,rootToRootX;

  srand(time(NULL));
  rootFirst = rand()%(roomY[first]-1)+iniRoomY[first];    //ランダムで道の初期値を発生
  rootSecond = rand()%(roomY[second]-1)+iniRoomY[second]; //ランダムで道の初期値を発生
  height  = 1;                                            //道の幅
  rootToRootX = 16;                                       //道の基準点

  leftX       = (iniRoomX[first] + roomX[first]);         //Xの初期値(誤差と大きさを足した)
  leftY       = (1+rootFirst);                            //Yの初期値(初期値の１と乱数発生の値を足した)
  leftWidth   = (20-(3+iniRoomX[first]+roomX[first]));    //(全体からXの初期値を引いた)

  rightX      = 16;                                       //Xの基準点(基準点から出す値)
  rightY      = (rootSecond);                             //Yの基準点(基本の＋１と乱数発生の値を足した)
  rightWidth  = (2+iniRoomX[second]);                     //右の余分な１８と基準の３に乱数発生を足した)

  if(first%2!=0) {       //1-2,4-5,7-8の時は定数たす
    leftX+=18;
    rightX+=18;
    rootToRootX += 18;
  }
  if(first==3){          //4の時、上にずらさないといけないため、足し込み
    //デバッグ
    leftX-=18;
    rightX-=18;
    rootToRootX-=18;

    leftY+=12;
    rightY+=12;
    rootFirst+=12;       //道と道をつなぐ際に必要な要素
    rootSecond+=12;      //上に同様
  }
  if(first==4){          //4の時、上にずらさないといけないため、足し込み
    //デバッグ
    leftX+=18;
    rightX+=18;
    rootToRootX+=18;

    leftY+=12;
    rightY+=12;
    rootFirst+=12;       //道と道をつなぐ際に必要な要素、
    rootSecond+=12;      //上に同様
  }
  if(first==6 || first==7){  //6,7の際に上にずらす必要がある
    leftY+=24;
    rightY+=24;
    rootFirst+=24;           //道と道をつなぐ際に必要な要素、
    rootSecond+=24;          //上に同様
  }
  //道は青
  HgWSetFillColor(layerID,HG_BLUE);
  //左から基準点までの道の描画
  HgWBoxFill(layerID,leftX*magnification,leftY*magnification,leftWidth*magnification,height*magnification,1);
  //右から基準点までの道の描画
  HgWBoxFill(layerID,rightX*magnification,rightY*magnification,rightWidth*magnification,height*magnification,1);

  //移動できる場所に1を代入
  for(i=leftX;i<leftX+leftWidth;i++){
    terrian[i][leftY] = 1;
  }
  //移動できる場所に1を代入
  for(i=rightX;i>rightX-rightWidth;i--){
    terrian[5+i][rightY] = 1;
  }

  if (rootFirst != rootSecond){
    if(rootFirst>rootSecond){
      //道と道をつなぐ道は赤
      HgWSetFillColor(layerID,HG_RED);
      HgWBoxFill(layerID,                                       //道と道をつなぐ道の描画
                 rootToRootX*magnification,                     //左側が上にある時、基準点から道の高さまで描画する
                 rootSecond*magnification,
                 1*magnification,
                 abs(1+rootFirst-rootSecond)*magnification,1);  //幅の絶対値をとる

      for(i=rootSecond;i<=rootSecond+abs(1+rootFirst-rootSecond);i++){
        terrian[rootToRootX][i] = 1;                            //移動できる場所に1を代入
      }
    }
    else{  //上に同様　
      HgWBoxFill(layerID,
                 rootToRootX*magnification,
                 (1+rootFirst)*magnification,
                 1*magnification,
                 abs(rootFirst-rootSecond)*magnification,1);

      for(i=rootFirst+1;i<=rootFirst+abs(rootFirst-rootSecond);i++){
        terrian[rootToRootX][i] = 1;  //移動できる場所に1を代入
      }
    }
  }
  return 0;
}


/** 縦の道をつなぐ、つなぎかたはgetRootRightに準ずる **/
int getRootUp(int first, int second){
  int i,rootFirst,rootSecond,height,lowX,lowY,lowHeight,highX,highY,highHeight,width,rootToRootY;
  srand(time(NULL));
  rootFirst = rand()%(roomX[first])+iniRoomX[first];    //誤差も含めたfirstの部屋のX座標方面大きさを決定,
  rootSecond = rand()%(roomX[second])+iniRoomX[second]; //誤差も含めたsecondの部屋のX座標方面の大きさを決定
  height = 12;
  width = 1;
  rootToRootY = 11;

  lowX       = (rootFirst);                             //Xの初期値(誤差と大きさを足す)
  lowY       = (roomY[first] +iniRoomY[first]);         //Yの初期値(初期値の１と乱数発生の値を足す)
  lowHeight   = (15-(3+iniRoomY[first]+roomY[first]));  //(全体からXの初期値を引いた)

  highX      = (rootSecond);                            //Xの基準点(基準点から出す値)
  highY      = 11;                                      //Yの基準点(基本の＋１と乱数発生の値を足した)
  highHeight  = (1+iniRoomY[second]);                   //右の余分な１８と基準の３に乱数発生を足した)

  if(first>2) {   //1-2,4-5,7-8の時は定数たす
    lowY+=12;
    highY+=12;
    rootToRootY += 12;
  }
  if(first==1 || first==4){  //getRootRightと同様
    lowX+=18;
    highX+=18;
    rootFirst+=18;           //道と道をつなぐ際に必要な要素、
    rootSecond+=18;          //上に同様
  }
  if(first==2 || first==5){  //getRootRightと同様
    lowX+=36;
    highX+=36;
    rootFirst+=36;           //道と道をつなぐ際に必要な要素、
    rootSecond+=36;          //上に同様
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
  else{                             //道と道をつなぐ道の計算と描画
    if(rootFirst>rootSecond){
      HgWBoxFill(layerID,
                 rootSecond*magnification,
                 rootToRootY*magnification,
                 abs(1+rootFirst-rootSecond)*magnification,
                 1*magnification,1);
      for(i=rootSecond;i<rootSecond+abs(1+rootFirst-rootSecond);i++){
        terrian[i][rootToRootY] = 1;
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

//位置調整
int regulation(){
  int i,j,temp;
  for(i=terrianSizeX;i>0;i--){
    for(j=terrianSizeY;j>0;j--){
      terrian[i+1][j+1] = terrian[i][j];
    }
  }
  return 0;
}

//仮のグリッド線を描画
int grid(){
  int i,width,temp;
  temp = WindowWidth / terrianSizeX;
  for(i=0;i<terrianSizeX;i++){
    HgWLine(layerID,width,0,width,WindowHeight);
    HgWLine(layerID,0,width,WindowWidth,width);
    width = width + temp;
  }
  return 0;
}

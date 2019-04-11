/**
金種計算　
854003 山内龍我
**/

#include<stdio.h>
#include<handy.h>

//プロトタイプ宣言
int textWrite();

int main(){
  int i = 0; //カウンタ
  int j = 0; //カウンタ
  int total; //計算のためのtemp変数
  int kind[6] = {500,100,50,10,5,1};  //硬貨の種類
  int num[6] = {};  //何枚なのか保持
  int x,y;  //コインの位置
  x = 50;
  y = 100;

  scanf("%d",&total);

  while(total!=0){
    num[i] = total/kind[i];
    total = total%kind[i];
    i++;
  }

  HgOpen(1000,600);
  textWrite();

  for(i=0;i<6;i++){
    for(j=0;j<num[i];j++){
      HgSetFillColor(HG_BLUE);
      HgCircleFill(x,y,20,1);
      y = y+10;
    }
    x = x+100;
    y = 100;
  }
  HgGetChar();
  HgClose();
  return 0 ;
}


//文字を書く
int textWrite(){
  HgText(20,50,"５００円");
  HgText(140,50,"１００円");
  HgText(240,50,"５０円");
  HgText(340,50,"１０円");
  HgText(440,50,"５円");
  HgText(540,50,"１円");
}
